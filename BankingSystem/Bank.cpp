#include "Bank.h"
#include "Client.h"


Bank::Bank(Client* bank)
{
	this->mainClient = bank;
	this->procent = 1.30;
}

double Bank::getProcent()
{
	return this->procent;
}

void Bank::setProcent(double newProsent)
{
	this->procent = newProsent;
}

Client* Bank::getMainClient()
{
	return this->mainClient;
}





