#include "WebServer.h"


WebServer::WebServer(int port, std::string dir):MongooseServer(port)
{
	this->dir = new char[dir.length()+1];
	strcpy_s(this->dir, dir.length()+1, dir.c_str());
	mg_set_protocol_http_websocket(nc);
	s_http_server_opts.document_root = this->dir;
	s_http_server_opts.enable_directory_listing = "yes";

	StartServer();
}


WebServer::~WebServer()
{
}

void WebServer::event_handler(mg_connection * nc, int ev, void * ev_data)
{
	switch (ev) {
		case MG_EV_HTTP_REQUEST: {
			mg_serve_http(nc, (struct http_message *) ev_data, s_http_server_opts);
			break;
		default:
			break;
		}
	}
}

