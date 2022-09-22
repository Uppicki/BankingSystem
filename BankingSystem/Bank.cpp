
#include "Bank.h"

Bank::Bank(Person* personOwner, std::string name)
{
	this->name = name;
	owner = new Account(this, name, personOwner);
	clients = {};
	procent = 0.3;
	balance = 0;
}

std::vector<Account*> Bank::getClients(char type)
{
	std::vector<Account*> result;

	switch (type)
	{
	case 'a':
		result = _getAllClients();
		break;
	case 'i':
		result = _getIndividualClients();
		break;
	case 'l':
		result = _getLegalClients();
		break;
	}

	return result;
}

int Bank::getClientsCount()
{
	return clients.size();
}

bool Bank::isEmpty() 
{
	return (clients.size() == 0);
}

double Bank::getProcent()
{
	return procent;
}

double Bank::getBalance()
{
	return balance;
}

std::string Bank::getName()
{
	return name;
}

void Bank::addAccount(Account* account)
{
	clients.push_back(account);
}

void Bank::eraseAccount(Account* account)
{
	int i = _getIndexOfClient(account);
	clients.erase(clients.begin() + i);
}

void Bank::changeBalance(double sum)
{
	if ((balance + sum) >= 0)
		balance += sum;
}

Account* Bank::getOwner()
{
	return owner;
}

void Bank::setOwner(Account* account)
{
	owner = account;
}


//private
int Bank::_getIndexOfClient(Account* account)
{
	for (int i = 0; i < clients.size(); i++)
		if (clients[i] == account)
			return i;
}

std::vector<Account*> Bank::_getAllClients()
{
	return clients;
}
std::vector<Account*> Bank::_getIndividualClients() 
{
	std::vector<Account*> result = {};
	for (Account* client : clients)
		if (client->getPersonOwner()->getType())
			result.push_back(client);
	return result;
}
std::vector<Account*> Bank::_getLegalClients()
{
	std::vector<Account*> result = {};
	for (Account* client : clients)
		if (!client->getPersonOwner()->getType())
			result.push_back(client);
	return result;
}

