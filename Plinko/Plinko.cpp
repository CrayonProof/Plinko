// Plinko.cpp : Defines the entry point for the console application.
// developed in Visual Studio

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;

double dropSingleChip(double inputSlot, bool pathReporting);
void enterYourSelection();
double ComputeWinnings(int slot);
void singleChipDialogue();
void multipleChipDialogue();
void displayMenu();

int SLOTS = 9;
int ROWS = 12;
double prizes[9] = {100.00, 500.00, 1000.00, 0.00, 10000.00, 0.00, 1000.00, 500.00, 100.00};

//stores the user's most recent input
int latestInput = -1;
bool endProgram;

//this function simulates dropping a chip down the plinko board.
//Since the simulation only needs to report the path of the chip for a single drop and not for a batch drop, pathReporting can be set to false at the function call to disable path reporting
double dropSingleChip(double inputSlot, bool pathReporting)
{
	cout << fixed << setprecision(1);
	if (pathReporting)
	{
		cout << "Path: [";
		cout << inputSlot;
		cout << ", ";
	}
	//this loop will simulate the chip's path at every row
	for (int i = 0; i < ROWS; i++)
	{
		if ((inputSlot >= 0) && (inputSlot <= SLOTS - 1))
		{
			//forces decrementing a half slot if chip is at the maximum slot
			if (inputSlot == SLOTS - 1)
			{
				inputSlot -= .5;
			}
			//forces incrementing a half slot if chip is at the minimum slot
			else if (inputSlot == 0)
			{
				inputSlot += .5;
			}
			else
			{
				//if the chip is not at either extreme, this either increments or decrements a half slot with a 50/50 chance of doing either one
				if ((rand() % 2) == 0)
				{
					inputSlot -= .5;
				}
				else
				{
					inputSlot += .5;
				}
			}
			if (pathReporting)
			{
				cout << inputSlot;
				if (i < ROWS - 1)
					cout << ", ";
			}
		}
		else
		{
			//out of bounds slot value should be handled outside of this function but, just in case it's not, this reports the error
			cout << "Error: invalid slot value";
			cout << endl;
		}
	}
	if (pathReporting)
	{
		cout << "]";
		cout << endl;
	}

	cout << fixed << setprecision(2);
	return ComputeWinnings(inputSlot);
}

double dropMultipleChips(int numChips, double slot)
{
	double total = 0.00;
	for (int i = 0; i < numChips; i++)
	{
		total = total + dropSingleChip(slot, false);
	}
	return total;
}

//not sure why I need this to be it's own function
double ComputeWinnings(int slot)
{
	return prizes[slot];
}

void displayMenu()
{
	//Display the options menu
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

	enterYourSelection();
}

void singleChipDialogue()
{
	cout << endl;
	cout << "*** Drop a single chip ***";
	cout << endl;

	cout << endl;
	cout << "Which slot do you want to drop the chip in (0-";
	cout << SLOTS - 1;
	cout << ")? ";

	//prompts the user for a slot to drop into

	//takes input for slot number
	cin >> latestInput;

	if ((latestInput >= 0) && (latestInput <= SLOTS - 1))
	{
		cout << endl;
		cout << "*** Dropping chip into slot ";
		cout << latestInput;
		cout << " ***";
		cout << endl;
		double winnings = dropSingleChip(latestInput, true);
		cout << "Winnings: $";
		cout << winnings;
		cout << endl;
	}
	else
	{
		cout << endl;
		cout << "Invalid slot.";
		cout << endl;
	}

	enterYourSelection();
}

void multipleChipDialogue()
{
	cout << endl;
	cout << "*** Drop multiple chips ***";
	cout << endl;

	//prompts the user for how many chips to drop
	cout << endl;
	cout << "How many chips do you want to drop (>0)? ";

	//takes user input for number of chips to drop
	cin >> latestInput;

	if (latestInput > 0)
	{
		//stores the number of chips in the numChips variable for later use
		int numChips = latestInput;

		cout << endl;
		cout << "Which slot do you want to drop the chip in (0-";
		cout << SLOTS - 1;
		cout << ")? ";

		//prompts the user for a slot to drop into

		//takes input for slot number
		cin >> latestInput;

		if ((latestInput >= 0) && (latestInput <= SLOTS - 1))
		{
			double total = dropMultipleChips(numChips, latestInput);

			cout << endl;
			cout << "Total winnings on ";
			cout << numChips;
			cout << " chips: $";
			cout << total;
			cout << endl;
			cout << "Average winnings per chip: $";
			cout << total / (double) numChips;
			cout << endl;
		}
		else
		{
			cout << endl;
			cout << "Invalid slot.";
			cout << endl;
		}
	}
	else
	{
		cout << endl;
		cout << "Invalid number of chips.";
		cout << endl;
	}

	enterYourSelection();
}

void enterYourSelection()
{
	cout << endl;
	cout << "Enter your selection now: ";
	cin >> latestInput;

	if (latestInput == 1)
		singleChipDialogue();
	else if (latestInput == 2)
		multipleChipDialogue();
	else if (latestInput == 3)
		multChipsEachSlotDialogue();
	else if (latestInput == 4)
		displayMenu();
	else if (latestInput == 5)
		endProgram = true;
	else
	{
		cout << endl;
		cout << ("Invalid selection.  Enter 3 to see options.");
		cout << endl;
		enterYourSelection();
	}
}

int main()
{
	srand(42);

	//sets double type to print out to the hundredths place to keep formatting consistent with lab output example
	cout << fixed << setprecision(2);

	cout << ("Welcome to the Plinko simulator!  Enter 3 to see options.");
	cout << endl;

	while (!endProgram)
	{
		enterYourSelection();
	}

	cout << endl;
	cout << "Goodbye!";
	return 0;
}