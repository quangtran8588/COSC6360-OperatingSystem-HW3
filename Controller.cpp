#include "Controller.h"
#define MAXCHILD 64

InputList *inputList = new InputList();
static pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;	// Mutex lock for nFreeClerk
static pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;	// Condition signal for pthread
static pthread_mutex_t wait_lock = PTHREAD_MUTEX_INITIALIZER;	// Mutex lock for hadToWait
static int nFreeClerk = 0;
static int hadToWait = 0;
int listCount = 0;

Controller::Controller()
{
}

Controller::~Controller()
{
}

Controller::Controller(int numb)
{
	nFreeClerk = numb;
}

// Function call when customer enter the post office
int arrivePostOffice(string customer)
{
	while (nFreeClerk == 0) {
		pthread_cond_wait(&cond_var, &mylock);
		pthread_mutex_lock(&wait_lock);
		hadToWait += 1;
		pthread_mutex_unlock(&wait_lock);
		if (nFreeClerk > 0) { pthread_mutex_unlock(&mylock); break; }
	}
	
	pthread_mutex_lock(&mylock);
	nFreeClerk -= 1;
	cout << "Customer #" << customer << " starts getting helped" << endl;
	
	if (nFreeClerk > 0) pthread_cond_signal(&cond_var);
	pthread_mutex_unlock(&mylock);
	return 0;
}

//	Function call to perform customer done getting help and leave the office
int leavePostOffice(string customer)
{
	pthread_mutex_lock(&mylock);
	nFreeClerk += 1;
	cout << "Customer #" << customer << " leaves the post office" << endl;
	pthread_cond_signal(&cond_var);
	pthread_mutex_unlock(&mylock);
}


void *print_message(void *data)
{
	string *temp;
	temp = (string*)data;
	int numb = 0;
	int processTime = stoi(temp[1].c_str());
	// Inform message when customer arrives the post office
	cout << "Customer #" << temp[0] << " arrives the post office" << endl;

	numb = arrivePostOffice(temp[0]);	
	
	// Customer is getting help, then leave the post office
	if (numb != 1) {
		for (int i = 0; i < processTime; i++) {
			sleep(1);
		}
		leavePostOffice(temp[0]);
	}
	pthread_exit(NULL);
}

//	Function to store input text file into node list of data
void Controller::storeFile(string vehicle, int aTime, int pTime)
{
	inputList = inputList->setData(listCount, vehicle, aTime, pTime);
	listCount++;
}


void Controller::execute()
{
	//	Create variables to be used
	pthread_t threads[MAXCHILD];	// create an array of thread child
	pthread_mutex_init(&mylock, NULL);  // Init mutex lock for nFreeClerk
	pthread_mutex_init(&wait_lock, NULL);	// Init mutex lock for hadToWait
	data* temp;
	string *data;
	int rc;

	for (int i = 0; i < listCount; i++)
	{
		data = new string[2];
		temp = inputList->getListData(inputList, i);
		data[0] = temp->customer;
		data[1] = to_string(temp->processTime);
		for (int i = 0; i < temp->arrvTime; i++)
			sleep(1);
		rc = pthread_create(&threads[i], NULL, &print_message, (void*)data);
		if (rc) {
			cout << "Unable to create thread" << endl;
			exit(1);
		}
	}
	for (int i = 0; i < listCount; i++)
		pthread_join(threads[i], NULL);

	cout << listCount << " customer(s) went serviced." << endl;
	cout << (listCount - hadToWait) << " customer(s) did not have to wait." << endl;
	cout << hadToWait << " customer(s) had to wait." << endl;
}
