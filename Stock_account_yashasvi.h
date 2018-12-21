#ifndef STOCK_ACCOUNT_YASHASVI_H
#define STOCK_ACCOUNT_YASHASVI_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<string>
#include"Account_yashasvi.h"
#include "Stock_node_yashasvi.h"
using namespace std;

//STL map to hash symbol and stock price 
typedef map<string, double>sym;

class stock_acc :public account
{

public:
	//Default Constructor and Destructor
	stock_acc();
	~stock_acc();

	//Stock Related Functions
	void displayprice();
	virtual void print();
	void buyshares();
	void sellshares();
	void write_bal();
	void buy_update(string, int);
	void sell_update(node*, int);
	bool isEmpty()const;
	
	
	//Portfolio Related Functions
	void write_port_value();
	void write_portfolio();
	void read_port_value();
	void read_portfolio();
	void display_port();
	
	
	void plot_graph();  //plot graph in matlab
	void sort();  //sort the portfolio
	sym select(sym, sym); //Randomly Select from two files
	node *search(string); //Search in portfolio
private:
	node *head;
	node *tail;

	string stock_symbol;
	double stock_price;
	int num_stock;
	int size;
	double max, min, total;

	ofstream stock_hist, bank_hist;
	ifstream read1, read2;
	string l1, l2;
	stringstream s1, s2;
	string time_array[100];
	double port_array[100];
	string symb1;
	double price1;
	int num1, num2;

	sym result1, result2;
};
#endif;
