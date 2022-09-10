// BankingSystem.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "BankService.h"

void sampleBox();
void clientActionsBox();
void bankActionsBox();
void oneBankOperationsBox();
void twoBankOperationsBox();

void showClientAction1();
void showClientAction2();
void showClientAction3();

void showBankAction1();
void showBankAction2();
void showBankAction3();
void showBankAction4();

void oneBankOperationAction1();
void oneBankOperationAction2();
void oneBankOperationAction3();
void oneBankOperationAction4();

void twoBankOperationAction1();


void printAllBankInformation(std::vector<BANK_COUNT>);
void printAllClientInformationShort(std::vector<Client*>);
void printAccountInformation(std::vector<ACCOUNT>);

BankService* bankService = new BankService();


int clientId;
char name[25];
char letterType;
double balance;

int bankId;
int bankIdTo;

int main()
{
    std::cout << "Hello! It's bank System\n\n";

    int change = -1;




    while (change != 0)
    {
        sampleBox();
        std::cout << "\n\nChoose your next action: ";
        std::cin >> change;

        switch (change)
        {
        case 1: 
            while (change != 9)
            {
                clientActionsBox();
                std::cout << "\n\nChoose your next action: ";
                std::cin >> change;
                switch (change)
                {
                case 1:
                    showClientAction1();
                    break;
                case 2:
                    showClientAction2();
                    break;
                case 3:
                    showClientAction3();
                    break;
                case 9:
                    break;
                case 0:
                    break;
                }
            }
            break;
        case 2:
            while (change != 9)
            {
                bankActionsBox();
                std::cout << "\n\nChoose your next action: ";
                std::cin >> change;
                switch (change)
                {
                case 1:
                    showBankAction1();
                    break;
                case 2:
                    showBankAction2();
                    break;
                case 3:
                    showBankAction3();
                    break;
                case 4:
                    showBankAction4();
                    break;
                case 9:
                    break;
                case 0:
                    break;
                }
            }
            break;
        case 3:
            while (change != 9)
            {
                oneBankOperationsBox();
                std::cout << "\n\nChoose your next action: ";
                std::cin >> change;
                switch (change)
                {
                case 1:
                    oneBankOperationAction1();
                    break;
                case 2:
                    oneBankOperationAction2();
                    break;
                case 3:
                    oneBankOperationAction3();
                    break;
                case 4:
                    oneBankOperationAction4();
                    break;
                case 9:
                    break;
                case 0:
                    break;
                }
            }
            break;
        case 4:
            while (change != 9)
            {
                twoBankOperationsBox();
                std::cout << "\n\nChoose your next action: ";
                std::cin >> change;
                switch (change)
                {
                case 1:
                    twoBankOperationAction1();
                    break;
                case 9:
                    break;
                case 0:
                    break;
                }
            }
            break;
        default:
            break;
        }
    }
       
}

void showClientAction1()
{
    std::vector<Client*> allClients = bankService->clientService->getAllClients();

    for (Client* c : allClients)
    {
        std::cout << "\nClient name: " << c->getName() << "\n";
        std::cout << "Client id: " << c->getId() << "\n";
        std::cout << "Client balance: " << c->getBalance() << "\n";
        std::cout << "Client type: " << c->getType() << "\n";
    }
}
void showClientAction2()
{
    std::cout << "\nInput client ID ( 1 .. " << bankService->clientService->getCount() << " ): ";
    std::cin >> clientId;

    if (clientId >= 1 && clientId <= bankService->clientService->getCount())
    {
        Client* client = bankService->clientService->getClient(clientId);

        std::cout << "\nClient name: " << client->getName() << "\n";
        std::cout << "Client id: " << client->getId() << "\n";
        std::cout << "Client balance: " << client->getBalance() << "\n";
        std::cout << "Client type: " << client->getType() << "\n";
    }
    else {
        std::cout << "Uncorect ID user\n";
    }
}
void showClientAction3()
{
    std::cout << "\nInput name: ";
    std::cin >> name;
    std::cout << "\nSelect type Individual / Legal entity (I/L): ";
    std::cin >> letterType;
    std::cout << "\nInput balance: ";
    std::cin >> balance;

    bankService->clientService->addClient(name, (letterType == 'L'), balance);
}

