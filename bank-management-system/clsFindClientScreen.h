#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "inputValidate.h"

class clsFindClientScreen : protected clsScreen {
private:
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
	static void FindClient()
	{
		if (!CheckAccessRights(clsUser::pFindClient))
		{
			return;
		}

		_DrawScreenHeader("\tFind Client Screen");

		std::string accountNumber = clsInputValidate::get_string("Please Enter Client Account Number: ");

		// check if the acc bumber is not exist.
		while (!clsBankClient::isClientExist(accountNumber))
		{
			system("cls");
			_DrawScreenHeader("\tFind Client Screen");
			char tryAgain = 'n';
			std::cout << "Account Number (" << accountNumber << ") Is Not Found, Do You Want to Try Again ? (Y / N) : ";
			tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				return;
			}
			system("cls");
			_DrawScreenHeader("\tFind Client Screen");
			accountNumber = clsInputValidate::get_string("Please Enter Client Account Number: ");
		}

		clsBankClient client = clsBankClient::find(accountNumber);

		if (!client.isEmpty())
		{
			std::cout << "\nClient Found :-)\n";
			_PrintClientInfo(client);
		}
		else
		{
			std::cout << "\nClient Was not Found :-(\n";
		}
	}
};
