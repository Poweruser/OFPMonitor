//---------------------------------------------------------------------------

#ifndef HttpsDownloaderH
#define HttpsDownloaderH
#include <vcl.h>
#include "Observer.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "IdIOHandler.hpp"
#include "IdIOHandlerSocket.hpp"
#include "IdIOHandlerStack.hpp"
#include "IdSSL.hpp"
#include <IdSSLOpenSSL.hpp>

class HttpsDownloader : public Observable {

        public:
                TIdHTTP *http;
                TMemoryStream *ms;
                String url;
                bool error;
                TStringList *file;

                HttpsDownloader(String url);
                ~HttpsDownloader();
                void start();
                void getFile(TStringList *file);
                bool checkError();
                void closeOpenConnections();


        private:

                HANDLE thread;

                TIdSSLIOHandlerSocketOpenSSL *ssl;


};
//---------------------------------------------------------------------------
#endif
