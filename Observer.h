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
                TList *observers;

        public:
                Observable();
                ~Observable();
                void SetObserver(Observer *o);
                void RemoveObserver(Observer *o);
                void NotifyObserver();
};

//---------------------------------------------------------------------------
#endif
