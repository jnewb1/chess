#pragma once
#include <string>
#include <functional>
#include "MongooseServer.h"

class WebSocketServer : MongooseServer
{
public:
	WebSocketServer(int port, std::function<void(std::string)>);
	~WebSocketServer();

	void send_msg(const std::string &msg);

	void event_handler(struct mg_connection *nc, int ev, void *ev_data);

private:
	std::function<void(std::string)> onmessage;
};

