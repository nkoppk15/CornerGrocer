/******************************************************************************
 * Program: Corner Grocer Inventory Tracker (inventory.cpp)
 * Author:  Nick Kopp
 * Date:    08/15/2025
 * Course:  CS210 – C++ Programming
 * 
 * Description: Defines the Inventory class that was decalred in 'Inventory.h'.
 */

#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <iomanip>
#include "Inventory.h"

using namespace std;

//Default Constructor
Inventory::Inventory() {

}
//Main Menu function
string Inventory::MainMenu() {

	cout << "******************************************************************" << endl;
	cout << "******************************************************************" << endl;
	cout << "~~~~~~~~~~~           WELCOME to Corner Grocer!        ~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~   Inventory Tracking  & Frequency System   ~~~~~~~~~~~" << endl;
	cout << "******************************************************************" << endl;
	cout << "******************************************************************" << endl << endl;
	cout << "                  How can we be of assistance?                    " << endl << endl;
	cout << "1: Search for item(s)" << endl;
	cout << "2: List of all inventory" << endl;
	cout << "3: Print inventory histogram" << endl;
	cout << "4: Exit" << endl << endl;
	cout << "Please enter your selection now: ";
	
	//Loop to protect stoi() from fatal error. Forces user to select a valid option.
	string menu;
	while (true) {
		
		getline(cin, menu);

		if ((menu == "1") || (menu == "2") || (menu == "3") || (menu == "4")) {
			break;
		}

		//Repeats menu options if valid selection wasnt made.
		else {
			cout << "\n--- Invalid selection, please select from the following options. ---" << endl;
			cout << "1: Search for item(s)" << endl;
			cout << "2: List of all inventory" << endl;
			cout << "3: Print inventory histogram" << endl;
			cout << "4: Exit" << endl << endl;
			cout << "Please enter your selection now: ";
			continue;
		}
	}

	return menu;
}


//Converts item to lower case for input validation & count accuracy.
string Inventory::ToLower(const std::string& str) {
	string lower = str;
	transform(lower.begin(), lower.end(), lower.begin(),
		[](unsigned char c) {return tolower(c); });

	return lower;
}


//Reads user input, adds to vector.
//Compiles list of items to search inventory list.
void Inventory::ReadUserInput() {
	string inputValue;
	itemsToFind.clear();

	cout << "Which items would you like to find? ('Q' to finish.)" << endl;

	//Allows user to enter multiple items, until Q or q
	while ((inputValue != "Q") && (inputValue != "q")) {
		getline(cin, inputValue);

		//Push back items to vector for later referencing
		if ((inputValue != "Q") && (inputValue != "q")) {
			itemsToFind.push_back(ToLower(inputValue));
		}
	}

	//User Feedback, lets them know we're locating what they asked
	cout << endl << "Locating: " << endl << endl;
	
}

//Access ifstream to find all user specified items and add the items/amounts to a map.
void Inventory::GetFrequencyUser() {

	//Clear map between uses
	InventoryItems.clear();
	vector<int> counts(itemsToFind.size(), 0);
	ifstream inventoryList;

	//File validation
	inventoryList.open("InventoryList.txt");

	if (!inventoryList.is_open()) {
		throw runtime_error("Error: Unable to read file 'InventoryList.txt'");
	}

	//Lower case for accurate counting
	string item;
	while (inventoryList >> item) {
		string lowerItem = ToLower(item);
		for (int i = 0; i < counts.size(); i++) {
			if (lowerItem == itemsToFind[i]) {
				counts[i]++;
			}
		}
	}
	//Adds all items found to map
	for (int i = 0; i < counts.size(); i++) {
		InventoryItems.emplace(itemsToFind[i], counts[i]);
	}
	
}

void Inventory::GetFrequencyAll() {
	InventoryItems.clear();
	ifstream inventoryList("inventoryList.txt");

	//File Validation
	if (!inventoryList.is_open()) {
		throw std::runtime_error("Error: Unable to read file 'inventoryList.txt'"); 
	}
	
	//Adds all items found to map
	std::string word;
	while (inventoryList >> word) {
		word = ToLower(word);  // normalize case
		InventoryItems[word]++; // default constructs int=0 if missing, then increments
	}
}




void Inventory::PrintFrequency() {
	//Prints the map that was generated in GetFrequency functions
	for (const auto& pair : InventoryItems) {
		cout << right << setw(12) << pair.first << " : ";
		cout << pair.second << endl;
	}
}



void Inventory::PrintHistogram() {

	//Uses InventoryItems map to print histogram based on item count
	for (const auto& pair : InventoryItems) {
		cout << right << setw(12) <<  pair.first << ": ";
		for (int i = 0; i < pair.second; i++) {
			cout << '*';
		}
		cout << endl;
	}
	cout << endl << endl;
}

void Inventory::OutputDataDat() {
	ofstream datStream;
	datStream.open("frequency.dat");

	//File validation
	if (!datStream.is_open()) {
		throw runtime_error("Error: Unable to write file 'frequency.dat'");

	}
	//Lets user know whats happening
	cout << endl << "WRITING HISTOGRAM TO FILE 'frequency.dat'..." << endl << endl;

	//Writes datStream to .dat file 'frequency.dat'
	for (const auto& pair : InventoryItems) {
		datStream << right << setw(12) << pair.first << ": ";
		for (int i = 0; i < pair.second; i++) {
			datStream << '*';
		}
		datStream << endl;
	}
	datStream << endl << endl;

	cout << "Writing finished." << endl;
}