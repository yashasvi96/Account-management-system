#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
//for matlab
#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )  
#pragma comment( lib, "libeng.lib" )

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
// end


#include<engine.h>
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<sstream>
#include<iomanip>
#include<stdlib.h>
#include<map>
#include"Stock_account_yashasvi.h"
#include"Account_yashasvi.h"
#include "Stock_node_yashasvi.h"



using namespace std;

stock_acc::stock_acc()  //Default Constructor Definition
{
	num1 = 0;
	num2 = 0;
	size = 0;
	set_cashbal();
	cash_balance = get_cashbal();

	read1.open("Result_1.txt");
	read2.open("Result_2.txt");


	//Retrieve and store data into STL map
	if (read1.is_open() && read2.is_open())
	{
		while (!read1.eof() && !read2.eof())
		{
			getline(read1, l1);
			s1 << l1;
			s1 >> symb1 >> price1;
			result1.insert(pair<string, double>(symb1, price1));
			s1.str(" ");
			s1.clear();

			getline(read2, l1);
			s1 << l1;
			s1 >> symb1 >> price1;
			result2.insert(pair<string, double>(symb1, price1));
			s1.str(" ");
			s1.clear();
		}
	}
	read1.close();
	read2.close();

	//Retrieve existing portfolio
	this->read_portfolio();
	this->read_port_value();
}

stock_acc::~stock_acc()  //Default Destructor
{
	
}

sym stock_acc::select(sym file1, sym file2)  //Randomly select between two stock files

{
	srand((unsigned int)time(NULL)); //Current time as seed for random number generator
	int rn;   //Random Number
	rn = (rand() % 2);


	if (rn == 1)  //Return either of the two file choices based on random number
	{
		return file1;
	}
	else
	{
		return file2;
	}

}
void stock_acc::displayprice()  //Display stock price on input symbol
{
	int flag = 0;
	cout << "Enter the stock symbol you want to be displayed" << endl;
	cin >> stock_symbol;

	sym a;
	sym::iterator it1;
	a = select(result1, result2);  //Randomly select file


	for (it1 = a.begin(); it1 != a.end(); it1++)
	{
		if (stock_symbol == it1->first)
		{
			cout << "Symbol";
			cout << setw(15) << "Price/Share$" << endl;
			cout << it1->first;
			cout << setw(15) << it1->second << endl;
			flag = 1;
		}
	}
	if (flag == 0)
	{
		cout << "Please enter a valid symbol,Symbol not found" << endl;
	}
}

//check if list is empty or not
bool stock_acc::isEmpty() const
{
	return(head == 0 && tail == 0);

}


//Sort the list using bubble sort
void stock_acc::sort()
{
	double x=0, y=0;

	if (head != NULL)
	{
		node *current = head;
		node *prev = 0;
		node*temp = NULL;

		sym temp_t;
		int flag = 0;
		for (int i = 0; i < size; i++)
		{
			while (current->next != 0)
			{
				temp_t = select(result1, result2);
				temp = current->next;

				sym::iterator it1;

				for (it1 = temp_t.begin(); it1 != temp_t.end(); it1++)
				{
					if (current->symb == it1->first)
					{
						x = it1->second;

					}
					if (temp->symb == it1->first)
					{
						y = it1->second;
					}
				}
				//comparing stock value
				if ((current->number)*x < (temp->number)*y)
				{
					temp->previous = current->previous;
					current->previous = temp;
					current->next = temp->next;

					flag = 1;
					if (current->next != NULL)
					{
						current->next->previous = current;
					}
					temp->next = current;
					if (prev != 0)
					{
						prev->next = temp;
					}
					if (head == current)
					{
						head = temp;
					}
					if (current->next == 0)
					{
						tail = current;
					}

				}
				else
				{
					prev = current;
					current = current->next;
				}



			}
			if (flag == 0)
			{
				break;
			}
			else
			{
				prev = NULL;
				current = head;
				flag = 0;
			}
		}
	}
}

