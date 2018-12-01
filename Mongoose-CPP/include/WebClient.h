#pragma once
#include "MongooseClass.h"

class WebClient : MongooseClass
{
public:
	WebClient();
	~WebClient();
	std::string get_request(std::string url, std::string headers);
	std::string post_request(std::string url, std::string headers, std::string post_data);

	void event_handler(struct mg_connection *nc, int ev, void *ev_data);
private:
	bool request_complete = false;
	std::string response;
};

