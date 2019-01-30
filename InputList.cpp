#include "InputList.h"

InputList::InputList()
{
	empty = true;
	top = NULL;
	ptr = NULL;
}

InputList::~InputList()
{
}

InputList* InputList::setData(int numb, string customer, int aTime, int pTime)
{
	data *newList = new data();
	newList->numbList = numb;
	newList->customer = customer;
	newList->arrvTime = aTime;
	newList->processTime = pTime;
	if (empty) { newList->prev = NULL, newList->next = NULL; top = newList; ptr = newList; empty = false; }
	else
	{
		newList->prev = ptr;
		newList->next = NULL;
		ptr->next = newList;
		ptr = newList;
	}
	return this;
}

data* InputList::getListData(InputList* inputList, int numb)
{
	data *temp = inputList->top;
	do {
		if (temp->numbList == numb) return temp;
		else {
			if (temp->next != NULL) temp = temp->next;
			else break;
		}
	} while (1);
	return NULL;
}
string InputList::getCustomer(data *list)
{
	return list->customer;
}
int InputList::getArrivalTime(data *list)
{
	return list->arrvTime;
}

int InputList::getProcessTime(data *list)
{
	return list->processTime;
}

void InputList::clean(InputList* dataList)
{
	do
	{
		data* temp = dataList->top;
		if (temp->next != NULL)
		{
			temp->next->prev = NULL;
			dataList->top = temp->next;
			delete temp;
		}
		else
		{
			delete temp;
			empty = true;
			break;
		}
	} while (1);
}

string InputList::toString(InputList *dataList)
{
	string toString;
	data *temp = dataList->top;
	do
	{
		dataList->ptr = temp;
		toString += dataList->getCustomer(temp) + " " + to_string(dataList->getArrivalTime(temp)) + " " + to_string(dataList->getProcessTime(temp)) + "\n";
		if (temp->next != NULL) temp = dataList->ptr->next;
		else break;
	} while (1);
	return toString;
}
