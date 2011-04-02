
#define ofpprefix "OM"


#define OFPMONITOR_VERSIO_REPORT "1.3.5"

bool chat_client_connect();
void chat_client_disconnect( );

void chat_client_timercallback(  void * tform1 );

void chat_client_pressedReturnKey(  void * tform1, const char *msg );

