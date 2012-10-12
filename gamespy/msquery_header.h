#include <winsock2.h>
#include <windows.h>

#pragma pack (1)

#define close       closesocket
#define GSMAXPATH       1024
#define MSXPORT         28910
#define MSPORT          28900
#define GSWPORT         28903
#define BUFFSZ          8192
#define QUERYSZ         BUFFSZ
#define SECURESZ        66
#define VALIDATESZ      ((SECURESZ / 6) * 8)
#define GETSZ           2048

static const unsigned char         MS[]            = "master.gamespy.com";
static const unsigned char         MSGAMENAME[]    = "gamespy2\\gamever\\20603020";
static const unsigned char         MSGAMEKEY[]     = "d4kZca";
static const unsigned char         MSGAMENAMEX[]   = "gslive";
static const unsigned char         MSGAMEKEYX[]    = "Xn221z";


unsigned short     msport          = MSPORT;           // do NOT touch
unsigned char   *mshost         = (unsigned char *)MS,         // do NOT touch
                *msgamename     = (unsigned char *)MSGAMENAME, // do NOT touch
                *msgamekey      = (unsigned char *)MSGAMEKEY,  // do NOT touch
                *mymshost       = NULL,
                gslist_path[GSMAXPATH + 1],
                *multigamenamep  = NULL,
                *multigamename   = NULL,
                *enctypex_query = "",
                *ipc             = NULL;
unsigned long msip          = INADDR_NONE;



int        quiet           = 0,
        myenctype       = -1,
        enctypex_type   = 1,
	sd;

typedef struct {
    unsigned long      ip;
    unsigned short     port;
} ipport_t;

#include "stristr.c"
#include "enctypex_decoder.c"
#include "gsmyfunc.h"

enctypex_data_t enctypex_data;
struct  sockaddr_in peer;
    ipport_t    *ipport,
                *ipbuffer;
int dynsz, len, itsok = 0;
unsigned char   *buff            = NULL,
                *gamestr         = "opflashr",
                validate[VALIDATESZ + 1],
                secure[SECURESZ + 1],
                enctypex_info[QUERYSZ],
                *filter = "";

