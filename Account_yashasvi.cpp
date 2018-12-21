//Class Account Definition

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<string>

#include "Account_yashasvi.h"
using namespace std;

double account::get_cashbal()
{
	return cash_balance;
}

void account::set_cashbal()
{
	int flag = 0; //Flag to check status of file
	ifstream f1;
	ofstream f2;

	f1.open("cash_balance.txt", ios_base::in); //Open a Cash_balance.txt File 

	if (f1.is_open()) //Check if any previous cash balance entry is present
	{
		while (!(f1.eof()))
		{
			flag++;
			break;
		}
	}
	f1.close();

	if (flag == 0)
	{
		double initial_balance = 10000.00;  //Initial Balance is set to $10000
		f2.open("cash_balance.txt", ios_base::out);
		f2 << initial_balance;   //Write Initial Balance as $10000
		f2.close();

		ifstream readbal("cash_balance.txt", ios_base::in); //Read the balance from the file
		readbal >> cash_balance;
		readbal.close();

	}
	else
	{
		ifstream readbal("cash_balance.txt", ios_base::in);  //Read the existing balance from the file
		readbal >> cash_balance;
		readbal.close();
	}
}
void account::print()
{
	string line;
	ifstream read_hist;

	read_hist.open("bank_transaction_history.txt", ios_base::in);
	cout << left << setw(25) << " Event ";
	cout << left << setw(20) << "Amount $";
	cout << left << setw(30) << "Date & Time";
	cout << left << setw(15) << "Balance $" << endl;

	while (!read_hist.eof())
	{
		getline(read_hist, line);
		cout << line << endl;
	}
}