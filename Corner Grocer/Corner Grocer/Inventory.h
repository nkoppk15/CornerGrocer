/******************************************************************************
 * Program: Corner Grocer Inventory Tracker (inventory.h)
 * Author:  Nick Kopp
 * Date:    08/15/2025
 * Course:  CS210 – C++ Programming
 *
 * Description: Defines the Inventory class that was decalred in 'Inventory.h'.
 */


#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>



class Inventory {

public:
	Inventory(); //Default Constructor
	void ReadUserInput(); //Reads user input into a vector 
	void GetFrequencyUser(); //Counts user input's occurences in ifstream and generates report
	void GetFrequencyAll(); //Counts all items in ifstream and generates report
	void PrintHistogram();//Prints a histogram of the data from GetFrequencyAll()
	void OutputDataDat(); //Outputs histogram from PrintHistogram() to 'frequency.dat'
	void PrintFrequency(); // Prints the map data generated from both GetFrequency functions
	std::string MainMenu(); //Shows a 4 choice main menu for user to select functionality 





private:
	std::vector<std::string> itemsToFind; //Items user wants to search for
	std::map<std::string, int> InventoryItems; //Map used to generate histogram and print frequency reports
	std::string ToLower(const std::string& str); //All items converted to lower case for input validation and correct reports






};
#endif //INVENTORY_H