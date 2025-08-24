/******************************************************************************
 * Program: Corner Grocer Inventory Tracker (main.cpp)
 * Author:  Nick Kopp
 * Date:    08/15/2025
 * Course:  CS210 – C++ Programming
 * Purpose: Reads inventory data from a file and allows the user to:
 *          1) Search for specific items and display their frequency
 *          2) Print all inventory items and their counts
 *          3) Display a histogram of item frequencies
 *          4) Exit the program
 *
 * Notes:   Backup of inventory data is written to frequency.dat when 
 *			option 3 is chosen.
 ******************************************************************************/

#include "Inventory.h"

using namespace std;

int main() {
	
	//Create inventory object
	Inventory inventory; 

	//Create menu loop
	while (true) { 

		int choice = -1;
		choice = stoi(inventory.MainMenu());
		
		try {
			switch (choice) {

			case 1: //Prints only items/amounts that user specifies.
				inventory.ReadUserInput();
				inventory.GetFrequencyUser();
				inventory.PrintFrequency();
				break;

			case 2: //Prints all inventory items and amounts
				inventory.GetFrequencyAll();
				inventory.PrintFrequency();
				break;

			case 3: //Prints histogram for visual aid of inventory
				
				inventory.GetFrequencyAll();
				inventory.PrintHistogram();
				inventory.OutputDataDat();

				break;

			case 4: //Exit
				cout << "\nThank you for using the Corner Grocery inventory program." << endl;
				cout << "Goodbye..." << endl;
				return 0;

			default: //Input Validation
				cout << "Invalid Choice, please try again." << endl;
			}
		}
		//Catch exception for runtime errors when file can't be read
		catch (const runtime_error& e) {
			cerr << e.what() << endl;
			return 1;
		}
		//Catch all other exceptions
		catch (const exception& e) {
			cerr << "Unexpected error: " << e.what() << endl;
			return 1;
		}

		cout << endl;
	}

	return 0;

}