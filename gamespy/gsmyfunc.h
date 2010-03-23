/*
    Copyright 2005,2006,2007,2008,2009,2010 Luigi Auriemma

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

    http://www.gnu.org/licenses/gpl-2.0.txt
*/

#define FREEX(X)    freex((void **)&X)
void freex(void **buff) {
    if(!buff || !*buff) return;
    free(*buff);
    *buff = NULL;
}

unsigned char *myinetntoa(unsigned int ip) { // avoids warnings and blablabla
    struct in_addr  ipaddr;
    ipaddr.s_addr = ip;
    return(inet_ntoa(ipaddr));
}




int timeout(int sock, int sec) {
    struct  timeval tout;
    fd_set  fd_read;
    int     err;

    tout.tv_sec  = sec;
    tout.tv_usec = 0;
    FD_ZERO(&fd_read);
    FD_SET(sock, &fd_read);
    err = select(sock + 1, &fd_read, NULL, NULL, &tout);
 //   if(err < 0) std_err();
    if(!err) return(-1);
    return(0);
}



unsigned long resolv(char *host) {
    struct      hostent *hp;
    unsigned long   host_ip;

    host_ip = inet_addr(host);
    if(host_ip == htonl(INADDR_NONE)) {
        hp = gethostbyname(host);
        if(!hp) {   // I prefer to exit instead of returning INADDR_NONE
//            fprintf(stderr, "\nError: Unable to resolv hostname (%s)\n\n", host);
           //  exit(1);
        } else host_ip = *(unsigned long *)(hp->h_addr);
    }
    return(host_ip);
}



int mystrcpy(unsigned char *dst, unsigned char *src, int max) {
    unsigned char      *p;

    for(p = dst; *src && --max; p++, src++) *p = *src;
    *p = 0;
    return(p - dst);
}



    /* returns a new clean string */
unsigned char *mychrdup(unsigned char *src) {
    int     len,
            max;
    unsigned char      *dst;

    len = max = strlen(src);
    dst = (unsigned char *) malloc(max + 1);
    if(!dst) std_err();

    max = enctypex_data_cleaner(dst, src, max);

        // probably useless free memory
    if(max < len) {
        dst = (unsigned char *) realloc(dst, max + 1);
        if(!dst) std_err();
    }

    return(dst);
}



int mysnprintf(unsigned char *buff, int len, unsigned char *fmt, ...) {
    va_list ap;
    int     ret;

    va_start(ap, fmt);
    ret = vsnprintf(buff, len, fmt, ap);
    va_end(ap);

    if((ret < 0) || (ret >= len)) {
        ret = len;
        buff[len] = 0;
    }
    return(ret);
}
  

int vspr(unsigned char **buff, unsigned char *fmt, va_list ap) {
    int     len,
            mlen;
    unsigned char      *ret;

    mlen = strlen(fmt) + 128;

    for(;;) {
        ret = (unsigned char *) malloc(mlen);
        if(!ret) return(0);     // return(-1);
        len = vsnprintf(ret, mlen, fmt, ap);
        if((len >= 0) && (len < mlen)) break;
        if(len < 0) {           // Windows style
            mlen += 128;
        } else {                // POSIX style
            mlen = len + 1;
        }
        FREEX(ret);
    }

    *buff = ret;
    return(len);
}

int tcpspr(int sd, unsigned char *fmt, ...) {
    va_list ap;
    int     len;
    unsigned char      *buff;

    va_start(ap, fmt);
    len = vspr(&buff, fmt, ap);
    va_end(ap);

    len = send(sd, buff, len, 0);
    FREEX(buff);
    return(len);
}