void showBankAction1()
{
    printAllBankInformation(bankService->getAllBanks());
}
void showBankAction2()
{
    std::cout << "\nInput bank ID ( 1 .. " << bankService->getCount() << " ): ";
    std::cin >> bankId;

    if (bankId >= 1 && bankId <= bankService->getCount())
    {
        BANK_ACCOUNTS bank = bankService->getBankById(bankId);
        std::vector<ACCOUNT> clients = bank.second;

        std::cout << "\nBank name: " << bank.first->getMainClient()->getName() << "\n";
        std::cout << "Bank balance: " << bank.first->getMainClient()->getBalance() << "\n";
        
        for (ACCOUNT account : clients)
        {
            std::cout << "\nClient name: " << account.first->getName() << "\n";
            std::cout << "Client type: " << account.first->getType() << "\n";
            std::cout << "Client bank balance: " << account.second<< "\n";
        }
    }
    else {
        std::cout << "Uncorect ID bank\n";
    }
    
}
void showBankAction3()
{
    std::vector<Client*> clients = bankService->clientService->getAllLegalEntityClients();

    for (Client* client : clients)
    {
        std::cout << "Client id: " << client->getId() << "\n";
        std::cout << "Client name: " << client->getName() << "\n";
    }

    std::cout << "\nChoose bank director: \n";

    std::cin >> clientId;

    bool access = false;

    for (Client* client : clients)
    {
        if (client->getId() == clientId)
        {
            access = true;
            break;
        }
    }

    if (access)
    {
        Bank* bank = bankService->createBank(bankService->clientService->getClient(clientId));
        std::cout << "\nBank was craeted\n";
        std::cout << "\tBank name: \t<" << bank->getMainClient()->getName() << ">\n";
        std::cout << "\tBank balance: \t<" << bank->getMainClient()->getBalance() << ">\n";
    }
    else
    {
        std::cout << "Uncorect ID user\n";
    }
        
}
void showBankAction4()
{
    std::cout << "\nInput bank ID ( 1 .. " << bankService->getCount() << " ): ";
    std::cin >> bankId;

    if (bankId >= 1 && bankId <= bankService->getCount())
    {
        Bank* bank = bankService->removeBank(bankId);
        std::cout << "Bank with name: " << bank->getMainClient()->getName() << " was removed\n";
        delete bank;
    }
    else {
        std::cout << "Uncorect ID bank\n";
    }
}


void oneBankOperationAction1()
{
    printAllBankInformation(bankService->getAllBanks());
    std::cout << "Choose bank Id: ";
    std::cin >> bankId;
    
    std::vector<Client*> freeClients = bankService->getAllFreeClients(bankId);
    printAllClientInformationShort(freeClients);
    std::cout << "Choose client Id: ";
    std::cin >> clientId;

    bool access = false;

    for (Client* client : freeClients)
    {
        if ((client->getId() == clientId) && (bankId >= 1 && bankId<= bankService->getCount()))
        {
            access = true;
            break;
        }
    }
    

    if (access)
    {
        bankService->addClient(bankId, bankService->clientService->getClient(clientId));
    }
    else
    {
        std::cout << "Uncorect ID user\n";
    }

}
void oneBankOperationAction2()
{
    printAllBankInformation(bankService->getAllBanks());
    std::cout << "Choose bank Id: ";
    std::cin >> bankId;
    std::vector<ACCOUNT> accounts = bankService->getBankClients(bankId);
    printAccountInformation(accounts);
    std::cout << "Choose client Id: ";
    std::cin >> clientId;

    bool access = false;

    for (ACCOUNT account : accounts)
    {
        if ((account.first->getId() == clientId) && (bankId >= 1 && bankId <= bankService->getCount()))
        {
            access = true;
            break;
        }
    }

    if (access)
    {
        bankService->removeClient(bankId, clientId);
    }
    else {
        std::cout << "\nUncorrecteId\n";
    }
}
void oneBankOperationAction3()
{
    printAllBankInformation(bankService->getAllBanks());
    std::cout << "Choose bank Id: ";
    std::cin >> bankId;
    std::vector<ACCOUNT> accounts = bankService->getBankClients(bankId);
    printAccountInformation(accounts);
    std::cout << "Choose client Id: ";
    std::cin >> clientId;
    std::cout << "Input to up balance sum: ";
    std::cin >> balance;


    bool access = false;

    for (ACCOUNT account : accounts)
    {
        if ((account.first->getId() == clientId) && (bankId >= 1 && bankId <= bankService->getCount())&& (balance>0))
        {
            access = true;
            break;
        }
    }

    if (access)
    {
        if (bankService->toUpClientBalance(bankId, clientId, balance))
            std::cout << "OK\n";
        else
            std::cout << "Operation ERROR\n";
    }
    else {
        std::cout << "\nUncorrecte Id or balance\n";
    }
}
void oneBankOperationAction4()
{
    printAllBankInformation(bankService->getAllBanks());
    std::cout << "Choose bank Id: ";
    std::cin >> bankId;
    std::vector<ACCOUNT> accounts = bankService->getBankClients(bankId);
    printAccountInformation(accounts);
    std::cout << "Choose client Id: ";
    std::cin >> clientId;
    std::cout << "Input Withdraw sum: ";
    std::cin >> balance;


    bool access = false;

    for (ACCOUNT account : accounts)
    {
        if ((account.first->getId() == clientId) && (bankId >= 1 && bankId <= bankService->getCount()) && (balance > 0))
        {
            access = true;
            break;
        }
    }

    if (access)
    {
        if (bankService->withdrawClientBalance(bankId, clientId, balance))
            std::cout << "OK\n";
        else
            std::cout << "Operation ERROR\n";
    }
    else {
        std::cout << "\nUncorrecte Id or balance\n";
    }
}

