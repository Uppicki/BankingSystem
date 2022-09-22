#include <iostream>

#include "Service.h"


void printPerson(Person*);
void createNewUser(Service*);

void printAccount(Account*);
void printFullInformationOfBank(Bank*, std::vector<Account*>);
void printInformationOfBank(Bank*);
Bank* createNewBank(Service*);


void printPersons(std::vector<Person*>);
void printBanks(std::vector<Bank*>);


void printPersonActionsBox();
void printBankActionsBox();
void printOperationsBox();

void printMainMenuBox();

void changebalance(Service*, bool);
void transferbalance(Service*);


int main()
{
	int choice = -1;

	Service* service = new Service();




	while (choice != 0)
	{
		printMainMenuBox();

		std::cin >> choice;

		switch (choice)
		{
		case 1:
			printPersonActionsBox();
			std::cin >> choice;
			
			switch (choice)
			{
			case 1:
				printPersons(service->getPersons('a'));
				break;
			case 2:
				printPersons(service->getPersons('i'));
				break;
			case 3:
				printPersons(service->getPersons('l'));
				break;
			case 4:
				printPersons(service->getPersons('w'));
				break;
			case 5:
				printPersons(service->getPersons('o'));
				break;
			case 6:
				createNewUser(service);
				break;
			}
			break;
		case 3:
			printOperationsBox();
			std::cin >> choice;
			switch (choice)
			{
			case 1:
				changebalance(service, true);
				break;
			case 2:
				changebalance(service, false);
				break;
			case 3:
				transferbalance(service);
				break;
			}
			break;
		case 2:
			printBankActionsBox();
			std::cin >> choice;

			int numberOfBank = 0;
			int numberOfPerson = 0;
			int numberOfAccount = 0;
			std::vector<Bank*> allBanks = service->getBanks('a');
			std::vector<Person*> persons;
			std::vector<Account*> accountsOfCurrentBank;
			Bank* currentBank;
			Person* currentPerson;
			Account* currentAccount;
			Account* newAccount;
			
			switch (choice)
			{
			case 1:
				printBanks(allBanks);
				break;
			case 2:
				printBanks(service->getBanks('e'));
				break;
			case 3:
				printBanks(service->getBanks('f'));
				break;
			case 4:
				printBanks(allBanks);
				std::cout << "\nInput number of bank: ";
				std::cin >> numberOfBank;
					
				if (numberOfBank > 0 && numberOfBank <= allBanks.size())
				{
					currentBank = allBanks[numberOfBank - 1];
					accountsOfCurrentBank = currentBank->getClients('a');
					printFullInformationOfBank(currentBank, accountsOfCurrentBank);
				}
				else
					std::cout << "\nIncorected number of bank\n";
					
				break;
			case 5:
				printBanks(allBanks);
				std::cout << "\nInput number of bank: ";
				std::cin >> numberOfBank;

				if (numberOfBank > 0 && numberOfBank <= allBanks.size())
				{
					currentBank = allBanks[numberOfBank - 1];
					accountsOfCurrentBank = currentBank->getClients('i');
					printFullInformationOfBank(currentBank, accountsOfCurrentBank);
				}
				else
					std::cout << "\nIncorected number of bank\n";
				break;
			case 6:
				printBanks(allBanks);
				std::cout << "\nInput number of bank: ";
				std::cin >> numberOfBank;

				if (numberOfBank > 0 && numberOfBank <= allBanks.size())
				{
					currentBank = allBanks[numberOfBank - 1];
					accountsOfCurrentBank = currentBank->getClients('l');
					printFullInformationOfBank(currentBank, accountsOfCurrentBank);
				}
				else
					std::cout << "\nIncorected number of bank\n";
				break;
			case 7:
				currentBank = createNewBank(service);
				if (currentBank != nullptr)
				{
					allBanks = service->getBanks('a');
					printInformationOfBank(currentBank);
				}
				else
					std::cout << "Uncorrected data";
				allBanks = service->getBanks('a');
				break;
			case 8:
				printBanks(allBanks);
				std::cout << "\nInput number of bank: ";
				std::cin >> numberOfBank;

				if (numberOfBank <= 0 || numberOfBank > allBanks.size())
				{
					std::cout << "\nIncorected number of bank\n";
					break;
				}

				currentBank = allBanks[numberOfBank - 1];

				persons = service->getPersons('a');

				printPersons(persons);
				std::cout << "\nInput number of person: ";
				std::cin >> numberOfPerson;

				currentPerson = persons[numberOfPerson-1];

				if (numberOfPerson <= 0 || numberOfPerson > persons.size())
				{
					std::cout << "\nIncorected number of person\n";
					break;
				}


				newAccount = service->addAccount(currentBank, currentPerson);

				break;
			case 9:
				allBanks = service->getBanks('f'); //filled

				printBanks(allBanks);
				std::cout << "\nInput number of bank: ";
				std::cin >> numberOfBank;

				if (numberOfBank <= 0 || numberOfBank > allBanks.size())
				{
					std::cout << "\nIncorected number of bank\n";
					break;
				}

				currentBank = allBanks[numberOfBank - 1];

				accountsOfCurrentBank = currentBank->getClients('a');
				printFullInformationOfBank(currentBank, accountsOfCurrentBank);
				std::cout << "\nInput number of bank: ";
				std::cin >> numberOfAccount;


				if (numberOfAccount <= 0 || numberOfAccount > accountsOfCurrentBank.size())
				{
					std::cout << "\nIncorected number of account\n";
					break;
				}


				currentAccount = accountsOfCurrentBank[numberOfAccount - 1];

				service->deleteAccount(currentAccount);

				allBanks = service->getBanks('a');	
				break;
			case 10:
				printBanks(allBanks);
				std::cout << "\nInput number of bank: ";
				std::cin >> numberOfBank;

				currentBank = allBanks[numberOfBank - 1];

				service->deleteBank(currentBank);

				allBanks = service->getBanks('a');

				break;
			}
			break;
		}

	}

	return 0;
}

