//---------------------------------------------------------------------------

#ifndef QueryAnswerH
#define QueryAnswerH

#include <vcl.h>

class QueryAnswer {


        public:
                String id;
                int part;
                bool final;
                QueryAnswer();
                ~QueryAnswer();
                void setContent(TStringList *content);
                void readContent(TStringList *out);

        private:
                TStringList *content;
};

//---------------------------------------------------------------------------
#endif
