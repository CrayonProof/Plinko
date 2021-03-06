// Plinko.cpp : Defines the entry point for the console application.
// developed in Visual Studio

//#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

double DropSingleChip(double inputSlot, bool pathReporting);
double DropMultipleChips(int numChips, double slot);

void EnterYourSelection();
void DisplayMenu();
bool TakeInput(int inputType);
double ComputeWinnings(int slot);

void SingleChipDialogue();
void MultipleChipDialogue();
void MultipleChipsEachSlotDialogue();

//The three constants that change the plinko board
int NUM_SLOTS = 9;
int NUM_ROWS = 12;
double PRIZES[9] = {100.00, 500.00, 1000.00, 0.00, 10000.00, 0.00, 1000.00, 500.00, 100.00};

double RANDOM_SEED = 42;
double total;
int latestInput;
bool endProgram;

//takes input for number of chips and which slot
bool TakeInput(int inputType) {
	//type 0 argument means which slot
	if (inputType == 0) {
		cout << endl;
		cout << "Which slot do you want to drop the chip in (0-";
		cout << NUM_SLOTS - 1;
		cout << ")? ";

		cin >> latestInput;

		if (!cin) {
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');

			cout << endl;
			cout << "Invalid slot.";
			cout << endl;

			return TakeInput(0);
		}
		else if ((latestInput >= 0) && (latestInput <= NUM_SLOTS - 1)) {
			return true;
		}
		else {
			cout << endl;
			cout << "Invalid slot.";
			cout << endl;

			//function recursively calls itself until valid input received
			return TakeInput(0);
		}
	}
	//type 1 argument means how many chips
	else if (inputType == 1) {
		cout << endl;
		cout << "How many chips do you want to drop (>0)? ";

		cin >> latestInput;
		if (!cin) {
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(),'\n');

			cout << endl;
			cout << "Invalid number of chips.";
			cout << endl;

			return TakeInput(1);
		}
		else if (latestInput > 0) {
			return true;
		}
		else {
			cout << endl;
			cout << "Invalid number of chips.";
			cout << endl;
			
			//function recursively calls itself until valid input received
			return TakeInput(1);
		}
	}
	//type 2 argument means which selection
	else if (inputType == 2) {

		cout << endl;
		cout << "Enter your selection now: ";
		cin >> latestInput;

		if (!cin) {
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');

			cout << endl;
			cout << "Invalid selection.  Enter 4 to see options.";
			cout << endl;

			return TakeInput(2);
		}
		else if ((latestInput > 0) && (latestInput <6)) {
			return true;
		}
		else {
			cout << endl;
			cout << "Invalid selection.  Enter 4 to see options.";
			cout << endl;

			//function recursively calls itself until valid input received
			return TakeInput(2);
		}
	}
	return false;
}

double DropSingleChip(double inputSlot, bool pathReporting) {

	//change double precision level to match the lab's sample output
	cout << fixed << setprecision(1);

	if (pathReporting) {
		cout << "Path: [";
		cout << inputSlot;
		cout << ", ";
	}
	//this loop will simulate the chip's path at every row
	for (int i = 0; i < NUM_ROWS; i++) {
		if ((inputSlot >= 0) && (inputSlot <= NUM_SLOTS - 1)) {
			//forces moving the chip down
			if (inputSlot == NUM_SLOTS - 1) {
				inputSlot -= .5;
			}
			//forces moving the chip up
			else if (inputSlot == 0) {
				inputSlot += .5;
			}
			else {
				//50/50 chance of moving chip right or left
				if ((rand() % 2) == 0) {
					inputSlot -= .5;
				}
				else {
					inputSlot += .5;
				}
			}
			if (pathReporting) {
				cout << inputSlot;
				if (i < NUM_ROWS - 1) {
					cout << ", ";
				}
			}
		}
		else {
			//out of bounds slot value should be handled outside of this function but just in case...
			cout << "Error: invalid slot value";
			cout << endl;
		}
	}
	if (pathReporting) {
		cout << "]";
		cout << endl;
	}

	//change double precision level to match the lab's sample output
	cout << fixed << setprecision(2);

	return ComputeWinnings(inputSlot);
}

double DropMultipleChips(int numChips, double slot) {
	total = 0.00;

	for (int i = 0; i < numChips; i++) {
		total = total + DropSingleChip(slot, false);
	}
	return total;
}

double ComputeWinnings(int slot)
{
	return PRIZES[slot];
}

void DisplayMenu() {

	cout << endl;

	cout << "Menu: Please select one of the following options:";
	cout << endl;
	cout << endl;
	cout << "1 - Drop a single chip into one slot";
	cout << endl;
	cout << "2 - Drop multiple chips into one slot";
	cout << endl;
	cout << "3 - Drop multiple chips into each slot";
	cout << endl;
	cout << "4 - Show the options menu";
	cout << endl;
	cout << "5 - Quit the program";
	cout << endl;

	EnterYourSelection();
}

void SingleChipDialogue() {
	cout << endl;
	cout << "*** Drop a single chip ***";
	cout << endl;

	if (TakeInput(0)) {
		cout << endl;
		cout << "*** Dropping chip into slot ";
		cout << latestInput;
		cout << " ***";
		cout << endl;
		double winnings = DropSingleChip(latestInput, true);
		cout << "Winnings: $";
		cout << winnings;
		cout << endl;
	}

	EnterYourSelection();
}

void MultipleChipDialogue() {
	cout << endl;
	cout << "*** Drop multiple chips ***";
	cout << endl;

	if (TakeInput(1)) {

		int numChips = latestInput;

		if (TakeInput(0)) {
			double total = DropMultipleChips(numChips, latestInput);

			cout << endl;
			cout << "Total Winnings on ";
			cout << numChips;
			cout << " chips: $";
			cout << total;
			cout << endl;
			cout << "Average winnings per chip: $";
			cout << total / (double) numChips;
			cout << endl;
		}
	}

	EnterYourSelection();
}

void MultipleChipsEachSlotDialogue() {
	cout << endl;
	cout << "*** Sequentially drop multiple chips ***";
	cout << endl;

	if (TakeInput(1)) {
		for (int i = 0; i < NUM_SLOTS; i++) {
			double total = DropMultipleChips(latestInput, i);

			cout << endl;
			cout << "Total Winnings on slot ";
			cout << i;
			cout << " chips: ";
			cout << total;
			cout << endl;
			cout << "Average winnings per chip: ";
			cout << total / (double)latestInput;
			cout << endl;
		}
	}

	EnterYourSelection();
}

void EnterYourSelection() {
	
	if (TakeInput(2)) {
		if (latestInput == 1) {
			SingleChipDialogue();
		}
		else if (latestInput == 2) {
			MultipleChipDialogue();
		}
		else if (latestInput == 3) {
			MultipleChipsEachSlotDialogue();
		}
		else if (latestInput == 4) {
			DisplayMenu();
		}
		else if (latestInput == 5) {
			endProgram = true;
		}
	}
}

int main() {
	srand(RANDOM_SEED);

	//change double precision level to match the lab's sample output
	cout << fixed << setprecision(2);

	cout << ("Welcome to the Plinko simulator!  Enter 4 to see options.");
	cout << endl;

	while (!endProgram) {

		EnterYourSelection();
	}

	//program terminate sequence
	cout << endl;
	cout << "Goodbye!";
	return 0;
}