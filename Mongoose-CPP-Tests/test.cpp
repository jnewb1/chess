#include "pch.h"
#include "WebClient.h"

TEST(WebClientTest, test01_basic) {

	WebClient client;
	std::string response = client.get_request("https://www.google.com", "");
	EXPECT_EQ(response, "Success");
}