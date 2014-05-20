//---------------------------------------------------------------------------


#pragma hdrstop

#include "windows.h"
#include <stdio.h>
#include "ServerListLoader.h"
#include "gamespy/gsmsalg.h"
#include "Unit1.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

ServerListLoader::ServerListLoader(int timeout) {
        this->timeout = timeout;
        this->socket = new TClientSocket(NULL);
        this->socket->ClientType = ctBlocking;
        this->stream = NULL;
}

ServerListLoader::~ServerListLoader() {
        this->reset();
        if(this->socket) {
                delete this->socket;
        }
}

TStringList* ServerListLoader::getServerList(String masterServerDomain, int port, String gamename, String gamekey) {
        this->reset();
        this->gamename = gamename;
        this->gamekey = gamekey;
        this->socket->Host = masterServerDomain;
        this->socket->Port = port;
        try {
                this->socket->Open();
        } catch (Exception &E) {
                return NULL;
        }
        try {
                this->stream = new TWinSocketStream(this->socket->Socket, this->timeout);
        } catch (Exception &E) {
                return NULL;
        }
        TStringList *ips = new TStringList;
        ips->Duplicates = dupIgnore;
        if(this->stream->WaitForData(this->timeout)) {
                int bufferSize = 128;
                char *buf = new char[bufferSize];
                String incomingText = "";
                int len = 0;
                try {
                        len = this->stream->Read(buf, bufferSize - 1);
                        buf[len] = 0;
                        incomingText = String(buf);
                        delete buf;
                } catch (Exception &E) {
                        delete buf;
                        return ips;
                }
                int pos = incomingText.AnsiPos("\\secure\\");
                if(pos >= 0 && ((pos + 13) <= incomingText.Length())) {
                        String secure = incomingText.SubString(pos + 8, 6);
                        int enctype = 2;
                        char *dest = new char[89];
                        String validate = "";
                        try {
                                gsseckey(dest, secure.c_str(), this->gamekey.c_str(), enctype);
                                validate = String(dest);
                                delete dest;
                        } catch (Exception &E) {
                                delete dest;
                                return ips;
                        }
                        String reply = "\\gamename\\";
                        reply += this->gamename;
                        reply += "\\gamever\\1.8\\location\\0\\validate\\";
                        reply += validate;
                        reply += "\\enctype\\";
                        reply += IntToStr(enctype);
                        reply += "\\final\\\\queryid\\1.1";
                        String query = "\\list\\cmp\\gamename\\";
                        query += this->gamename;
                        query += String("\\enctype\\");
                        enctype = 3;
                        query += IntToStr(enctype);
                        query += String("\\where\\\\final\\");
                        reply += query;
                        int writeBufSize = reply.Length();
                        char *writeBuf = new char[writeBufSize];
                        strcpy(writeBuf, reply.c_str());
                        try {
                                this->stream->WriteBuffer(writeBuf, writeBufSize);
                                delete writeBuf;
                        } catch (Exception &E) {
                                delete writeBuf;
                                return ips;
                        }

                        unsigned char start = 0;
                        int counter = 0;
                        while(counter < 4 && this->stream->WaitForData(this->timeout)) {
                                try {
                                        this->stream->ReadBuffer(&start, 1);
                                        if(start == 0xFF) {
                                                counter++;
                                        } else {
                                                counter = 0;
                                        }
                                } catch (Exception &E) {
                                        return ips;
                                }
                        }
                        int bytesReceived = 0, completeLength;
                        if(this->stream->WaitForData(this->timeout)) {
                                char *header = new char[8];
                                try {
                                        this->stream->ReadBuffer(header, 8);
                                } catch (Exception &E) {
                                        delete header;
                                        return ips;
                                }
                                int ipv4 = header[0];
                                ipv4 = (ipv4 << 4) | header[1];
                                ipv4 = (ipv4 << 4) | header[2];
                                ipv4 = (ipv4 << 4) | header[3];
                                int ipv6 = header[4];
                                ipv6 = (ipv6 << 4) | header[5];
                                ipv6 = (ipv6 << 4) | header[6];
                                ipv6 = (ipv6 << 4) | header[7];
                                delete header;
                                int received = 0, buflen = 6;
                                unsigned char *ipBuf = new unsigned char[buflen];
                                while(received < ipv4) {
                                        if(this->stream->WaitForData(this->timeout)) {
                                                try {
                                                        this->stream->ReadBuffer(ipBuf, buflen);
                                                } catch (Exception &E) {
                                                        break;
                                                }
                                                received += buflen;
                                                int port = ((int)(ipBuf[4] << 8) | (int)ipBuf[5]);
                                                String address = IntToStr(ipBuf[0]) + ".";
                                                address += IntToStr(ipBuf[1]) + ".";
                                                address += IntToStr(ipBuf[2]) + ".";
                                                address += IntToStr(ipBuf[3]) + ":";
                                                address += IntToStr(port);
                                                ips->Add(address);
                                        } else {
                                                break;
                                        }
                                }
                                delete ipBuf;
                        }
                }
        }
        return ips;
}

void ServerListLoader::reset() {
        if(this->socket->Socket->Connected) {
                this->socket->Socket->Close();
        }
        if(this->stream) {
                delete this->stream;
        }
        this->gamename = "";
        this->gamekey = "";
}

String ServerListLoader::getGamename() {
        return this->gamename;
}

String ServerListLoader::getGameKey() {
        return this->gamekey;
}
