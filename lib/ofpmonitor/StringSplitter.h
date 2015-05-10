//---------------------------------------------------------------------------

#ifndef StringSplitterH
#define StringSplitterH

#include <vcl.h>

class StringSplitter {
        public:
                StringSplitter(String str);
                void setKeepEmptyParts(bool keep);
                TStringList* split(String splitter);
        private:
                String str;
                bool keep;
};




//---------------------------------------------------------------------------
#endif
