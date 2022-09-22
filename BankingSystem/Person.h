#pragma once
#include <vector>
#include <string>

class Account;

class Person
{
private:
	std::string name;
	double balance;
	std::vector<Account*> accounts;
	std::vector<Account*> banks;
	bool type;

	int _getIndexOfAccount(Account*);
	int _getIndexOfBankAccount(Account*);
public:	
	Person(std::string, double, bool);

	std::string getName();
	double getBalance();
	std::vector<Account* > getAccouts();
	int getAccoutsCount();
	int getBanksCount();
	bool getType();
	std::string getTypeAsString();

	void setBalance(double);
	bool changeBalance(double);
	void addAccount(Account*);
	void eraseAccount(Account*);
	void addBankAccount(Account*);
	void eraseBankAccount(Account*);
};

