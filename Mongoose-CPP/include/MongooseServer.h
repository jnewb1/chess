#pragma once
#include "MongooseClass.h"



class MongooseServer : public MongooseClass
{
public:
	MongooseServer(int port_in);
	~MongooseServer();
};