int tcpxspr(int sd, unsigned char *gamestr, unsigned char *msgamestr, unsigned char *validate, unsigned char *filter, unsigned char *info, int type) {  // enctypex
    int     len;
    unsigned char      *buff,
            *p;

    len = 2 + 7 + strlen(gamestr) + 1 + strlen(msgamestr) + 1 + strlen(validate) + strlen(filter) + 1 + strlen(info) + 1 + 4;
    buff = (unsigned char *) malloc(len);

    p = buff;
    p += 2;
    *p++ = 0;
    *p++ = 1;
    *p++ = 3;
    *p++ = 0;   // 32 bit
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    p += sprintf(p, "%s", gamestr) + 1;     // the one you are requesting
    p += sprintf(p, "%s", msgamestr) + 1;   // used for the decryption algorithm
    p += sprintf(p, "%s%s", validate, filter) + 1;
    p += sprintf(p, "%s", info) + 1;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = type;
        // bits which compose the "type" byte:
        // 00: plain server list, sometimes the master server returns also the informations if requested
        // 01: requested informations of the server, like \hostname\numplayers and so on
        // 02: nothing???
        // 04: available informations on the master server??? hostname, mapname, gametype, numplayers, maxplayers, country, gamemode, password, gamever
        // 08: nothing???
        // 10: ???
        // 20: peerchat IRC rooms
        // 40: ???
        // 80: nothing???

    len = p - buff;
    buff[0] = len >> 8;
    buff[1] = len;

    len = send(sd, buff, len, 0);
    FREEX(buff);
    return(len);
}



unsigned char *strduplow(unsigned char *str) {
    unsigned char     *p;

    str = strdup(str);
    for(p = str; *p; p++) {
        *p = tolower(*p);
    }
    return(str);
}



#define MAXDNS  64

    /* the following function caches the IP addresses    */
    /* actually the instructions which replace the older */
    /* entries are not the best in the world... but work */


unsigned long dnsdb(char *host) {
    typedef struct {
        unsigned long   ip;
        unsigned char          *host;
        time_t      time;
    } db_t;

    static db_t *db;
    static int  older;
    unsigned long   fastip;
    int         i;

    if(!host) {
        db = (db_t *) malloc(sizeof(db_t) * MAXDNS);         // allocate
       // if(!db) std_err();

        for(i = 0; i < MAXDNS; i++) {
            db[i].ip   = INADDR_NONE;
            db[i].host = NULL;
            db[i].time = time(NULL);
        }

        older = 0;
        return 0;
    }

    if(!host[0]) return(INADDR_NONE);

    fastip = inet_addr(host);

    if(fastip != INADDR_NONE) return(fastip);

    for(i = 0; i < MAXDNS; i++) {
        if(!db[i].host) break;                      // new host to add

        if(!strcmp(db[i].host, host)) {             // host in cache
            db[i].time = time(NULL);                // update time
            return(db[i].ip);
        }

        if(db[i].time < db[older].time) {           // what's the older entry?
            older = i;
        }
    }

    if(i == MAXDNS) i = older;                      // take the older one

    if(db[i].host) free(db[i].host);

    db[i].ip   = resolv(host);

    if(db[i].ip == INADDR_NONE) {
        db[i].host = NULL;
        return(INADDR_NONE);
    }

    db[i].host = strduplow(host);                   // low case!

    db[i].time = time(NULL);
              
    return(db[i].ip);
}

int tcpsocket(void) {
    static const struct linger  ling = {1,1};
    int     sd;

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //if(sd < 0) std_err();
    setsockopt(sd, SOL_SOCKET, SO_LINGER, (char *)&ling, sizeof(ling));
    return(sd);
}

void gslist_step_1(unsigned char *gamestr, unsigned char *filter) {

    if(enctypex_query[0] && (myenctype >= 0)) {
        myenctype = -1;
    }

    if(myenctype < 0) {
        if((unsigned char *)msgamename == (unsigned char *)MSGAMENAME) {  // change if default
            msgamename = (unsigned char *)MSGAMENAMEX;
            msgamekey  = (unsigned char *)MSGAMEKEYX;
        }
        if(!mymshost) {   // lame work-around in case we use -x IP
            mshost = enctypex_msname(gamestr, NULL);
            msport = MSXPORT;
        }
    }

    if((enctypex_type == 0x20) && !enctypex_query[0]) {
        enctypex_query = "\\hostname";
    }

    msip = dnsdb(mshost);

}



