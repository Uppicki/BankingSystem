
#include "BankService.h"


BankService::BankService()
{
	banks = {};
	clientService = new ClientService();
}


std::vector<BANK_COUNT> BankService::getAllBanks() {
	std::vector<BANK_COUNT> result;
	for (BANK_ACCOUNTS bankPair : this->banks)
	{
		result.push_back(std::make_pair(bankPair.first, bankPair.second.size()));
	}
	return result;
}

BANK_ACCOUNTS BankService::getBankById(int bankId)
{
	return banks[bankId - 1];
}

void BankService::addClient(int bankId, Client* client)
{
	BANK_ACCOUNTS bankPair = getBankPairById(bankId);
	
	bankPair.second.push_back(std::make_pair(client, 0));

	banks[bankId - 1] = bankPair;
}

std::vector<ACCOUNT> BankService::getBankClients(int bankId)
{
	return getBankPairById(bankId).second;
}

std::vector<Bank*> BankService::getClientBanks(int bankId, int clientId)
{
	std::vector<Bank*> clientBanks = {};
	for (int i = 1; i <= banks.size(); i++)
	{
		if (i == bankId) continue;
		if (containClient(i, clientId))
		{
			clientBanks.push_back(banks[i-1].first);
		}
	}
	return clientBanks;
}

void BankService::removeClient(int bankId, int clientId)
{
	BANK_ACCOUNTS bankPair = getBankPairById(bankId);
	std::vector<ACCOUNT> bankClients = bankPair.second;

	for (int i = 0; i < bankPair.second.size(); i++)
		if (bankPair.second[i].first->getId() == (clientId))
			bankPair.second.erase(bankPair.second.begin() + i);
	//banks[bankId - 1] = bankPair;
}

std::vector<Client*> BankService::getAllFreeClients(int bankId)
{
	std::vector<Client*> result;
	std::vector<Client*> allClients = clientService->getAllClients();
	for (Client* client : allClients)
	{
		if (containClient(bankId, client->getId()))
			continue;
		else
			result.push_back(client);
	}
	return result;
}

bool BankService::containClient(int bankId, int clientId)
{
	BANK_ACCOUNTS bankPair = getBankPairById(bankId);
	for (ACCOUNT account : bankPair.second)
		if (account.first->getId() == clientId) 
			return true; 
		else return false;
}



int BankService::getCount()
{
	return this->banks.size();
}

Bank* BankService::createBank(Client* client)
{
	Bank* bank = new Bank(client);
	std::vector<ACCOUNT> clients = {};
	BANK_ACCOUNTS bankPair = std::make_pair(bank, clients);
	banks.push_back(bankPair);

	return bank;
}

Bank* BankService::removeBank(int bankId)
{
	BANK_ACCOUNTS bank = getBankById(bankId);
	banks.erase(banks.begin() + (bankId - 1));
	Client* client;
	for (ACCOUNT c : bank.second)
	{
		client = c.first;
		client->setBalance(client->getBalance() + c.second);
	}
	client = nullptr;
	delete client;
	return bank.first;
}

bool BankService::toUpClientBalance(int bankId, int clientId, double sum)
{
	BANK_ACCOUNTS bankPair = getBankPairById(bankId);
	int indexInAccounts = getACCOUNTByClientId(bankPair.second, clientId);
	ACCOUNT account = bankPair.second[indexInAccounts];
	ACCOUNT newAccount = balanceFromClientToBank(account, sum);
	if (newAccount.first != nullptr)
	{
		banks[bankId - 1].second[indexInAccounts] = newAccount;
		return true;
	}
	else
		return false;
}

bool BankService::withdrawClientBalance(int bankId, int clientId, double sum)
{
	BANK_ACCOUNTS bankPair = getBankPairById(bankId);
	int indexInAccounts = getACCOUNTByClientId(bankPair.second, clientId);
	ACCOUNT account = bankPair.second[indexInAccounts];
	double sumWithPercent = sum * bankPair.first->getProcent();
	ACCOUNT newAccount = balanceFromBankToClient(bankPair.first, account, sum, sumWithPercent);
	if (newAccount.first != nullptr)
	{
		banks[bankId - 1].second[indexInAccounts] = newAccount;
		return true;
	}
	else
		return false;
}

bool BankService::remittanceIntoBanks(int bankIdFrom, int bankIdTo, int clientId, double sum)
{
	BANK_ACCOUNTS bankFrom = getBankPairById(bankIdFrom);
	BANK_ACCOUNTS bankTo = getBankPairById(bankIdTo);

	int indexInAccountsFrom = getACCOUNTByClientId(bankFrom.second, clientId);
	int indexInAccountsTo = getACCOUNTByClientId(bankTo.second, clientId);

	ACCOUNT accountFrom = bankFrom.second[indexInAccountsFrom];
	ACCOUNT accountTo = bankTo.second[indexInAccountsTo];

	if (accountFrom.first->getTypeBool())
		return false;
	else{

	double sumWithPercent = sum * bankFrom.first->getProcent();

	ACCOUNT newAccountFrom = balanceFromBankToClient(bankFrom.first, accountFrom, sum, sumWithPercent);
	
	if (newAccountFrom.first != nullptr)
	{
		ACCOUNT newAccountTo = balanceFromClientToBank(accountTo, sum);
		banks[bankIdFrom - 1].second[indexInAccountsFrom] = newAccountFrom;
		banks[bankIdTo - 1].second[indexInAccountsTo] = newAccountTo;
		return true;
	}
	else
		return false;;
	}
}

int BankService::getACCOUNTByClientId(std::vector<ACCOUNT> clients, int clientId)
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i].first->getId() == clientId) return i;
	}
	return -1;
}

ACCOUNT BankService::balanceFromBankToClient(Bank* bank, ACCOUNT account, double sum, double sumWithProcent)
{
	ACCOUNT result = std::make_pair(nullptr, -1);
	double newBalance = account.second - sumWithProcent;
	if (newBalance >= 0)
	{
		account.first->setBalance(account.first->getBalance() + sum);
		result.first = account.first;
		result.second = newBalance;
		Client* bankMainClient = bank->getMainClient();
		bankMainClient->setBalance(bankMainClient->getBalance() + (sumWithProcent - sum));
	}
	return result;
}

ACCOUNT BankService::balanceFromClientToBank(ACCOUNT account, double sum)
{
	ACCOUNT result = std::make_pair(nullptr, -1);
	double newBalance = account.first->getBalance() - sum;
	if (newBalance >= 0)
	{
		account.first->setBalance(newBalance);
		result.first = account.first;
		result.second = account.second + sum;
	
	}
	return result;
	
}

BANK_ACCOUNTS BankService::getBankPairById(int id)
{
	if (id <= 0 || banks.size() < id)
	{
		std::vector<ACCOUNT> empty = {};
		return std::make_pair(nullptr, empty);
	}
	else {
		return this->banks[id - 1];
	}
	
}
