#include <iostream>

#include "Client.h"

Client::Client(int id, char* name)
{
	Client::Client(id, name, true);
}

Client::Client(int id, char* name, bool type)
{
	Client::Client(id, name, type, 0);
}

Client::Client(int id, char* name, bool type, double balance)
{
	init(id, name, type, balance);
}

void Client::init(int id, char* name, bool type, double balance)
{
	this->id = id;
	this->name = name;
	this->type = type;
	this->balance = balance;
}

int Client::getId()
{
	return this->id+1;
}

char* Client::getName()
{
	return this->name;
}

char* Client::getType()
{
	return  (this->type) ? (char*) "Legal entity" : (char*) "Individual";
}

double Client::getBalance()
{
	return this->balance;
}

void Client::setBalance(double newBalance)
{
	this->balance = newBalance;
}

bool Client::getTypeBool()
{
	return this->type;
}


