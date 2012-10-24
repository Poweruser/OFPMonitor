//---------------------------------------------------------------------------

#ifndef ObserverH
#define ObserverH

#include <vcl.h>

class Observable;

class Observer {
        public:
                virtual void update(Observable *o) = 0;
};

class Observable {
        private:
                Observer *observer;

        public:
                Observable();
                void SetObserver(Observer *o);
                void NotifyObserver();
};

//---------------------------------------------------------------------------
#endif
