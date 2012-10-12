//---------------------------------------------------------------------------

#ifndef AudioPositionH
#define AudioPositionH

class AudioPosition {
        public:
                AudioPosition(int position);
	        int getMilliSeconds();
	        int getSeconds();
	        int getMinutes();
                int getPosition();

        private:
                int position;
                int milli;
                int sec;
                int min;

};

//---------------------------------------------------------------------------
#endif
