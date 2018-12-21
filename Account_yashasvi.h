//Class Account Declaration

#ifndef ACCOUNT_YASHASVI_H
#define ACCOUNT_YASHASVI_H

class account
{
public:

	//Set and Get The Cash Balance
	double get_cashbal();
	void set_cashbal();

	//Virtual Function to print transaction history
	virtual void print();
protected:

	//Store the Cash Balance
	double cash_balance;
};
#endif;
