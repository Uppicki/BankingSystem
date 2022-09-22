#include "Person.h"

Person::Person(std::string name, double balance, bool type)
{
	this->name = name;
	this->balance = balance;
	this->type = type;
	accounts = {};
	banks = {};
}



std::string Person::getName()
{
	return name;
}

double Person::getBalance()
{
	return balance;
}

std::vector<Account*> Person::getAccouts()
{
	return accounts;
}

int Person::getAccoutsCount()
{
	return accounts.size();
}

int Person::getBanksCount()
{
	return banks.size();
}

bool Person::getType()
{
	return type;
}

std::string Person::getTypeAsString()
{
	return (type ? "Individual" : "Legal entity");
}

void Person::setBalance(double sum)
{
	balance = sum;
}

bool Person::changeBalance(double sum)
{
	if ((balance + sum) >= 0)
	{
		balance += sum;
		return true;
	}
	return false;
}

void Person::addAccount(Account* account)
{
	accounts.push_back(account);
}

void Person::eraseAccount(Account* account)
{
	int i = _getIndexOfAccount(account);
	accounts.erase(accounts.begin() + i);
}

void Person::addBankAccount(Account* account)
{
	banks.push_back(account);
}

void Person::eraseBankAccount(Account* account)
{
	int i = _getIndexOfBankAccount(account);
	banks.erase(banks.begin() + i);
}


//private
int Person::_getIndexOfAccount(Account* account)
{
	for (int i = 0; i < accounts.size(); i++)
		if (accounts[i] == account)
			return i;
}
int Person::_getIndexOfBankAccount(Account* account)
{
	for (int i = 0; i < banks.size(); i++)
		if (banks[i] == account)
			return i;
}

