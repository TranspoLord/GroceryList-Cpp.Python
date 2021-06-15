#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


/*
Description:
	Used to prevent any unwanted results if the user enters a non numeric answer
	Has own if and while loop that runs until a selection is made.
	Returns selection as an int. If the first index of the string is a number, it will use that
Example: 
	int x = GetUserInputInt("Please make selection", 4)
	User enters 3
Return:
	3 is returned
Example:
	User enters wasd
	"Please make a different selection"
	User needs to enter new selection
*/
int GetUserInputInt(string whatToSay, int numSelections)          
{	
	string sUserInput;
	int iNum = 0;
	do
	{
		cout << whatToSay;						//Used a string here just incase the msg needed to be different
		getline(cin, sUserInput);				//Gets the user input as a string
		stringstream streamUserIn(sUserInput);	//Creates new stream with the input as the variable
		streamUserIn >> iNum;					//Inputs the stream variable into the int only if it starts with numbers(minus any non-num)
												//Prevents any unwanted program interactions if user enters a non number
		if (iNum <= 0 && iNum >= numSelections + 1)
		{
			cout << endl;
			cout << " Invalid selection. Try a different number.\n" << endl;
		}
		else if (iNum > 0 && iNum <= numSelections)
			break;
	} while (iNum > 0 && iNum <= numSelections);
	cout << endl;
	return iNum;
}


void main()
{
	ifstream inFreqFile;
	bool bCalledTxtFile = false;
	int iInput;
	string sItemInput, sFreqFileName = "frequency.dat";

	callIntFunc("SetFeqFileName", sFreqFileName);		//Calls a function in python to set the freq file name. This will prevent spelling errors in the file name

	do {
		cout << endl;
		cout << " 1. Determine number of times each individual item appears" << endl;
		cout << " 2. Determine number of times a specific items appears" << endl;
		cout << " 3. Display a text-based histogram for each item" << endl;
		cout << " 4. Exit Program" << endl;
		iInput = GetUserInputInt(" Enter Selection: ", 4);  //Calls a function that gets user input and validates it with the number of selections


		if (iInput == 1)
		{
			CallProcedure("PrintAllDict");   //Calls a funct in python to print the list and the freq of the items
			cout << endl;
		}

		else if (iInput == 2)
		{
			int iFreq = 0;													
			cout << " Enter the name of the item: ";
			getline(cin, sItemInput);		
			sItemInput[0] = toupper(sItemInput[0]);							//Capitalizes the first letter of the word 
			iFreq = callIntFunc("GetFreqItem", sItemInput);					//Calls a python func that finds the item and returns the freq
			cout << endl;
			if (iFreq == 0)													//Prints if the item isnt found in the list
			{
				cout << " Sorry, this item does not seem to be in the list." << endl;
				cout << " If you believe this is an error, please check your spelling." << endl;
			}

			else if (iFreq > 0)												//Prints if an item is found in the list
			{
				cout << " There are " << iFreq << " " << sItemInput << " in the list." << endl;
			}
			cout << endl;
		}

		else if (iInput == 3)
		{

			string tempString = "";						//Creates variables for use in this scope
			int itemFreq = 0;
			bool bStringNumSwitch = false;

			CallProcedure("TxtToDat");
			inFreqFile.open(sFreqFileName);				//Opens freq.dat file
			if (!inFreqFile.is_open())	
				cout << " Could not open " << sFreqFileName << endl;

			do	//Iterates over each line in the text file
			{	
				inFreqFile >> tempString;				//Streams a string from the file to a temporary string
				if (tempString != "")					//Prevents unwanted spaces from printing
				{
					if (!bStringNumSwitch)				//Runs if the temp string is an item name
					{
						cout << left << setw(15) << tempString << "| ";
						bStringNumSwitch = true;
					}	
					else if (bStringNumSwitch)			//Runs if the temp string is an item frequency
					{
						stringstream toInt(tempString);	//Creates a new string stream with pointing to the temp string
						toInt >> itemFreq;				//Converts the string freq to an int freq
						for (int i = 0; i < itemFreq; ++i) //Prints a * for the amount of freq
						{
							cout << right << "*";
						}
						cout << endl;
						bStringNumSwitch = false;
					}
				}
				tempString = "";						//Clears the temp string to prevent unwanted printing
			} while (!inFreqFile.eof());
			inFreqFile.close();							//Closes the file to allow the program to reopen it
			cout << endl;
		}

		else if (iInput == 4)
		{
			cout << "      Goodbye!" << endl;
		}

		else
		{
			cout << " That is not a selection. Please enter again " << endl;
		}
		
	} while (iInput != 4);
	CallProcedure("CloseFiles");
}