void printPersons(std::vector<Person*> persons)
{
	if (persons.size() == 0)
	{
		std::cout << "\nPersons list is empty\n";
	}
	else
	{
		std::cout << "\nCount persons: <" << persons.size() << ">\n";
		int i = 1;
		for (Person* p : persons)
		{
			std::cout << "N " << i++ << "\n";
			printPerson(p);
		}
	}
}

void createNewUser(Service* service)
{
	Person* newPerson;
	std::string name;
	char typeAsChar;
	bool type;
	double balance;

	std::cout << "Input name: ";
	std::cin >> name;
	std::cout << "Input type account (I/L): ";
	std::cin >> typeAsChar;
	std::cout << "Input balance: ";
	std::cin >> balance;

	type = (typeAsChar == 'I');

	if (balance >= 0)
	{
		newPerson = service->createPerson(name, balance, type);
		std::cout << "\nCraeted new Person\n";
		printPerson(newPerson);
	}
	else
		std::cout << "\nUncorrecte data\n";
}


void printPerson(Person* person)
{
	std::cout << "\nName: <" << person->getName() << ">\n";
	std::cout << "Balance: <" << person->getBalance() << ">\n";
	std::cout << "Type: <" << person->getTypeAsString() << ">\n";
	std::cout << "Accounts: <" << person->getAccoutsCount() << ">\n";
}

void printFullInformationOfBank(Bank* bank, std::vector<Account*> accountsOfBank)
{
	std::cout << "\nBank name: <" << bank->getName() << ">\n";
	if (accountsOfBank.size() == 0)
	{
		std::cout << "\Clients list is empty\n";
	}
	else
	{
		std::cout << "\nCount accounts: <" << accountsOfBank.size() << ">\n";
		int i = 1;
		for (Account* account : accountsOfBank)
		{
			std::cout << "N " << i++ << "\n";
			printAccount(account);
		}
	}
}

void printInformationOfBank(Bank* bank)
{
	std::cout << "\nBank name: <" << bank->getName() << ">\n";
	if (bank->getClientsCount() == 0)
	{
		std::cout << "\Clients list is empty\n";
	}
	else
	{
		std::cout << "\nCount accounts: <" << bank->getClientsCount() << ">\n";
	}
}
 
void printBanks(std::vector<Bank*> allBanks)
{
	if (allBanks.size() == 0)
	{
		std::cout << "\Banks list is empty\n";
	}
	else
	{
		std::cout << "\nCount persons: <" << allBanks.size() << ">\n";
		int i = 1;
		for (Bank* bank : allBanks)
		{
			std::cout << "N " << i++ << "\n";
			printInformationOfBank(bank);
		}
	}
}

