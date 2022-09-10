#include "ClientService.h"

ClientService::ClientService()
{
	init();
}

void ClientService::init() 
{
	clients = {};
	clients.push_back(new Client(clients.size(), (char*)"Oleg Bors", false, 10000));
	clients.push_back(new Client(clients.size(), (char*)"Vladislav Olegov", false, 50000));
	clients.push_back(new Client(clients.size(), (char*)"Sergey", false, 1000));
	clients.push_back(new Client(clients.size(), (char*)"Bill", false, 25000));
	clients.push_back(new Client(clients.size(), (char*)"Any Bank", true, 10000));
	clients.push_back(new Client(clients.size(), (char*)"Any Bank2", true, 30000));
	clients.push_back(new Client(clients.size(), (char*)"Any Bank4", true, 4500));
	clients.push_back(new Client(clients.size(), (char*)"Any Bank3", true, 50000));
}

int ClientService::getCount()
{
	return clients.size();
}

void ClientService::addClient(char* name, bool type, double balance)
{
	clients.push_back(new Client(clients.size(), name, type, balance));
}

std::vector<Client*> ClientService::getAllClients()
{
	return clients;
}


Client* ClientService::getClient(int id)
{
	return getClientById(id);
}

std::vector<Client*> ClientService::getAllLegalEntityClients()
{
	std::vector<Client*> result;
	for (Client* client : clients)
	{
		if (client->getTypeBool())
			result.push_back(client);
	}
	return result;
}

void ClientService::topUpClientBalance(int clientId, double balance)
{	

}

void withdrawClientBalance(int clientId, double balance){}

Client* ClientService::getClientById(int id)
{
	if (id <= 0 || id > clients.size())
	{
		return nullptr;
	}
	else {
		return clients[id - 1];
	}
	
}

