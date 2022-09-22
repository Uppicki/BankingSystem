#include "Account.h"
#include "Bank.h"

Account::Account(Bank* bank, Person* person)
{
	id = _generateId(bank->getName(), person->getName());
	personOwner = person;
	bankOwner = bank;
	balance = 0;
	personOwner->addAccount(this);
}

Account::Account(Bank* bank, std::string name, Person* person)
{
	id = _generateOwnerId(name, person->getName());
	personOwner = person;
	bankOwner = bank;
	balance = 0;
	personOwner->addBankAccount(this);
}

Bank* Account::getBankOwner()
{
	return bankOwner;
}

Person* Account::getPersonOwner()
{
	return personOwner;
}

double Account::getBalance()
{
	return balance;
}

bool Account::changeBalance(double sum)
{
	if ((balance + sum) >= 0)
	{
		balance += sum;
		return true;
	}
	return false;
}

void Account::setPersonOwner(Person* person)
{
	personOwner = person;
}

void Account::setBankOwner(Bank* bank)
{
	bankOwner = bank;
}

std::string Account::getId()
{
	return id;
}

//private
std::string Account::_generateId(std::string bankname, std::string personname) 
{
	return "Account:<Bank:" + bankname + "><Person:" + personname + ">";
}
std::string Account::_generateOwnerId(std::string bankname, std::string personname)
{
	return "AccountOwner:<Bank:" + bankname + "><Owner:" + personname + ">";
}