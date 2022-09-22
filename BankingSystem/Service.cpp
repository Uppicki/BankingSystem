#include "Service.h"
#include <iostream>


Service::Service()
{
	allAccounts = {};
	allPersons = {};
	allBanks = {};
}


std::vector<Person*> Service::getPersons(char type)
{
	std::vector<Person*> result;

	switch (type)
	{
	case 'a':
		result = _getAllPersons();
		break;
	case 'i':
		result = _getAllIndividualPersons();
		break;
	case 'l':
		result = _getAllLegalPersons();
		break;
	case 'w':
		result = _getAllWithAccountPersons();
		break;
	case 'o':
		result = _getAllWithoutAccountPersons();
		break;
	case 'b':
		result = _getAllWithoutBankOwnerPersons();
		break;
	case 't':
		result = _getAllWithoutBankOwnerPersons();
		break;
	}

	return result;
}

Person* Service::createPerson(std::string name, double balance, bool type)
{
	Person* person = new Person(name, balance, type);
	allPersons.push_back(person);
	return person;
}


std::vector<Bank*> Service::getBanks(char type)
{
	std::vector<Bank*> result;

	switch (type)
	{
	case 'a':
		result = _getAllBanks();
		break;
	case 'f':
		result = _getFullBanks();
		break;
	case 'e':
		result = _getEmptyBanks();
		break;
	}

	return result;
}

Account* Service::addAccount(Bank* bank, Person* person)
{
	Account* result = new Account(bank, person);
	allAccounts.push_back(result);
	bank->addAccount(result);
	return result;
}

void Service::deleteAccount(Account* account)
{
	int i = _getIndexOfAccount(account);
	if (i >= 0)
	{
		allAccounts.erase(allAccounts.begin() + i);
		account->getBankOwner()->eraseAccount(account);
		account->getPersonOwner()->eraseAccount(account);
		_deleteAccount(account, true);
	}

}

std::vector<Account*> Service::getAccountsByPerson(Person* person)
{
	std::vector<Account*> result = {};

	for (Person* p : allPersons)
		if (p == person)
			result = p->getAccouts();
	return result;
}

bool Service::toUpBalance(Account* account, double sum)
{
	double newSum = account->getPersonOwner()->getBalance() - sum;

	if (newSum >= 0)
	{
		account->getPersonOwner()->setBalance(newSum);
		account->changeBalance(sum);
		return true;
	}
	return false;
}

double Service::withdrawBalance(Account* account, double sum)
{
	double res = 0;

	if (account->changeBalance(-sum))
	{
		res = (1 - account->getBankOwner()->getProcent()) * sum;
		account->getPersonOwner()->changeBalance(res);
		account->getBankOwner()->changeBalance(sum - res);
	}
	return res;
}

void Service::deleteBank(Bank* bank)
{
	std::vector<Account*> accounts = bank->getClients('a');
	int i = -1;
	for (Account* account : accounts)
	{
		i = _getIndexOfAccount(account);
		allAccounts.erase(allAccounts.begin() + i);
		account->getPersonOwner()->eraseAccount(account);
		_deleteAccount(account, false);
	}
	Account* accountOwner = bank->getOwner();
	i = _getIndexOfAccount(accountOwner);
	allAccounts.erase(allAccounts.begin() + i);
	accountOwner->changeBalance(bank->getBalance());
	_deleteAccount(accountOwner, false);
	delete bank;
}

Bank* Service::createBank(std::string name, Person* person)
{
	Bank* bank = new Bank(person, name);
	std::cout << "||||||||||||||||||||||\n";
	allBanks.push_back(bank);
	return bank;
}


//private

std::vector<Person*> Service::_getAllPersons()
{
	return allPersons;
}
std::vector<Person*> Service::_getAllIndividualPersons()
{
	std::vector<Person*> result = {};
	for (Person* p : allPersons)
		if (p->getType())
			result.push_back(p);
	return result;
}
std::vector<Person*> Service::_getAllLegalPersons()
{
	std::vector<Person*> result = {};
	for (Person* p : allPersons)
		if (!p->getType())
			result.push_back(p);
	return result;
}
std::vector<Person*> Service::_getAllWithAccountPersons()
{
	std::vector<Person*> result = {};
	for (Person* p : allPersons)
		if (p->getAccoutsCount() != 0)
			result.push_back(p);
	return result;
}
std::vector<Person*> Service::_getAllWithoutAccountPersons()
{
	std::vector<Person*> result = {};
	for (Person* p : allPersons)
		if (p->getAccoutsCount() == 0)
			result.push_back(p);
	return result;
}
std::vector<Person*> Service::_getAllWithoutBankOwnerPersons()
{
	std::vector<Person*> result = {};
	for (Person* p : allPersons)
	{
		if (p->getBanksCount() == 0)
			result.push_back(p);
	}
	return result;
}

std::vector<Bank*> Service::_getAllBanks()
{
	return allBanks;
}
std::vector<Bank*> Service::_getEmptyBanks()
{
	std::vector<Bank*> result = {};
	for (Bank* b : allBanks)
		if (b->isEmpty())
			result.push_back(b);
	return result;
}
std::vector<Bank*> Service::_getFullBanks()
{
	std::vector<Bank*> result = {};
	for (Bank* b : allBanks)
		if (!b->isEmpty())
			result.push_back(b);
	return result;
}

void Service::_deleteAccount(Account* account, bool self)
{
	double sum = account->getBalance();
	if (self)
	{
		account->getBankOwner()->changeBalance(sum * account->getBankOwner()->getProcent());
		account->getPersonOwner()->changeBalance(sum * ( 1 - account->getBankOwner()->getProcent()));
	}
	else {
		account->getPersonOwner()->changeBalance(sum);
	}
	account->changeBalance(-sum);
	account->setPersonOwner(nullptr);
	account->setBankOwner(nullptr);

	delete account;
}

int Service::_getIndexOfAccount(Account* account)
{
	for (int i = 0; i < allAccounts.size(); i++)
		if (allAccounts[i] == account)
			return i;
}

std::vector<Person*> Service::_getAllWithTwoAccountsPersons()
{
	std::vector<Person*> result = {};
	for (Person* p : allPersons)
		if (p->getAccoutsCount() == 2)
			result.push_back(p);
	return result;
}
