#pragma once
#include "WebClient.h"

class WebAPI : public WebClient
{
public:
	WebAPI();
	~WebAPI();

	json make_api_call(json &call) const;

};