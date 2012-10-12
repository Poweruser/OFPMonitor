//---------------------------------------------------------------------------

#pragma hdrstop
#include "QueryRequest.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

QueryRequest::QueryRequest(Server *svr, String query) {
        this->svr = svr;
        this->query = query;
}

Server* QueryRequest::getServer() {
        return this->svr;
}

String QueryRequest::getQuery() {
        return this->query;
}