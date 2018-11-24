#include "WebSocketServer.h"

WebSocketServer::WebSocketServer(int port, std::function<void(std::string)> onmessage) : MongooseServer(port), onmessage(onmessage)
{
	mg_set_protocol_http_websocket(nc);

	StartServer();
}

WebSocketServer::~WebSocketServer()
{
}

// Send message to every websocket client
void WebSocketServer::send_msg(const std::string & msg)
{
	struct mg_connection *c;
	char addr[32];
	mg_sock_addr_to_str(&nc->sa, addr, sizeof(addr),MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);

	for (c = mg_next(nc->mgr, NULL); c != NULL; c = mg_next(nc->mgr, c)) {
		mg_send_websocket_frame(c, WEBSOCKET_OP_TEXT, msg.c_str(), msg.length());
	}
}

// Handle event from Mongoose Server
// Calls onmessage function on the input data
void WebSocketServer::event_handler(mg_connection * nc, int ev, void * ev_data)
{
	switch (ev) {
		case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
			break;
		}
		case MG_EV_WEBSOCKET_FRAME: {
			struct websocket_message *wm = (struct websocket_message *) ev_data;
			onmessage(std::string((char*)wm->data, wm->size));
			break;
		}
		default: {
			break;
		}
	}
}