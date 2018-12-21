#ifndef STOCK_NODE_YASHASVI_H
#define STOCK_NODE_YASHASVI_H
#include<string>
#include<iostream>
#include "Account_yashasvi.h"
using namespace std;
class node
{
	friend class stock_acc;
public:


	node(string &s, int n) :symb(s), number(n)
	{
		this->next = NULL;
		this->previous = NULL;
	}
private:
	
	//Store Symbol and Number of Stocks
	int number;
	string symb;

	//For Double Linked List
	node *next;
	node *previous;
};
#endif;