void stock_acc::buyshares()  // Buy Shares
{
	cout << "Enter the stock symbol you want to buy" << endl;
	cin >> stock_symbol;

	int flag = 0;
	sym a;

	a = select(result1, result2);
	sym::iterator it1;

	for (it1 = a.begin(); it1 != a.end(); it1++)
	{
		if (stock_symbol == it1->first)
		{
			flag = 1;
			stock_price = it1->second;
		}
	}
	if (flag == 0)
	{
		cout << "Symbol not found,please enter a valid symbol" << endl;
		return;
	}
	cout << "Enter the number of stocks you are willing to buy" << endl;
	cin >> num_stock;
	cout << "Enter the maximum price you are willing to pay" << endl;
	cin >> max;

	if (max > stock_price)   //Check if Stock price is less than max amount
	{
		total = num_stock * stock_price;
	}
	else
	{
		cout << "Cannot process your request,Stock price is higher than the amount you are willing to pay" << endl;
		return;
	}

	set_cashbal();  //Get recent cash balance
	cash_balance = get_cashbal();

	if (total <= cash_balance) //check if sufficient funds are available
	{
		cash_balance = cash_balance - total;
		write_bal();
		cout << "Transcation complete.You have purchased " << num_stock << " shares of " << stock_symbol << " for amount $" << total << endl;

		//get transaction time
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
		string str(buffer);

		stock_hist.open("stock_transaction_history.txt", ios::app);
		stock_hist << left << setw(10) << "Buy";
		stock_hist << left << setw(15) << stock_symbol;
		stock_hist << left << setw(15) << num_stock;
		stock_hist << left << setw(20) << stock_price;
		stock_hist << left << setw(20) << total;
		stock_hist << left << setw(25) << str << endl;
		stock_hist.close();

		//record bank transaction
		bank_hist.open("bank_transaction_history.txt", ios::app);
		bank_hist << left << setw(25) << "withdraw(stock)";
		bank_hist << left << setw(20) << total;
		bank_hist << left << setw(30) << str;
		bank_hist << left << setw(10) << cash_balance << endl;
		bank_hist.close();
	}
	else
	{
		cout << "Invalid Transaction! Insufficient Balance\n";
		return;
	}

	//update the list
	buy_update(stock_symbol, num_stock);
	sort();
	write_port_value();
	write_portfolio();



}

void stock_acc::write_bal()
{
	ofstream myfile;
	myfile.open("cash_balance.txt", ios_base::out);
	myfile << endl << cash_balance;
	myfile.close();
}