Bank* createNewBank(Service* service)
{
	std::string name;
	int personNumber = -1;

	std::cout << "Input name: ";
	std::cin >> name;

	std::vector<Person*> persons = service->getPersons('l');
	printPersons(persons);
	std::cout << "Input number: ";
	std::cin >> personNumber;

	
	if (personNumber > 0 && personNumber <= persons.size())
		return service->createBank(name, persons.at(personNumber - 1));
	else
		return nullptr;
}


void printAccount(Account* account)
{
	std::cout << "\nAccountId: <" << account->getId() << ">\n";
	std::cout << "Account Balance: <" << account->getBalance() << ">\n";
	std::cout << "Account Owner: <" << account->getPersonOwner()->getName() << ">\n";
}

void printPersonActionsBox()
{
	std::cout << "\nPerson actions:\n\n";
	std::cout << "1) Show all persons\n";
	std::cout << "2) Show Individual persons\n";
	std::cout << "3) Show Legal Entety persons\n";
	std::cout << "4) Show persons with accounts\n";
	std::cout << "5) Show persons without accounts\n";
	std::cout << "6) Create new person\n";
}
void printBankActionsBox()
{
	std::cout << "\nBank actions:\n\n";
	std::cout << "1) Show all banks\n";
	std::cout << "2) Show empty banks\n";
	std::cout << "3) Show filled banks\n";
	std::cout << "4) Show bank\n";
	std::cout << "5) Show Individual persons of bank\n";
	std::cout << "6) Show Legal Entety persons of bank\n";
	std::cout << "7) Create new bank\n";
	std::cout << "8) Create new account of bank\n";
	std::cout << "9) Remove account of bank\n";
	std::cout << "10) Remove bank\n";
}

void printOperationsBox()
{
	std::cout << "\nAccount actions:\n\n";
	std::cout << "1) To up Balance\n";
	std::cout << "2) Withdraw Balance\n";
	std::cout << "3) Transfer\n";
}


void printMainMenuBox()
{
	std::cout << "\nSelect next action:\n\n";
	std::cout << "1) Client Actions\n";
	std::cout << "2) Bank Actions\n";
	std::cout << "3) Account Actions\n";
	std::cout << "\n0) Exit\n";
}


void changebalance(Service* service, bool toUp)
{
	std::vector<Person*> persons = service->getPersons('w');
	std::vector<Account*> accounts;
	int personId;
	int accountId;
	double sum;

	printPersons(persons);

	std::cout << "\nChange person: ";
	std::cin >> personId;

	if (personId > 0 && personId <= persons.size())
	{
		accounts = service->getAccountsByPerson(persons[personId - 1]);

		for (Account* a : accounts)
		{
			printAccount(a);
		}

		std::cout << "\nSelect Account: ";
		std::cin >> accountId;

		std::cout << "\nInput sum: ";
		std::cin >> sum;


		if (accountId > 0 && accountId <= accounts.size() && sum >=0)
		{
			if ((toUp ? service->toUpBalance(accounts[accountId - 1], sum) : service->withdrawBalance(accounts[accountId - 1], sum)))
			{
				std::cout << "\nOperation complit\n";
				printAccount(accounts[accountId - 1]);
			}
			else {
				std::cout << "\nOperation failed\n";
			}
		}
		else {
			std::cout << "\nUncorrected data\n";
		}
	}

}

void transferbalance(Service* service)
{
	std::vector<Person*> persons = service->getPersons('t');
	std::vector<Account*> accounts;
	Person* person;
	int personId;
	int accountFirstId;
	int accountSecondId;
	double sum;

	printPersons(persons);

	std::cout << "\nChange person: ";
	std::cin >> personId;

	if (personId > 0 && personId <= persons.size())
	{
		person = persons[personId - 1];

		if (person->getType())
		{

			accounts = service->getAccountsByPerson(person);

			for (Account* a : accounts)
			{
				printAccount(a);
			}

			std::cout << "\nSelect Account From: ";
			std::cin >> accountFirstId;

			std::cout << "\nSelect Account To: ";
			std::cin >> accountSecondId;


			std::cout << "\nInput sum: ";
			std::cin >> sum;


			if (accountFirstId > 0 && accountFirstId <= accounts.size() &&
				accountSecondId > 0 && accountFirstId != accountSecondId && sum >= 0)
			{
				sum = service->withdrawBalance(accounts[accountFirstId - 1], sum);
				if (sum)
				{
					service->toUpBalance(accounts[accountSecondId - 1], sum);
				}
				else {
					std::cout << "\nOperation failed\n";
				}
			}
		}
	}
	else {
		std::cout << "\nUncorrected data\n";
	}
}
