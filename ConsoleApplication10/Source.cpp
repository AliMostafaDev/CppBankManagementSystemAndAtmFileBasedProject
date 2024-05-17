#pragma once
#include <iostream>

#include "clsLoginScreen.h"

using namespace std;


int main() {


	while (true) {

		if (!clsLoginScreen::ShowLoginScreen())
			break;

	}
	
	cout << "ali" << endl;


	return 0;
}

