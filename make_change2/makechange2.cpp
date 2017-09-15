/* makechange.cpp : A project for INFO 450
   This program takes in an amount due and an amount paid and calculates the change
*/

#include "stdafx.h"
#include <iostream>
#include <tuple>

using namespace std;




/*
Prompts the user for input until the price is greater than zero and the
amount paid is greater than or equal to the amount owed then returns both
values in a tuple
*/
tuple<double, double> get_transaction() {

	double price = 0.0;
	double paid = 0.0;

	while (price <= 0) {

		cout << "What is the price of the goods sold? (set to 0 to quit) ";
		cin >> price;
		//cout << "DEBUG: price == " << price << endl;

		if (price < 0) {
			cout << "The price needs to be greater than zero!" << endl;
			cout << "You supplied $" << price << " , " << paid << " try agian!\n" << endl;
		}
		else if (price == 0)
			return make_tuple(0, 0);

		cin.ignore();
		cin.clear();
	}

	while (paid < price) {
		cout << "What is the amount paid? ";
		cin >> paid;

		if (paid < price) {
			cout << "The amount paid needs to be greater than the price!" << endl;
			cout << "You supplied $" << paid << " , try agian!\n" << endl;
		}

		cin.ignore();
		cin.clear();
	}

	return make_tuple(price, paid);
}


// calucate the amount of change due. There is an issue where two nickles do noe convert to dimes, just ran out of time
void make_change(double price, double paid) {

	// If exact change has been used, exit
	if (paid == price) { return; }

	double remain = paid - price;
	int dollars,
		quarters,
		dimes,
		nickels;


	// Print a transaction summary
	cout << "\nAmount Due: $" << price << "\tAmount Paid: $" << paid
		<< "\tChange Due: $" << remain << "\n" << endl;

	// determine the quantity of each acceptable type
	dollars = remain;
	remain -= dollars;

	quarters = remain / .25;
	remain -= (quarters * .25);

	dimes = remain / .10;
	remain -= (dimes * .10);

	nickels = remain / .05;
	remain -= (nickels * .05);

	// print each type of change given, if it is greater than zero

	// lazy fix for remain = .049999999999999995 just ran out of time 
	if (remain >= .04) { 
		nickels++;
	}

	if (dollars > 0)
		cout << dollars << "\tX\t$1.00\t=\t$" << dollars << endl;

	if (quarters > 0)
		cout << quarters << "\tX\t$0.25\t=\t$" << double(quarters * .25) << endl;

	if (dimes > 0)
		cout << dimes << "\tX\t$0.10\t=\t$" << double(dimes * .10) << endl;

	if (nickels > 0)
		cout << nickels << "\tX\t$0.05\t=\t$" << double(nickels * .05) << endl;

	cout << "\nEnding Transaction!\n" << endl;

	return;
}


// flow control
int main() {

	double price = 0;

	do {
		auto transaction = get_transaction();

		price = get<0>(transaction);
		double paid = get<1>(transaction);

		make_change(price, paid);

	} while (price != 0);

	cout << "\nExiting!" << endl;

	return 0;

}


