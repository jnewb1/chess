#pragma once

#include "mongoose.h"
#include <thread>

class MongooseClass
{
public:
	MongooseClass();
	~MongooseClass();

	void ev_handler(struct mg_connection *nc, int ev, void *ev_data);
	void StartServer();
private:
	sig_atomic_t s_signal_received = 0;
	struct mg_serve_http_opts s_http_server_opts;

	static void signal_handler(int sig_num);
	int is_websocket(const struct mg_connection *nc);
	void broadcast(struct mg_connection *nc, const struct mg_str msg);

	//Handler for specific server type
	virtual void event_handler(struct mg_connection *nc, int ev, void *ev_data) = 0;

	void ServerThread();


protected:
	std::thread runthread;
	struct mg_mgr mgr;
	struct mg_connection *nc;
	bool running = true;
};