//Search if stock exists in the portfolio
node * stock_acc::search(string a)
{
	node *temp = head;

	while (temp != NULL)
	{
		if (temp->symb == a)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;   //Return NULL if symbol not found
}
void stock_acc::buy_update(string s, int n)  //Update portfolio after buying stock

{
	node *temp;
	temp = new node(s, n);
	node *find = search(s);  //Check if Stock Symbol is in portfolio list

	if (find == NULL)  //Symbol not found
	{
		if (head == NULL && tail == NULL)  //if list is empty
		{
			temp->previous = NULL;
			temp->next = NULL;

			head = temp;
			tail = temp;

		}
		else   //add to end of list
		{
			node *temp1 = tail;
			tail->next = temp;
			tail = temp;
			temp->previous = temp1;


		}
		size++;
	}
	else   //Increse number of stock if symbol exists
	{
		find->number = temp->number + find->number;
	}
	sort();
}
void stock_acc::sellshares()  //sell shares
{
	int flag = 0;
	node *temp = NULL;
	cout << "Enter the stock symbol you want to sell" << endl;
	cin >> stock_symbol;
	
	temp = search(stock_symbol);  //search for the stock symbol
	if (temp != NULL)
	{
		flag = 1;  //reset the flag
	}
	if (flag == 0)  //invalid symbol
	{
		cout << "Symbol not found" << endl;
		return;
	}
	cout << "Enter the number of shares you want to sell" << endl;
	cin >> num_stock;

	if (num_stock > temp->number)
	{
		cout << "Number of shares is out of range" << endl;
		return;
	}

	cout << "Enter the minimum amoount you want to sell per share" << endl;
	cin >> min;

	sym a;

	a = select(result1, result2);
	sym::iterator it1;

	for (it1 = a.begin(); it1 != a.end(); it1++)
	{
		if (stock_symbol == it1->first)
		{
			stock_price = it1->second;
		}
	}

	if (stock_price < min)
	{
		cout << "Transaction failed! Sell price is high" << endl;
		return;
	}
	set_cashbal();
	cash_balance = get_cashbal();
	total = num_stock * stock_price;
	cash_balance = cash_balance + total;
	write_bal();

	cout << "Transaction complete! You have sold" << num_stock << " Share of " << stock_symbol << "for amount $" << total << endl;

	//get transaction time
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	string str(buffer);

	//record stock transaction
	stock_hist.open("stock_transaction_history.txt", ios::app);
	stock_hist << left << setw(10) << "Sell";
	stock_hist << left << setw(15) << stock_symbol;
	stock_hist << left << setw(15) << num_stock;
	stock_hist << left << setw(20) << stock_price;
	stock_hist << left << setw(20) << total;
	stock_hist << left << setw(25) << str << endl;
	stock_hist.close();

	//record bank transaction
	bank_hist.open("bank_transaction_history.txt", ios::app);
	bank_hist << left << setw(25) << "deposit(stock)";
	bank_hist << left << setw(20) << total;
	bank_hist << left << setw(30) << str;
	bank_hist << left << setw(10) << cash_balance << endl;
	bank_hist.close();

	sell_update(temp, num_stock);
	sort();
	write_port_value();
	write_portfolio();

}

void stock_acc::sell_update(node *f, int n)  //Update portfolio after selling shares
{
	f->number = f->number - n;  //Subtract the shares

	if (f->number == 0) //Delete node if number of shares is zero
	{
		if (f == head)
		{
			if (f == tail)  //If its the only node in list
			{
				head = NULL;
				tail = NULL;
				delete f;
				size--;
				return;
			}

			node *temp = f->next;
			head = f->next;
			temp->previous = NULL;
			delete f;
			size--;
			return;
		}

		else if (f == tail)
		{
			if (f == head)  //If its the only node in list
			{
				head = NULL;
				tail = NULL;
				delete f;
				size--;
				return;

			}
			node *temp1 = f->previous;
			tail = f->previous;
			temp1->next = NULL;
			delete f;
			size--;
			return;
		}
		else
		{
			node *temp2 = f->previous;
			node *temp3 = f->next;
			temp2->next = f->next;
			temp3->previous = f->previous;
			delete f;
			size--;
			return;
		}
	}
}

void stock_acc::display_port()   //Display Portfolio
{
	set_cashbal();
	cash_balance = get_cashbal();
	sort();

	node *temp = head;

	sym a;
	sym::iterator it1;
	a = select(result1, result2);
	double pr, val, port_val;
	double stock_val = 0;

	if (size > 0)
	{
		cout << endl << left << setw(20) << "Symbol";
		cout << left << setw(20) << "Shares";
		cout << left << setw(20) << "Price/Share($)";
		cout << left << setw(20) << "Total Value($)" << endl;
	}

	while (temp != NULL)
	{
		for (it1 = a.begin(); it1 != a.end(); it1++)
		{
			if (temp->symb == it1->first)
			{
				pr = it1->second;
				val = temp->number*pr;

				cout << left << setw(20) << temp->symb;
				cout << left << setw(20) << temp->number;
				cout << left << setw(20) << pr;
				cout << left << setw(20) << val << endl;
				stock_val = stock_val + val;
			}
		}
		temp = temp->next;
	}

	if (size > 0)
	{
		cout << " Cash : $" << cash_balance << endl;
		cout << " Stock : $" << stock_val << endl;
		port_val = cash_balance + stock_val;
		cout << "Total Portfolio value : $" << port_val << endl;
	}
	else if (size == 0)
	{
		port_val = cash_balance;
		cout << " Total portfolio value : $" << port_val << endl;
		cout << " You have not bought  sharesin the current session" << endl;
	}

}

void stock_acc::write_portfolio()
{
	sort();
	node *temp = head;
	ofstream myfile;

	myfile.open("portfolio.txt", ios_base::out);

	while (temp != NULL)
	{
		myfile << temp->symb << "\t" << temp->number << endl;
		temp = temp->next;
	}
	myfile.close();
}

void stock_acc::write_port_value()
{
	node *temp = head;
	double cost = 0.0;
	double total = 0.0;
	double port_val = 0.0;
	ofstream write;

	sym a;
	a = select(result1, result2);
	sym::iterator it1;
	while (temp != NULL)
	{
		for (it1 = a.begin(); it1 != a.end(); it1++)
		{
			if (temp->symb == it1->first)
			{
				cost = it1->second;;
				total = total + temp->number*cost;
			}
		}
		temp = temp->next;
	}

	set_cashbal();
	cash_balance = get_cashbal();
	port_val = total + cash_balance;

	if (num1 < 100)
	{
		port_array[num1] = port_val;
	}

	//generating the current date and time 
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	std::string str(buffer);

	if (num2 < 100)
	{
		time_array[num2] = str;			//store time in time array
	}

	if (size == 0)
	{
		port_val = cash_balance;
	}

	write.open("portfoliovalue.txt", ios::app);
	write << port_val << "  " << str << endl;
	write.close();
	num1++;
	num2++;

}

void stock_acc::read_port_value()
{
	string t;
	read1.open("portfolio.txt", ios_base::in);
	while (!read1.eof())
	{
		getline(read1, l1);
		s1 << l1;
		s1 >> port_array[num1] >> time_array[num2] >> t;

		if (time_array[num2] == "")
		{
			continue;
		}
		else
		{
			time_array[num1].append(" ");
			time_array[num1].append(t);
		}
		num1++;
		num2++;
		s1.clear();
	}
	read1.close();

}

void stock_acc::read_portfolio()
{
	string p;
	int flag = 0;
	int n;
	sym temp;
	string temp_symb;
	int temp_share;
	ifstream myfile;
	myfile.open("portfolio.txt", ios_base::in);
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, l1);
			s1 << l1;
			s1 >> temp_symb >> temp_share;
			temp.insert(pair<string, int>(temp_symb, temp_share));
			s1.clear();
			flag = 1;
		}
	}

	myfile.close();

	if (flag == 1)
	{
		for (sym::iterator it1 = temp.begin(); it1 != temp.end(); it1++)
		{
			p = it1->first;
			n = it1->second;

			buy_update(p, n);
		}
	}
}

