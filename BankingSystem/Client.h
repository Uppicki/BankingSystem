#pragma once
class Client
{
	int id;
	bool type; // 0 - fiz, 1 - yr
	char* name;
	double balance;

public:
	Client(int id, char* name);
	Client(int id, char* name, bool type);
	Client(int id, char* name, bool type, double balance);
	
	int getId();
	char* getName();
	char* getType();
	double getBalance();
	void setBalance(double newBalance);
	bool getTypeBool();
private:
	void init(int id, char* name, bool type, double balance);
};

