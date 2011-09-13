//---------------------------------------------------------------------------

#ifndef QueryAnswerH
#define QueryAnswerH

#include <vcl.h>
#include <list.h>

class QueryAnswer {
        public:
                String id;
                String part;
                bool final;
                list<String> content;

                QueryAnswer();

                void clear();
};

//---------------------------------------------------------------------------
#endif
