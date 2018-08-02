// Plinko.cpp : Defines the entry point for the console application.
// developed in Visual Studio

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int SLOTS = 9;
int ROWS = 12;
int prizes[9] = {100, 500, 1000, 0, 10000, 0, 1000, 500, 100};

//TODO: slim down commenting, change invalid input from reprompt to error notification and return to original prompt, check chapter 4 and chapter 6 guidlines and additions

//this function simulates dropping a chip down the plinko board.
//Since the simulation only needs to report the path of the chip for a single drop and not for a batch drop, pathReporting can be set to false at the function call to disable path reporting
double dropChip(double inputSlot, bool pathReporting)
{
	//this loop will simulate the chip's path at every row
	for (int i = 0; i < ROWS; i++)
	{
		if ((inputSlot >= 0) && (inputSlot <= SLOTS - 1))
		{
			//forces decrementing a half slot if chip is at the maximum slot
			if (inputSlot == SLOTS - 1)
			{
				if (pathReporting)
					cout << "The chip moved down and is at ";
				inputSlot -= .5;
			}
			//forces incrementing a half slot if chip is at the minimum slot
			else if (inputSlot == 0)
			{
				if (pathReporting)
					cout << "The chip moved up and is at ";
				inputSlot += .5;
			}
			else
			{
				//if the chip is not at either extreme, this either increments or decrements a half slot with a 50/50 chance of doing either one
				if ((rand() % 2) == 0)
				{
					if (pathReporting)
						cout << "The chip moved down and is at ";
					inputSlot -= .5;
				}
				else
				{
					if (pathReporting)
						cout << "The chip moved up and is at ";
					inputSlot += .5;
				}
			}
			if (pathReporting)
			{
				cout << inputSlot;
				cout << endl;
			}
		}
		else
		{
			//out of bounds slot value should be handled outside of this function but, just in case it's not, this reports the error
			cout << "Error: invalid slot value";
			cout << endl;
		}
	}
	return inputSlot;
}

void main()
{
	//seeds the random number genorator with 42 for repeatability
	srand(42);

	//latestInput stores the users latest text input while running the program
	int latestInput = -1;

	//prompts the user to input 3 until they input 3
	while (latestInput != 3)
	{
		cout << "Welcome to the Plinko simulator!  Enter 3 to see options.";
		cout << endl;
		cin >> latestInput;
	}

	//loops the simulation program until the user inputs 4, at which point the while loop condition is no longer valid and the program terminates
	while (latestInput != 4)
	{
		
		//Display the options menu
		cout << endl;
		cout << "1 - Drop a single chip into one slot";
		cout << endl;
		cout << "2 - Drop multiple chips into one slot";
		cout << endl;
		cout << "3 - Show the options menu";
		cout << endl;
		cout << "4 - Quit the program";
		cout << endl;
		
		//take input for the program's next action
		cin >> latestInput;

		//drops a single chip into one slot if 1 is input
		if (latestInput == 1)
		{
			//prompts the user for a slot to drop into
			cout << endl;
			cout << "pick a slot between 0 and ";
			cout << SLOTS - 1;
			cout << " in which to drop your chip";
			cout << endl;

			//takes input for slot number
			cin >> latestInput;

			//re-prompts user while slot number input is out of range
			while (!((latestInput >= 0) && (latestInput <= SLOTS - 1)))
			{
				cout << "slot must be inbetween 0 and ";
				cout << SLOTS - 1;
				cout << endl;
				//takes input for slot number if previous input was out of bounds
				cin >> latestInput;
			}
			cout << endl;

			//sets outputSlot to the return value of the dropChip function with the user's input for the slot as the inputSlot argument and with pathReporting set to true
			int outputSlot = (int)dropChip(latestInput, true);

			//reports the user's winnings based on the content of the outputSlot index of the prizes array
			cout << "you won $";
			cout << prizes[outputSlot];
			cout << endl;
			//reverts latestInput to -1 to avoid program terminating if user selected slot 4, thereby validating the enclosing while loop condition (latestInput = 4) and terminating the program
			latestInput = -1;
		}
		//drops multiple chips into one slot if 2 is input
		if (latestInput == 2)
		{
			//prompts the user for how many chips to drop
			cout << endl;
			cout << "How many chips would you like to drop?";
			cout << endl;

			//takes user input for number of chips to drop
			cin >> latestInput;

			//re-prompts the user for number of chips to drop if previous input was non-positive (including 0)
			while (latestInput <= 0)
			{
				cout << "The number of chips must be greater than 0";
				cout << endl;
				//takes user input for number of chips to drop if previous input was non-positive (including 0)
				cin >> latestInput;
			}
			//stores the number of chips in the numChips variable for later use
			int numChips = latestInput;
			cout << endl;

			//prompts the user for a slot to drop into
			cout << "Pick a slot between 0 and ";
			cout << SLOTS - 1;
			cout << " in which to drop your chips";
			cout << endl;

			//takes input for slot number
			cin >> latestInput;

			//re-prompts user while slot number input is out of range
			while (!((latestInput >= 0) && (latestInput <= SLOTS - 1)))
			{
				cout << "The slot must be inbetween 0 and ";
				cout << SLOTS - 1;
				cout << endl;

				//takes input for slot number if previous input was out of bounds
				cin >> latestInput;
			}
			cout << endl;

			//runs the simulation for the number of chips the user selected to drop, keeping track of total winnings
			int total = 0;
			for (int i = 0; i < numChips; i++)
			{
				int outputSlot = (int)dropChip(latestInput, false);
				total += prizes[outputSlot];
			}

			//reports total winnings and average winnings
			cout << "you won a total of $";
			cout << total;
			cout << " with an average of $";
			cout << total / numChips;
			cout << " on each drop";
			cout << endl;
			//reverts latestInput to -1 to avoid program terminating if user selected slot 4 and the enclosing while loop therfore terminates
			latestInput = -1;
		}
	}

	cout << "Program Terminating";
}

