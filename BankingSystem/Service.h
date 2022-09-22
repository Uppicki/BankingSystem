#pragma once
#include "Bank.h"


class Service
{
private:
	std::vector<Person*> allPersons;
	std::vector<Account*> allAccounts;
	std::vector<Bank*> allBanks;

	std::vector<Person*> _getAllPersons();
	std::vector<Person*> _getAllIndividualPersons();
	std::vector<Person*> _getAllLegalPersons();
	std::vector<Person*> _getAllWithAccountPersons();
	std::vector<Person*> _getAllWithoutAccountPersons();
	std::vector<Person*> _getAllWithoutBankOwnerPersons();
	std::vector<Person*> _getAllWithTwoAccountsPersons();
	
	std::vector<Bank*> _getAllBanks();
	std::vector<Bank*> _getEmptyBanks();
	std::vector<Bank*> _getFullBanks();

	int _getIndexOfAccount(Account*);

	void _deleteAccount(Account*, bool);
public:
	Service();

	std::vector<Person*> getPersons(char); // a - all, i - ind., l - legal, w - with, o -without, b -bankOwners, t - two accounts
	Person* createPerson(std::string, double, bool);

	std::vector<Bank*> getBanks(char); // a - all, e - empty, f - filled

	Account* addAccount(Bank*, Person*);
	void deleteAccount(Account*);

	std::vector<Account*> getAccountsByPerson(Person*);

	bool toUpBalance(Account*, double);
	double withdrawBalance(Account*, double);

	Bank* createBank(std::string, Person*);
	void deleteBank(Bank*);
};


