//---------------------------------------------------------------------------

#pragma hdrstop
#include "QueryRequest.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

QueryRequest::QueryRequest(int serverID, String query) {
        this->serverID = serverID;
        this->query = query;
}

int QueryRequest::getServerID() {
        return this->serverID;
}

String QueryRequest::getQuery() {
        return this->query;
}