void stock_acc::print()  //Print stock transaction history
{
	ifstream myfile;
	myfile.open("stock_transaction_history.txt", ios::app);

	cout << left << setw(10) << "Event";
	cout << left << setw(15) << "CompSymbol";
	cout << left << setw(15) << "Shares";
	cout << left << setw(20) << "Price/Share";
	cout << left << setw(20) << "Value($)";
	cout << left << setw(25) << "Date & Time" << endl;

	while (!myfile.eof())
	{
		getline(myfile, l1);
		cout << l1 << endl;
	}
}





//Plot graph using MATLAB
void stock_acc::plot_graph()
{
	Engine *m_pEngine;

	m_pEngine = engOpen(NULL);
	if (m_pEngine == NULL) {
		std::cout << "Error: Failed to open Matlab." << std::endl;
	}
	else {
		// Open portfolio value history file.
		std::ifstream portfolio_value_history_file;
		portfolio_value_history_file.open("portfoliovalue.txt");
		std::string line;

		// Get count for dynamic array size.
		unsigned int line_count = 0;
		while (getline(portfolio_value_history_file, line)) {
			line_count++;
		}

		// Build dyanmic arrays based on line count from portfolio value history file.
		// Additional index for current value.
		double *x_labels = new double[line_count + 1];
		double *plot_values = new double[line_count + 1];

		double date_temp, stock_value_temp, temp_time;
		int iter = 0;

		portfolio_value_history_file.clear();
		portfolio_value_history_file.seekg(0, std::ios::beg);

		while (getline(portfolio_value_history_file, line)) {
			std::istringstream ss(line);
			ss >> stock_value_temp >> date_temp >> temp_time;
			*(x_labels + iter) = date_temp;
			*(plot_values + iter) = stock_value_temp;
			iter++;
		}



		mxArray* LABELS = mxCreateDoubleMatrix(iter, 1, mxREAL);
		std::memcpy((void *)mxGetPr(LABELS), (void *)x_labels, sizeof(double) * iter);
		engPutVariable(m_pEngine, "plot_values_x", LABELS);

		// Enter y_labels to Matlab variable.
		mxArray* PLOT = mxCreateDoubleMatrix(iter, 1, mxREAL);
		std::memcpy((void *)mxGetPr(PLOT), (void *)plot_values, sizeof(double) * iter);
		engPutVariable(m_pEngine, "plot_values_y", PLOT);

		// Open Matlab figure.
		engEvalString(m_pEngine, "figure();");
		// Plot portfolio values trend.
		engEvalString(m_pEngine, "plot(plot_values_x, plot_values_y, 'g'), grid minor, title('Portfolio Value Trend')");

		// Format x-axis to datetime.
		engEvalString(m_pEngine, "xlabel('Date '); datetick('x','yyyy-mm-dd ',); xtickangle(45)");
		// Format y-axis to zero min and US dollar units.
		engEvalString(m_pEngine, "ylim([0 inf]); ylabel('Portfolio Value'); ytickformat('usd')");
		// Remove space between axis and plotted line.
		engEvalString(m_pEngine, "axis tight");

		system("pause");

		// Close Matlab engine.
		engEvalString(m_pEngine, "close;");

		// Free memory used to build dynamic arrays.
		delete[] x_labels;
		delete[] plot_values;
	}


}

	




			