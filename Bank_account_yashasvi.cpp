#include<iostream>
#include "Bank_account_yashasvi.h"
#include<fstream>
#include<string>
#include<time.h>
#include<sstream>
#include<map>
#include<iomanip>

using namespace std;

//Default Constructor Definition
bank_acc::bank_acc()
{
	cash_deposit = 0;
	cash_withdraw = 0;
	set_cashbal();
	cash_balance = get_cashbal();

}


//Default Destructor Definition
bank_acc::~bank_acc()
{

}
void bank_acc::update_bal()  //Write Balance into account
{
	ofstream f;
	f.open("cash_balance.txt", ios_base::out);
	f << endl << cash_balance;
	f.close();
}

void bank_acc::view_bal()  //View Account Balance
{
	set_cashbal();
	cash_balance = get_cashbal();
	cout << "You have $" << cash_balance << " in your account" << endl;
}
void bank_acc::deposit()  //Deposit money into account
{
	cout << "Enter the amount you want to deposit " << endl;
	cin >> cash_deposit;

	while (cash_deposit < 0)  //Valid Deposit check
	{
		cout << "Please enter a valid amount(>0)" << endl;
		cin >> cash_deposit;
	}

	//Update Cash Balance
	set_cashbal();  
	cash_balance = get_cashbal();
	cash_balance = cash_balance + cash_deposit;
	update_bal();
	cout << "Amount" << cash_deposit << " is deposited to your account" << endl;

	//Get current time and date
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	string str(buffer);

	//Store transaction history
	bank_history.open("bank_transaction_history.txt", ios::app);
	bank_history << left << setw(25) << "Deposit";
	bank_history << left << setw(20) << cash_deposit;
	bank_history << left << setw(30) << str;
	bank_history << left << setw(10) << cash_balance << endl;
	bank_history.close();

}

void bank_acc::withdraw() //Withraw money from account
{
	cout << "Enter the amount you want to withdraw" << endl;
	cin >> cash_withdraw;

	while (cash_withdraw < 0)
	{
		cout << "Please enter a valid amount" << endl;
		cin >> cash_withdraw;
	}
	set_cashbal();
	cash_balance = get_cashbal();
	if (cash_balance > 0)
	{
		if (cash_withdraw <= cash_balance)
		{
			cash_balance = cash_balance - cash_withdraw;  //Update and write cash balance
			cout << "You have sucessfully withdrwan $" << cash_withdraw << endl;
			update_bal();

			time_t rawtime;   //Get current time and date
			struct tm timeinfo;
			char buffer[80];
			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);
			strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
			string str(buffer);

			//Store transaction history
			bank_history.open("bank_transaction_history.txt", ios::app);
			bank_history << left << setw(25) << "Withdraw";
			bank_history << left << setw(20) << cash_withdraw;
			bank_history << left << setw(30) << str;
			bank_history << left << setw(10) << cash_balance << endl;
			bank_history.close();

		}
		else
		{
			cout << "Transaction failed:You have Insufficient funds in your account" << endl;
		}
	}
	else
	{
		cout << "Transaction failed: Account balance is zero" << endl;
	}

}

void bank_acc::print()  //print history
{
	string line;
	ifstream read_history;
	read_history.open("bank_transaction_history.txt", ios_base::app);
	cout << left << setw(25) << " Event ";
	cout << left << setw(20) << "Amount $";
	cout << left << setw(30) << "Date & Time";
	cout << left << setw(15) << "Balance $" << endl;

	while (!read_history.eof())
	{
		getline(read_history, line);
		cout << line << endl;
	}
	
}