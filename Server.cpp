//---------------------------------------------------------------------------


#pragma hdrstop

#include "Server.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

                ServerItem::ServerItem() {
                        this->address = "";
                        this->watch = false;
                        this->favorite = false;
                        this->persistent = false;
                        this->blocked = false;
                }

                ServerItem::ServerItem(String address) {
                        this->address = address;
                        this->watch = false;
                        this->favorite = false;
                        this->persistent = false;
                        this->blocked = false;
                }

                Server::Server() {
                        this->watch = false;
                        this->favorite = false;
                        this->persistent = false;
                        this->blocked = false;
                        this->index = -1;
                        this->ip = "";
                        this->gamespyport = 0;
                        this->timeouts = 0;
                        this->ping = 0;
                        this->clear();
                }

                Server::Server(String i, int p, int ind) {
                        this->watch = false;
                        this->favorite = false;
                        this->persistent = false;
                        this->blocked = false;
                        this->clear();
                        this->index = ind;
                        this->ip = i;
                        this->timeouts = 0;
                        this->ping = 0;
                        this->gamespyport = p;
                }

                void Server::clear() {
                        this->autojoin = false;
                        this->autojoinConf = "";
                        this->gameport = 0;
                        this->timeleft = "";
                        this->gametime = 0;
                        this->players = 0;
                        this->maxplayers = 0;
                        this->mission = "";
                        this->name = "";
                        this->gamestate = 0;
                        this->impl = "";
                        this->param1 = "";
                        this->param2 = "";
                        this->island = "";
                        this->actver = 0;
                        this->reqver = 0;
                        this->platform = "";
                        this->password = -1;
                        this->mod = "";
                        this->equalMod = 0;
                        this->messageSent = 0;
                        this->queryid = 0;
                        this->playerlist.clear();
                        this->notificationRuleIndex = -1;
                        this->missedQueryTurns = 1;
                        this->emptyServerCounter = 0;
                }

                String Server::getAddress() {
                        String out = this->ip + ":";
                        if(this->gameport > 0) {
                                out += IntToStr(this->gameport);
                        } else {
                                out += IntToStr(this->gamespyport - 1);
                        }
                        return out;
                }

                String Server::getGamespyAddress() {
                        String out = this->ip + ":" + IntToStr(this->gamespyport);
                        return out;
                }

                ServerItem* Server::createServerItem() {
                        ServerItem *sI = new ServerItem(this->getGamespyAddress());
                        sI->watch = this->watch;
                        sI->favorite = this->favorite;
                        sI->persistent = this->persistent;
                        sI->blocked = this->blocked;
                        return sI;
                }


