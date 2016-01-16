//---------------------------------------------------------------------------
#pragma hdrstop

#include "HttpFileDownloader.h"
#include "tchar.h"
#include <windows.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)



/*
 * Class QueueEntry
 */

QueueEntry::QueueEntry(String resourceURL, String description) {
        this->requestHandle = NULL;
        this->resourceURL = resourceURL;
        this->stream = NULL;
        this->errorMessage = "";
        this->description = description;
}

QueueEntry::~QueueEntry() {
        if(this->stream != NULL) {
                delete this->stream;
                this->stream = NULL;
        }
}

bool QueueEntry::isDone() {
        return (this->stream != NULL);
}

String QueueEntry::getErrorMessage() {
        return this->errorMessage;
}

int QueueEntry::getProgress() {
        return this->progress;
}

bool QueueEntry::downloadResource(HINTERNET connectHandle, bool useSSL) {
        if(connectHandle == NULL) {
                return false;
        }
        String mediaType = "text/";
        mediaType += "*";
        LPCTSTR rgpszAcceptTypes[] = {(mediaType.c_str()), NULL};
        DWORD flags = INTERNET_FLAG_NO_UI | INTERNET_FLAG_RELOAD | INTERNET_FLAG_CACHE_IF_NET_FAIL | INTERNET_FLAG_NO_COOKIES;
        if(useSSL) {
                flags |= INTERNET_FLAG_SECURE;
        }
        this->requestHandle = HttpOpenRequest(connectHandle,
                _T("GET"),
                _T(this->resourceURL.c_str()),
                _T("HTTP/1.1"),
                0,
                rgpszAcceptTypes,
                flags,
                0);

        if(requestHandle == NULL) {
                this->errorMessage = "HttpOpenRequest failed. (Error code: " + String(GetLastError()) + ")";
                return false;
        }

        if(!HttpSendRequest(this->requestHandle, NULL, 0, NULL, 0)) {
                this->errorMessage = "HttpSendRequest failed. (Error code: " + String(GetLastError()) + ")";
                this->closeRequestHandle();
                return false;
        }
        DWORD dwSize = 0;
        TMemoryStream *stream = new TMemoryStream;
        boolean checkForFileNotFoundError = true;
        while (InternetQueryDataAvailable(this->requestHandle, &dwSize, 0, 0) && dwSize > 0) {
                char *lpszData = new char[dwSize + 1];
                DWORD  dwDownloaded = 0;
                if(InternetReadFile(this->requestHandle, (LPVOID)lpszData, dwSize, &dwDownloaded)) {
                        lpszData[dwDownloaded] = '\0';
                        if(checkForFileNotFoundError) {
                                checkForFileNotFoundError = false;
                                String data = String(lpszData);

                                // check for html or xml like content, i.e. 404-error pages
                                if(data.AnsiPos("<") == 1) {
                                        delete stream;
                                        stream = NULL;
                                        delete lpszData;
                                        String errorMsg = "File not found: ";
                                        errorMsg += this->resourceURL;
                                        this->errorMessage = errorMsg;
                                        break;
                                }
                        }

                        try {
                                stream->Write(lpszData, dwDownloaded);
                        } catch (Exception &E) {
                                String errorMsg = "Writing downloaded data to stream failed. (Exception: " + E.Message + ")";
                                this->errorMessage = errorMsg;

                                delete stream;
                                stream = NULL;
                                delete lpszData;
                                break;
                        }
                } else {
                        String errorMsg = "InternetReadFile failed. (Error code: " + String(GetLastError()) + ")";
                        this->errorMessage = errorMsg;

                        delete stream;
                        stream = NULL;
                        delete lpszData;
                        break;
                }

                delete lpszData;
                this->progress = stream->Size;
                this->NotifyObserver();
        }
        this->closeRequestHandle();
        this->stream = stream;
        if(this->stream != NULL) {
                this->stream->Position = 0;
        }
        this->NotifyObserver();
        return this->isDone();
}

bool QueueEntry::getDataAsList(TStringList *list) {
        if(this->isDone()) {
                try {
                        this->stream->Position = 0;
                        list->LoadFromStream(this->stream);
                } catch (Exception &E) {
                        return false;
                }
                return true;
        }
        return false;
}

bool QueueEntry::getDataAsStream(TMemoryStream *stream) {
        if(this->isDone()) {
                try {
                        this->stream->Position = 0;
                        stream->LoadFromStream(this->stream);
                        stream->Position = 0;
                } catch (Exception &E) {
                        return false;
                }
                return true;
        }
        return false;
}

String QueueEntry::getDescription() {
        return this->description;
}

void QueueEntry::closeRequestHandle() {
        if(this->requestHandle != NULL) {
                InternetCloseHandle(this->requestHandle);
                this->requestHandle = NULL;
        }
}

/*
 * Class HttpFileDownloader
 */

HttpFileDownloader::HttpFileDownloader() {
        this->thread = NULL;
        this->openHandle = NULL;
        this->connectHandle = NULL;
        this->queue = new TList;
        this->useSSL = false;
        this->hostURL = "";
        this->port = 0;
        this->mainErrorMessage = "";
}

HttpFileDownloader::~HttpFileDownloader() {
        this->closeConnection();
        if(this->thread != NULL) {
                TerminateThread(this->thread, 0);
                this->thread = NULL;
        }
        while(this->queue->Count > 0) {
                QueueEntry *entry = (QueueEntry*) this->queue->Items[0];
                entry->RemoveAllObservers();
                delete entry;
                this->queue->Delete(0);
        }
        delete this->queue;
}

