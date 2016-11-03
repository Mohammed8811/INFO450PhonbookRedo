// INFO 450 A4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

#define MAX_ARR 100 //max entries
#define DISPLAY_PAUSE 5 //display 5 entries then pause

//define PhoneBook class that represents an entry of phone book
class PhoneBook {
public:
	//constructor
	PhoneBook(string, string, string);

	//get methods
	string getFullName() const;
	string getHomePhone() const;
	string getMobilePhone() const;
private:
	string fullName;
	string homePhone;
	string mobilePhone;
};

//constructor
PhoneBook::PhoneBook(string fn, string hp, string mp) {
	fullName = fn;
	homePhone = hp;
	mobilePhone = mp;
}

string PhoneBook::getFullName() const {
	return fullName;
}

string PhoneBook::getHomePhone() const {
	return homePhone;
}

string PhoneBook::getMobilePhone() const {
	return mobilePhone;
}

//save entries to file
//input: array of entries, number of entries
bool isDuplicate(PhoneBook* entries[], int numEntries, string fullName, string homePhone, string mobilePhone);

//load phone book from file
//input file name
//output: array is loaded and numEntries is set
void load(string filename, PhoneBook* entries[], int &numEntries);

//save entries to file
//input: file name, array of entries, number of entries
void save(string filename, PhoneBook* entries[], int numEntries);

//add entry
//input: array of entries, number of entries
//output: one entry is added and numEntries is increase by one or error is displayed
void addEntry(PhoneBook* entries[], int &numEntries);

//search by name
//input: array of entries, number of entries
void search(PhoneBook* entries[], int numEntries);

//display
//input: array of entries, number of entries
void display(PhoneBook* entries[], int numEntries);

//free resource
//input: array of entries, number of entries
void freeResources(PhoneBook* entries[], int &numEntries);

/*
main function
*/
int main() {

	//array of phone books
	PhoneBook* entries[MAX_ARR];

	//input file name
	string filename;

	int numEntries; //number of entries

					//selection
	string selection = "";

	//prompt for file name
	cout << "Please enter the phonebook file name: ";
	getline(cin, filename);

	//load file
	load(filename, entries, numEntries);

	//display menu and process user selection
	while (selection != "0") {

		cout << "1. Add Entry" << endl;
		cout << "2. Search Entry by portion of name" << endl;
		cout << "3. Display all entries" << endl;
		cout << "0. Save and Exit" << endl;

		cout << "Your selection? ";
		getline(cin, selection);

		if (selection == "1")
		{
			addEntry(entries, numEntries);
		}
		else if (selection == "2")
		{
			search(entries, numEntries);
		}
		else if (selection == "3")
		{
			display(entries, numEntries);
		}
		else if (selection == "0")
		{//save and exit

		}
		else {
			cout << "Invalid selection" << endl;
		}

		cout << endl; //print a new line
	}//end while

	 //save file
	save(filename, entries, numEntries);

	//free resource	
	freeResources(entries, numEntries);

	return 0;
}

//save entries to file
//input: array of entries, number of entries
bool isDuplicate(PhoneBook* entries[], int numEntries, string fullName, string homePhone, string mobilePhone) {
	//iterate the array
	for (int i = 0; i < numEntries; i++)
	{
		if (entries[i]->getFullName() == fullName || entries[i]->getHomePhone() == homePhone ||
			entries[i]->getMobilePhone() == mobilePhone) {
			return true;
		}
	}
	return false;
}

