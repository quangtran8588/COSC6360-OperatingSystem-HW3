#pragma once
#include <string>

using namespace std;

struct data
{
	int numbList;
	string customer;
	int arrvTime;
	int processTime;
	data *next;
	data *prev;
	data() : customer(""), arrvTime(0), processTime(0) {}
};

class InputList
{
private:
	bool empty;
	data* top;
	data* ptr;
public:
	InputList();
	~InputList();
	InputList* setData(int numb, string customer, int aTime, int pTime);
	data* getListData(InputList* inputList, int numb);
	string getCustomer(data *list);
	int getArrivalTime(data *list);
	int getProcessTime(data *list);
	void clean(InputList* dataList);
	string toString(InputList *list);
};
