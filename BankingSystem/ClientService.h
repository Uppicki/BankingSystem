#pragma once
#include <vector>
#include "Client.h"
class ClientService
{
	std::vector<Client*> clients;
public: 
	ClientService();

	void init();

	int getCount();

	std::vector<Client*> getAllLegalEntityClients();

	void addClient(char* name, bool type, double balance);
	Client* getClient(int id);
	std::vector<Client*> getAllClients();
	void topUpClientBalance(int clientId, double balance);
private:
	Client* getClientById(int id);
};

