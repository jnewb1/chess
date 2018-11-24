#pragma once
#include <string>
#include "MongooseServer.h"

class WebServer : MongooseServer
{
public:
	WebServer(int port, std::string directory);
	~WebServer();


	void event_handler(struct mg_connection *nc, int ev, void *ev_data);

private:
	struct mg_serve_http_opts s_http_server_opts = mg_serve_http_opts();
	char* dir;

};

