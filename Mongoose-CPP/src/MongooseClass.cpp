#include "MongooseClass.h"




MongooseClass::MongooseClass()
{
	signal(SIGTERM, MongooseClass::signal_handler);
	signal(SIGINT, MongooseClass::signal_handler);

	mg_mgr_init(&mgr, this);



}

void MongooseClass::StartServer()
{
	runthread = std::thread(&MongooseClass::ServerThread, this);
}

void MongooseClass::ServerThread() {
	while (running) {
		mg_mgr_poll(&mgr, 200);
	}
	mg_mgr_free(&mgr);
}



MongooseClass::~MongooseClass()
{
	running = false;
	mg_mgr_free(&mgr);
}

void MongooseClass::signal_handler(int sig_num) {
	signal(sig_num, MongooseClass::signal_handler);  // Reinstantiate signal handler
}

void MongooseClass::ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
	event_handler(nc, ev, ev_data); // Specific server event handler
}