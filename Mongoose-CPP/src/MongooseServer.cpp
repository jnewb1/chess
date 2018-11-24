#include "MongooseServer.h"

// Callback for MongooseClass, calls the specific event handler on an event.
static void ev_handler_callback(struct mg_connection *nc, int ev, void *ev_data) {
	(static_cast<MongooseClass*>(nc->mgr->user_data))->ev_handler(nc, ev, ev_data);
}

MongooseServer::MongooseServer(int port_in) : MongooseClass()
{

	char port[5];
	sprintf(port, "%ld", port_in);

	nc = mg_bind(&mgr, port, ev_handler_callback);
}


MongooseServer::~MongooseServer()
{
}
