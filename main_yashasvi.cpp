

#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<utility>

#include "stock_node_yashasvi.h"
#include "Account_yashasvi.h"
#include "Bank_account_yashasvi.h"
#include "Stock_account_yashasvi.h"

using namespace std;

int main()
{
	node *node = NULL;
	bank_acc B;
	stock_acc S;

	int ch1 = 0;
	int ch2 = 0;
	int ch3 = 0;

	cout << "Welcome to Account Management System"<<endl;

	while (ch1 != 3)
	{
		cout << "\n1. Stock Portfolio Account"
			<< "\n2. Bank Account"
			<< "\n3. Exit"
			<< "\nSelect Account or exit(3) : ";
		cin >> ch1;

		switch (ch1)
		{
		case 1:
			while (ch2 != 7)// Stock Account Options displaying till it returns to previous menu
			{
				cout << "\nStock Portfolio account"
					<< "\n1. Display the price for a Stock Symbol"
					<< "\n2. Display Current Portfolio"
					<< "\n3. Buy Shares"
					<< "\n4. Sell Shares"
					<< "\n5. View a Graph for the Portfolio Value"
					<< "\n6. View Transaction History"
					<< "\n7. Return to the Previous Menu";
				cout << "\nEnter Your Choice : ";
				cin >> ch2;
				switch (ch2)
				{
				case 1:
					S.displayprice();
					break;
				case 2:
					S.display_port();
					break;
				case 3:
					S.buyshares();
					break;
				case 4:
					S.sellshares();
					break;
				case 5:
					cout << "Display graph here\n";
					S.plot_graph();
					break;
				case 6:
					S.print();
					break;

				case 7:
					break;
				default:
					cout << "\nPlease Enter a Valid Option!";
				}
			}
			ch2 = 0;
			break;
		case 2:

			while (ch3 != 5)
			{
				cout << "\nBank Account"
					<< "\n1. View Account Balance"
					<< "\n2. Deposit Money"
					<< "\n3. Withdraw Money"
					<< "\n4. Print History"
					<< "\n5. Return to Previous Menu";
				cout << "\nPlease Enter Your Choice : ";
				cin >> ch3;
				switch (ch3)
				{
				case 1:
					B.view_bal();
					break;
				case 2:
					B.deposit();
					S.write_port_value();
					break;
				case 3:
					B.withdraw();
					S.write_port_value();
					break;
				case 4:
					B.print();
					break;
				case 5:
					break;
				default:
					cout << "\nPlease Enter a Valid Option!";
				}
			}
			ch3 = 0;
			break;

		case 3:
			S.write_portfolio();
			break;
		default:
			cout << "\nPlease Enter a Valid Option!";
		}
	}
	return 0;
}