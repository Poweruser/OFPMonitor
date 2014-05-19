//---------------------------------------------------------------------------


#pragma hdrstop

#include "HttpsDownloader.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "IdIOHandler"
#pragma link "IdIOHandlerSocket"
#pragma link "IdIOHandlerStack"
#pragma link "IdSSL"

HttpsDownloader::HttpsDownloader(String url) {
        this->url = url;
        this->http = new TIdHTTP(NULL);
        this->ssl = new TIdSSLIOHandlerSocketOpenSSL(NULL);
        this->http->HandleRedirects = true;
        this->http->IOHandler = ssl;
        this->http->ReadTimeout = 2000;
        this->ms = new TMemoryStream;
        this->file = new TStringList;
        this->error = false;
}

HttpsDownloader::~HttpsDownloader() {
        TerminateThread(this->thread, 0);
        delete this->ms;
        this->http->Disconnect();
        delete this->ssl;
        delete this->http;
        delete this->file;
}

DWORD WINAPI DownloadThread (LPVOID lpdwThreadParam__ ) {
        HttpsDownloader *downloader = (HttpsDownloader*) lpdwThreadParam__;
        try {
                downloader->http->Get(downloader->url, downloader->ms);
        } catch (EIdException &E) {
                downloader->error = true;
        }
        downloader->NotifyObserver();
}

void HttpsDownloader::start() {
        this->thread = CreateThread(0, 0, DownloadThread, this, 0, 0);
}

void HttpsDownloader::getFile(TStringList *file) {
        this->ms->Position = 0;
        file->LoadFromStream(this->ms);
}

bool HttpsDownloader::checkError() {
        return this->error;
}
