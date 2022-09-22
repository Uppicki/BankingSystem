#pragma once
#include "Account.h"


class Bank
{
private:
	Account* owner;
	std::string name;
	std::vector<Account*> clients;
	double procent;
	double balance;

	int _getIndexOfClient(Account*);

	std::vector<Account*> _getAllClients();
	std::vector<Account*> _getIndividualClients();
	std::vector<Account*> _getLegalClients();
public:
	Bank(Person*, std::string);

	std::vector<Account*> getClients(char); // a - all, i - individual, l - legal
	int getClientsCount();
	bool isEmpty();

	double getProcent();
	double getBalance();
	std::string getName();

	void addAccount(Account*);
	void eraseAccount(Account*);

	void changeBalance(double);
	Account* getOwner();
	void setOwner(Account*);
};