#pragma once
#include "Person.h"

class Bank;


class Account
{
private:
	Person* personOwner;
	Bank* bankOwner;
	double balance;
	std::string id;

	std::string _generateId(std::string, std::string);
	std::string _generateOwnerId(std::string, std::string);
public:
	Account(Bank*, Person*);
	Account(Bank*, std::string, Person*);

	Bank* getBankOwner();
	Person* getPersonOwner();

	double getBalance();
	bool changeBalance(double);

	void setPersonOwner(Person*);
	void setBankOwner(Bank*);

	std::string getId();
};