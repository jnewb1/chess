#include "WebClient.h"

static void ev_handler_callback(struct mg_connection *nc, int ev, void *ev_data) {
	(static_cast<MongooseClass*>(nc->mgr->user_data))->ev_handler(nc, ev, ev_data);
}


WebClient::WebClient()
{

}


WebClient::~WebClient()
{
}

std::string WebClient::get_request(std::string url, std::string headers)
{
	request_complete = false;
	mg_connect_http(&mgr, ev_handler_callback, url.c_str(), headers.c_str(), NULL);
	while (!request_complete)
	{
		mg_mgr_poll(&mgr, 1000);
	}
	return response;
}

std::string WebClient::post_request(std::string url, std::string headers, std::string post_data)
{
	request_complete = false;
	mg_connect_http(&mgr, ev_handler_callback, url.c_str(), headers.c_str(), post_data.c_str());
	while (!request_complete)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return response;
}

void WebClient::event_handler(mg_connection * nc, int ev, void * ev_data)
{
	struct http_message *hm = (struct http_message *) ev_data;

	switch (ev) {
	case MG_EV_CONNECT:
		break;
	case MG_EV_HTTP_REPLY:
		request_complete = true;
		response = hm->body.p;
		break;
	case MG_EV_CLOSE:
		
		break;
	default:
		break;
	}
}


