#ifndef BANK_ACCOUNT_YASHASVI_H
#define BANK_ACCOUNT_YASHASVI_H
#include"Account_yashasvi.h"
#include<fstream>
#include<iostream>
#include<string>
#include<time.h>
#include<sstream>
#include<map>
#include<iomanip>
using namespace std;


class bank_acc : public account
{
public:

	//Default Contrsuctor and Destructor
	bank_acc();
	~bank_acc();
	
	//Transactions functions
	void view_bal();
	void deposit();
	void withdraw();
	void update_bal();
	
	
	virtual void print();
	//Virtual function to print history

private:

	double cash_deposit;
	double cash_withdraw;

	ofstream bank_history;
	ifstream read_history;
};
#endif;
