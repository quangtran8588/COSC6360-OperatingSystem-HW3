#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "InputList.h"
#include <pthread.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>

using namespace std;

class Controller
{
public:
	Controller();
	Controller(int numb_of_clerk);
	~Controller();
	void storeFile(string vehicle, int aTime, int pTime);
	void execute();
};


