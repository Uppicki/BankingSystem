#include "Client.h"



#pragma once
class Bank
{
	Client* mainClient;

	double procent;

public:
	Bank(Client* banks);

	double getProcent();
	void setProcent(double newProsent);

	Client* getMainClient();
};