int gslist_step_2(struct sockaddr_in *peer, unsigned char *buff, unsigned char *secure, unsigned char *gamestr, unsigned char *validate, unsigned char *filter, enctypex_data_t *enctypex_data) {

    int sd = tcpsocket();
    if(connect(sd, (struct sockaddr *)peer, sizeof(struct sockaddr_in)) >= 0) {
        if(myenctype < 0) {
                memset(enctypex_data, 0, sizeof(enctypex_data_t));    // needed
                enctypex_decoder_rand_validate(validate);
                if(tcpxspr(sd,
                gamestr,
                msgamename,
                validate,
                filter,
                enctypex_query,  // \\hostname\\gamever\\numplayers\\maxplayers\\mapname\\gametype
                enctypex_type) >= 0) {
                        return(sd);
                }
        }

    }
    close(sd);
    return(-1);
}



ipport_t *gslist_step_3(int gsTcpSocket, unsigned char *validate, enctypex_data_t *enctypex_data, int *ret_len, unsigned char **ret_buff, int *ret_dynsz) {
    ipport_t    *ipport;
    int     err,
            len,
            dynsz;
    unsigned char      *buff;

    buff   = *ret_buff;
    dynsz  = *ret_dynsz;

    ipport = NULL;
    len    = 0; // *ret_len not needed

    while(!timeout(gsTcpSocket, 10)) {

        err = recv(gsTcpSocket, buff + len, dynsz - len, 0);
        if(err <= 0) break;
        len += err;
        if(len >= dynsz) {
            dynsz += BUFFSZ;
            buff = (unsigned char *) realloc(buff, dynsz);
      //      if(!buff) std_err();
        }
        if(myenctype < 0) {   // required because it's a streamed list and the socket is not closed by the server
            ipport = (ipport_t *)enctypex_decoder(msgamekey, validate, buff, &len, enctypex_data);
            if(ipport && enctypex_decoder_convert_to_ipport((unsigned char *)ipport, len - ((unsigned char *)ipport - buff), NULL, NULL, 0, 0)) break;  // end of the stream
        }
    
    }
    close(gsTcpSocket);

    *ret_len   = len;
    *ret_buff  = buff;
    *ret_dynsz = dynsz;

    return(ipport);

}



int gslist_step_4(unsigned char *secure, unsigned char *buff, enctypex_data_t *enctypex_data, ipport_t **ret_ipport, int *ret_len) {
    static unsigned char   *enctypextmp    = NULL;
    ipport_t    *ipport;
    int     len,
            itsok;

    ipport = *ret_ipport;
    len    = *ret_len;
    itsok  = 1;
    if(!myenctype && !strncmp(buff + len - 7, "\\final\\", 7)) {
        ipport = (ipport_t *)buff;
        len -= 7;
    } else if((myenctype < 0) && len && ipport) {
            // because for some games like AA the server sends 5 bytes for each IP
            // so if I use the same untouched buffer as input and output I overwrite its fields
            // the amount of allocated bytes wasted by this operation is enough small (for example 200k on 1megabyte of received data)
        enctypextmp = (unsigned char *) realloc(enctypextmp, (len / 5) * 6);
        if(!enctypextmp) std_err();
        len = enctypex_decoder_convert_to_ipport(buff + enctypex_data->start, len - enctypex_data->start, enctypextmp, NULL, 0, 0);
        if(len < 0) {   // yeah, the handling of the master server's error doesn't look so good although all perfect, but it's a rare event and I wanted to handle it
            if(enctypex_data->offset > enctypex_data->start) {
                len = enctypex_data->offset - enctypex_data->start;
                memmove(buff, buff + enctypex_data->start + ((len > 6) ? 6 : 0), len - ((len > 6) ? 6 : 0));
            } else {
                len = 0;
            }
            ipport = NULL;
            itsok  = 0;
        } else {
            ipport = (ipport_t *)enctypextmp;
        }
    } else {
        ipport = NULL;
        itsok  = 0;
    }
    if(!ipport) itsok = 0;
    if(len < 0) {
        itsok = 0;
        len = 0;
    }

    *ret_ipport = ipport;
    *ret_len    = len;
    return(itsok);
}
