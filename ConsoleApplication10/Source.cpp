#pragma once
#include <iostream>

#include "clsLoginScreen.h"

#include "clsAtmMainScreen.h"

using namespace std;


int main() {

	while (true) {
		system("cls");
		cout << "\n\n\nSelect An Option: \n";
		cout << "===========================================\n\n";
		cout << "[1] ATM\n\n\n";
		cout << "[2] BANK MANAGEMENT SYSTEM\n\n";
		cout << "===========================================\n\n\n\n";

		cout << "Enter 1 or 2: ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 2, "Invalid Option! Enter 1 or 2: ");

		if (Choice == 1) {
			clsAtmMainScreen::ShowAtmMainScreen();
		}
		else {
			
			clsLoginScreen::ShowLoginScreen();
			
		}
		cout << setw(37) << left << "" << "\n\tPress any key to LOGOUT...\n";
		system("pause>0");
	}

	
	
	

	/*while (true) {

		if (!clsLoginScreen::ShowLoginScreen())
			break;

	}*/
	
	


	return 0;
}