void twoBankOperationAction1()
{
    std::vector<BANK_COUNT> allBanks = bankService->getAllBanks();
    printAllBankInformation(allBanks);
    std::cout << "Choose bank Id from: ";
    std::cin >> bankId;
    std::vector<ACCOUNT> accounts = bankService->getBankClients(bankId);
    printAccountInformation(accounts);
    std::cout << "Choose client Id: ";
    std::cin >> clientId;

    bool access = false;

    for (ACCOUNT account : accounts)
    {
        if ((account.first->getId() == clientId) && (bankId >= 1 && bankId <= bankService->getCount()))
        {
            access = true;
            break;
        }
    }

    if (access)
    {
        std::vector<Bank*> banks = bankService->getClientBanks(bankId, clientId);
        for(int i = 1; i <= allBanks.size(); i++)
            for(int j = 1; j <= banks.size(); j++)
                if (allBanks[i-1].first == banks[j-1])
                {
                    std::cout << "\nBank id: <" << i << ">\n";
                    std::cout << "Bank name: <" << banks[j - 1]->getMainClient()->getName() << "\n";
                }
        std::cout << "Choose bank Id to: ";
        std::cin >> bankIdTo;
        std::cout << "Input remittance sum: ";
        std::cin >> balance; 



        if (bankService->remittanceIntoBanks(bankId, bankIdTo, clientId, balance))
            std::cout << "OK\n";
        else
            std::cout<< "Operation ERROR\n";
    }
    else {
        std::cout << "\nUncorrecteId\n";
    }

    
}


void printAllBankInformation(std::vector<BANK_COUNT> banks)
{
    for (BANK_COUNT bank : banks)
    {
        std::cout << "\nBank name: " << bank.first->getMainClient()->getName() << "\n";
        std::cout << "Bank balance: " << bank.first->getMainClient()->getBalance() << "\n";
        std::cout << "Clients: " << bank.second << "\n";
    }
}
void printAllClientInformationShort(std::vector<Client*> clients)
{
    for (Client* c : clients)
    {
        std::cout << "\nClient name: " << c->getName() << "\n";
        std::cout << "Client id: " << c->getId() << "\n";
        std::cout << "Client type: " << c->getType() << "\n";
    }
}
void printAccountInformation(std::vector<ACCOUNT> accounts)
{
    for (ACCOUNT account : accounts)
    {
        std::cout << "\tClient id: <" << account.first->getId() << ">\n";
        std::cout << "\tClient name: <" << account.first->getName() << ">\n";
        std::cout << "\tAccount balance: <" << account.second << ">\n";
    }
}


void clientActionsBox()
{
    std::cout << "\n";

    std::cout << "\n---Clients Actions---\n\n";
    std::cout << "\t1) Show All Clients\n";
    std::cout << "\t2) Show Client by Id\n";
    std::cout << "\t3) Create new Client\n\n";

    std::cout << "\t9)back\n";
    std::cout << "\t0)exit\n";

    std::cout << "\n";
}
void bankActionsBox()
{
    std::cout << "\n";

    std::cout << "\n---Bank Actions---\n\n";
    std::cout << "\t1) Show All Banks\n";
    std::cout << "\t2) Show Bank by Id\n";
    std::cout << "\t3) Create new Bank\n\n";

    std::cout << "\t9)back\n";
    std::cout << "\t0)exit\n";

    std::cout << "\n";
}
void oneBankOperationsBox()
{
    std::cout << "\n";

    std::cout << "\n---One bank operations---\n\n";
    std::cout << "\t1) Add Client\n";
    std::cout << "\t2) Remove Client\n";
    std::cout << "\t3) Top Up balance\n";
    std::cout << "\t4) Withdraw\n\n";

    std::cout << "\t9)back\n";
    std::cout << "\t0)exit\n";

    std::cout << "\n";
}
void twoBankOperationsBox()
{
    std::cout << "\n";

    std::cout << "\n---Two bank operations---\n\n";
    std::cout << "\t1) Remittance\n";

    std::cout << "\t9)back\n";
    std::cout << "\t0)exit\n";

    std::cout << "\n";
}

void sampleBox() 
{
    std::cout << "\n";

    std::cout << "\n1) Clients Actions\n";
    std::cout << "2) Bank Actions\n";
    std::cout << "3) One bank operations\n";
    std::cout << "4) Two bank operations\n\n";

    std::cout << "0)exit\n";

    std::cout << "\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
