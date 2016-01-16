//---------------------------------------------------------------------------

#ifndef HttpFileDownloaderH
#define HttpFileDownloaderH

#include <vcl.h>
#include "Observer.h"
#include "Wininet.h"

bool crackURL(String url, URL_COMPONENTS &urlComponents) {
	memset(&urlComponents, 0, sizeof(urlComponents));
	urlComponents.dwStructSize = sizeof(urlComponents);
	urlComponents.dwHostNameLength = 1;
        urlComponents.dwUserNameLength = 1;
        urlComponents.dwPasswordLength = 1;
        urlComponents.dwUrlPathLength = 1;

        char *urlToCrack = url.c_str();
        return InternetCrackUrl(urlToCrack, strlen(urlToCrack), 0, &urlComponents);
}

class QueueEntry : public Observable {
        public:
                QueueEntry(String resourceURL, String description);
                ~QueueEntry();
                bool isDone();
                int getProgress();
                String getErrorMessage();
                bool downloadResource(HINTERNET connectHandle, bool useSSL);
                bool getDataAsList(TStringList *list);
                bool getDataAsStream(TMemoryStream *stream);
                String getDescription();

        private:
                HINTERNET requestHandle;
                TMemoryStream *stream;
                String errorMessage;
                String resourceURL;
                String description;
                int progress;

                void closeRequestHandle();
};

class HttpFileDownloader : public Observable, Observer {
        public:
                HttpFileDownloader();

                ~HttpFileDownloader();
                bool setHost(String hostURL);
                int queueResourceForDownload(String resourceURL);
                int queueResourceForDownload(String resourceURL, String optionalDescription);

                void startDownloadThread();
                void downloadInSync();

                bool getFileAsList(int queueIndex, TStringList *list);
                bool getFileAsStream(int queueIndex, TMemoryStream *stream);
                bool checkError(int queueIndex);
                String getErrorMessage(int queueIndex);
                String getMainErrorMessage();
                bool isDone(int queueIndex);
                int getProgress(int queueIndex);
                String getDescription(int queueIndex);
                bool hasQueueIndex(int queueIndex);
                void update(Observable *o);

        private:
                HANDLE thread;

                HINTERNET openHandle;
                HINTERNET connectHandle;
                TList *queue;
                bool useSSL;

                String hostURL;
                unsigned short port;

                String mainErrorMessage;

                void exitWithError(String message);
                void cleanUp();
                QueueEntry* getQueueEntry(int queueIndex);
                void closeConnection();
};
//---------------------------------------------------------------------------
#endif
