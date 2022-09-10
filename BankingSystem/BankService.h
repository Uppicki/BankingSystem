#include "Bank.h"

#include "ClientService.h"

#define ACCOUNT std::pair<Client*, double>
#define BANK_ACCOUNTS std::pair<Bank*, std::vector<ACCOUNT>>

#define BANK_COUNT std::pair<Bank*, int>

class BankService
{
	std::vector<BANK_ACCOUNTS> banks;

public:

	ClientService* clientService;

	BankService();

	std::vector<BANK_COUNT> getAllBanks();
	BANK_ACCOUNTS getBankById(int);



	int getCount();

	Bank* createBank(Client*);
	Bank* removeBank(int);

	void addClient(int bankId, Client* client);
	void removeClient(int bankId, int clientId);
	std::vector<Client*> getAllFreeClients(int);
	std::vector<ACCOUNT> getBankClients(int bankId);
	std::vector<Bank*> getClientBanks(int bankId, int clientId);

	bool toUpClientBalance(int bankId, int clientId, double sum);
	bool withdrawClientBalance(int bankId, int clientId, double sum);
	bool remittanceIntoBanks(int bankIdFrom, int bankIdTo, int clientId, double sum);

private:
	BANK_ACCOUNTS getBankPairById(int id);
	int getACCOUNTByClientId(std::vector<ACCOUNT>, int);
	bool containClient(int, int);
	ACCOUNT balanceFromBankToClient(Bank*, ACCOUNT, double, double);
	ACCOUNT balanceFromClientToBank(ACCOUNT, double);
};

