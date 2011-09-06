
#define ofpprefix "OM"

void chat_client_connect();
void chat_client_disconnect( );

void chat_client_timercallback(  void * tform1 );

void chat_client_pressedReturnKey(void *t, const char *receiver, const char *msg);