bool HttpFileDownloader::setHost(String hostURL) {
        URL_COMPONENTS url;
        bool result = crackURL(hostURL, url);
        bool error = false;
        if(result) {
                unsigned short port = url.nPort;
                String host = String(url.lpszHostName);
                if(port != 0 && host.Length() > 0) {
                        String hostAddress = host;
                        int pos = hostAddress.AnsiPos("/");
                        if(pos > 0) {
                                hostAddress = hostAddress.SubString(1, pos - 1);
                        }
                        pos = hostAddress.AnsiPos(":");
                        if(pos > 0) {
                                hostAddress = hostAddress.SubString(1, pos - 1);
                        }
                        this->hostURL = hostAddress;
                        this->port = port;
                        if(this->port == INTERNET_DEFAULT_HTTPS_PORT || hostURL.AnsiPos("https://") > 0) {
                                this->useSSL = true;
                        }
                } else {
                        error = true;
                        this->mainErrorMessage = "Unable to crack host URL. Check it for validity and completeness.";
                }
        } else {
                error = true;
                this->mainErrorMessage = "Unable to crack host URL. Error: " + IntToStr(GetLastError());
        }
        return !error;
}

int HttpFileDownloader::queueResourceForDownload(String resourceURL) {
        return this->queueResourceForDownload(resourceURL, "");
}

int HttpFileDownloader::queueResourceForDownload(String resourceURL, String optionalDescription) {
        QueueEntry *entry = new QueueEntry(resourceURL, optionalDescription);
        entry->SetObserver(this);
        return this->queue->Add(entry);
}

DWORD WINAPI DownloadThread (LPVOID lpdwThreadParam__ ) {
        HttpFileDownloader *downloader = (HttpFileDownloader*) lpdwThreadParam__;
        downloader->downloadInSync();
        downloader->NotifyObserver();
        return 0;
}

void HttpFileDownloader::startDownloadThread() {
        this->thread = CreateThread(0, 0, DownloadThread, this, 0, 0);
}

void HttpFileDownloader::downloadInSync() {
        String userAgent = Application->Title;

        this->openHandle = InternetOpen(userAgent.c_str(),
                        INTERNET_OPEN_TYPE_PRECONFIG,
                        NULL,
                        NULL,
                        0);

        if(this->openHandle != NULL) {
                this->connectHandle = InternetConnect (this->openHandle,
                        this->hostURL.c_str(),
                        this->port,
                        0,
                        0,
                        INTERNET_SERVICE_HTTP,
                        0,
                        NULL);
        } else {
                this->mainErrorMessage = "InternetOpen failed. (Error code: " + String(GetLastError()) + ")";
                return;
        }

        if(this->connectHandle != NULL) {
                for(int i = 0; i < this->queue->Count; i++) {
                        QueueEntry *entry = (QueueEntry*) this->queue->Items[i];
                        if(entry != NULL) {
                                entry->downloadResource(this->connectHandle, this->useSSL);
                        }
                }
        } else {
                this->mainErrorMessage = "InternetConnect failed. (Error code: " + String(GetLastError()) + ")";
        }
        this->closeConnection();
}

QueueEntry* HttpFileDownloader::getQueueEntry(int queueIndex) {
        if(queueIndex >= 0 && queueIndex < this->queue->Count) {
                return (QueueEntry*) this->queue->Items[queueIndex];
        }
        return NULL;
}

bool HttpFileDownloader::getFileAsList(int queueIndex, TStringList *list) {
        QueueEntry *entry = this->getQueueEntry(queueIndex);
        if(entry != NULL) {
                return entry->getDataAsList(list);
        }
        return false;
}

bool HttpFileDownloader::getFileAsStream(int queueIndex, TMemoryStream *stream) {
        QueueEntry *entry = this->getQueueEntry(queueIndex);
        if(entry != NULL) {
                return entry->getDataAsStream(stream);
        }
        return false;
}

bool HttpFileDownloader::checkError(int queueIndex) {
        QueueEntry *entry = this->getQueueEntry(queueIndex);
        if(entry != NULL) {
                return entry->getErrorMessage().Length() > 0;
        }
        return false;
}

String HttpFileDownloader::getErrorMessage(int queueIndex) {
        QueueEntry *entry = this->getQueueEntry(queueIndex);
        if(entry != NULL) {
                return entry->getErrorMessage();
        }
        return "";
}

String HttpFileDownloader::getMainErrorMessage() {
        return this->mainErrorMessage;
}

bool HttpFileDownloader::isDone(int queueIndex) {
        QueueEntry *entry = this->getQueueEntry(queueIndex);
        if(entry != NULL) {
                return entry->isDone();
        }
        return false;
}

int HttpFileDownloader::getProgress(int queueIndex) {
        QueueEntry *entry = this->getQueueEntry(queueIndex);
        if(entry != NULL) {
                return entry->getProgress();
        }
        return 0;
}

String HttpFileDownloader::getDescription(int queueIndex) {
        QueueEntry *entry = this->getQueueEntry(queueIndex);
        if(entry != NULL) {
                return entry->getDescription();
        }
        return "";
}

bool HttpFileDownloader::hasQueueIndex(int queueIndex) {
        QueueEntry *entry = this->getQueueEntry(queueIndex);
        return entry != NULL;
}

void HttpFileDownloader::update(Observable *o) {
        this->NotifyObserver();
}

void HttpFileDownloader::closeConnection() {
        if(this->connectHandle != NULL) {
                InternetCloseHandle(this->connectHandle);
                this->connectHandle = NULL;
        }
        if(this->openHandle != NULL) {
                InternetCloseHandle(this->openHandle);
                this->openHandle = NULL;
        }
}

