#include "Controller.h"
#include "InputList.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	string clerk; string data;
	Controller controller;
	int numb_of_clerk;
	clerk = "";
	numb_of_clerk = 0;
	if (argc > 1)
	{
		stringstream ss(argv[1]);
		ss >> clerk;
		numb_of_clerk = stoi(clerk.c_str());
		controller = Controller(numb_of_clerk);
	}
	else {
		cout << "Not enough argument" << endl;
		return -1;
	}
	while (getline(cin, data))
	{
		stringstream ss(data);
		string customer;
		int aTime, pTime;
		ss >> customer >> aTime >> pTime;
		controller.storeFile(customer, aTime, pTime);
	}
	controller.execute();
	return 0;
}

