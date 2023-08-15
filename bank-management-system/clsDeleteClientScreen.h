#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "InputValidate.h"

class clsDeleteClientScreen :protected clsScreen {
	// Print client information
	static void _PrintClientInfo(const clsBankClient& client) {
		std::cout << "\nclient details:";
		std::cout << "\n____________________________________";
		std::cout << "\nFirstName   : " << client.getFirstName();
		std::cout << "\nLastName    : " << client.getLastName();
		std::cout << "\nFull Name   : " << client.fullName();
		std::cout << "\nEmail       : " << client.getEmail();
		std::cout << "\nPhone       : " << client.getPhone();
		std::cout << "\nAcc. Number : " << client.accountNumber();
		std::cout << "\nPassword    : " << client.getPinCode();
		std::cout << "\nBalance     : " << client.getAccountBalance();
		std::cout << "\n____________________________________\n";
	}
public:
	static void DeleteClient() {
		if (!CheckAccessRights(clsUser::pDeleteClient))
		{
			return;
		}

		_DrawScreenHeader("\tDelete Client Screen");

		std::string accountNumber = clsInputValidate::get_string("Please Enter Client Account Number: ");

		// check if the acc bumber is not exist.
		while (!clsBankClient::isClientExist(accountNumber))
		{
			system("cls");
			_DrawScreenHeader("\tDelete Client Screen");
			char tryAgain = 'n';
			std::cout << "Account Number (" << accountNumber << ") Is Not Found, Do You Want to Try Again ? (Y / N) : ";
			tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				return;
			}
			system("cls");
			_DrawScreenHeader("\tDelete Client Screen");
			accountNumber = clsInputValidate::get_string("Please Enter Client Account Number: ");
		}

		system("cls");
		_DrawScreenHeader("\tDelete Client Screen");

		clsBankClient client = clsBankClient::find(accountNumber);
		_PrintClientInfo(client);

		char answer = clsInputValidate::get_char("\nAre you sure you want To Delete this client (y/n)?: ");
		if (tolower(answer) != 'y')
			return;

		if (client.Delete()) {
			std::cout << "Client With AccountNumber (" << accountNumber << ") has been deleted successfully.\n";
		}
		else {
			std::cout << "An unexpected error occurred. The client was not deleted.\n";
		}
	}
};