//load phone book from file
//input file name
//output: array is loaded and numEntries is set
void load(string filename, PhoneBook* entries[], int &numEntries) {

	string line; //line from file

				 //phone book data	
	string fullName;
	string homePhone;
	string mobilePhone;

	ifstream input(filename.c_str());
	numEntries = 0;

	if (input.good())
	{
		//read line by line until end of file
		while (!input.eof() && !input.fail())
		{
			getline(input, line); //read a line

			if (line != "") {

				//split to get entry
				istringstream iss(line);

				getline(iss, fullName, '|');
				getline(iss, homePhone, '|');
				getline(iss, mobilePhone, '|');

				if (numEntries == MAX_ARR)
				{
					cout << "The phone book is full" << endl;
					break;
				}
				else if (isDuplicate(entries, numEntries, fullName, homePhone, mobilePhone)) {
					cout << "The phone book is duplicate (full name or home phone or mobil phone)" << endl;
				}
				else {
					//create new PhoneBook
					//put into array
					entries[numEntries++] = new PhoneBook(fullName, homePhone, mobilePhone);
				}
			}
		}//end while

		 //close file
		input.close();
	}
	else {
		cout << "Unable to open file for reading" << endl;
	}
}

//save entries to file
//input: file name, array of entries, number of entries
void save(string filename, PhoneBook* entries[], int numEntries) {

	//open file for writing
	ofstream ouput(filename.c_str());

	//check if file can be opened
	if (ouput.is_open())
	{
		for (int i = 0; i < numEntries; i++)
		{
			ouput << entries[i]->getFullName() << "|" << entries[i]->getHomePhone() <<
				"|" << entries[i]->getMobilePhone() << endl;
		}

		//close file
		ouput.close();
	}
	else {
		cout << "Unable to open file for writing" << endl;
	}
}

//add entry
//input: array of entries, number of entries
//output: one entry is added and numEntries is increase by one or error is displayed
void addEntry(PhoneBook* entries[], int &numEntries) {

	//phone book data	
	string fullName;
	string homePhone;
	string mobilePhone;

	if (numEntries == MAX_ARR)
	{
		cout << "The phone book is full" << endl;
	}
	else {

		//prompt for full name
		cout << "Please enter full name: ";
		getline(cin, fullName);
		//prompt for home phone
		cout << "Please enter home phone: ";
		getline(cin, homePhone);
		//prompt for full name
		cout << "Please enter mobile phone: ";
		getline(cin, mobilePhone);

		if (isDuplicate(entries, numEntries, fullName, homePhone, mobilePhone)) {
			cout << "The phone book is duplicate (full name or home phone or mobil phone)" << endl;
		}
		else {
			//create new PhoneBook
			//put into array
			entries[numEntries++] = new PhoneBook(fullName, homePhone, mobilePhone);
		}
	}
}

//search by name
//input: array of entries, number of entries
void search(PhoneBook* entries[], int numEntries) {

	//portion of name
	string name;

	bool found = false; //is found?

						//prompt for portion of name
	cout << "Please enter name: ";
	getline(cin, name);

	//iterate the array
	for (int i = 0; i < numEntries; i++)
	{

		if (strstr(entries[i]->getFullName().c_str(), name.c_str()) != NULL)
		{
			found = true;
			cout << "Full name: " << entries[i]->getFullName() << endl;
			cout << "Home phone: " << entries[i]->getHomePhone() << endl;
			cout << "Mobile phone: " << entries[i]->getMobilePhone() << endl << endl;
		}
	}//end for

	if (!found) {
		cout << "Phone book not found" << endl;
	}
}

//display
//input: array of entries, number of entries
void display(PhoneBook* entries[], int numEntries) {

	if (numEntries == 0)
	{
		cout << "The phone book is empty" << endl;
	}
	else {
		//iterate the array
		for (int i = 0; i < numEntries; i++)
		{
			cout << "Full name: " << entries[i]->getFullName() << endl;
			cout << "Home phone: " << entries[i]->getHomePhone() << endl;
			cout << "Mobile phone: " << entries[i]->getMobilePhone() << endl << endl;

			if ((i + 1) % DISPLAY_PAUSE == 0)
			{
				system("pause");
				cout << endl; //print new line
			}
		}
	}
}


//free resource
//input: array of entries, number of entries
void freeResources(PhoneBook* entries[], int &numEntries) {

	//iterate the array
	for (int i = 0; i < numEntries; i++)
	{
		delete entries[i];
	}//end for
	numEntries = 0;
}