#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "inputValidate.h"

class clsWithDrawScreen : protected clsScreen {
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

	static std::string _ReadClientAccountNumber()
	{
		std::string AccountNumber = clsInputValidate::get_string("Please Enter Client Account Number: ");
		return AccountNumber;
	}

public:
	static void ShowWithDrawScreen()
	{
		_DrawScreenHeader("\t   WithDraw Screen");

		std::string AccountNumber = _ReadClientAccountNumber();

		while (!clsBankClient::isClientExist(AccountNumber)) {
			std::cout << "\nClient with [" << AccountNumber << "] does not exist, Do You Want to Try Again ? (Y / N) : ";
			char tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				return;
			}
			system("cls");
			_DrawScreenHeader("\t   WithDraw Screen");
			AccountNumber = _ReadClientAccountNumber();
		}

		clsBankClient client = clsBankClient::find(AccountNumber);
		_PrintClientInfo(client);

		// Check If the Client balance is Zero
		if (client.accountBalance == 0)
		{
			std::cout << "Your balance is currently zero. You are unable to withdraw funds at this time.";
			return;
		}

		double Amount = clsInputValidate::get_Positive_double("Please Enter WithDraw Amount: ");

		//Validate that the amount does not exceeds the balance i.e not bigger than balance
		while (Amount > client.accountBalance)
		{
			std::cout << "\nAmount Exceeds the balance, you can withdraw up to : " << client.accountBalance << std::endl;
			std::cout << "Do You Want to Try Again ? (Y / N) : ";
			char tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				std::cout << "\nOperation was cancelled.\n";
				return;
			}
			system("cls");
			_DrawScreenHeader("\t   WithDraw Screen");
			_PrintClientInfo(client);
			Amount = clsInputValidate::get_Positive_double("Please Enter WithDraw Amount: ");
		}

		char Answer = 'n';
		std::cout << "\n\nAre you sure you want perform this transaction? (Y / N) : ";
		Answer = clsInputValidate::get_char();

		if (tolower(Answer) != 'y')
		{
			std::cout << "\nOperation was cancelled.\n";
			return;
		}

		if (client.Withdraw(Amount))
		{
			system("cls");
			_DrawScreenHeader("\t   WithDraw Screen");
			_PrintClientInfo(client);

			std::cout << "\nAmount Withdrew Successfully.\n";
			std::cout << "\nNew Balance Is: " << client.accountBalance << "\n";
		}
		else
		{
			std::cout << "\nCannot withdraw, Insuffecient Balance!\n";
			std::cout << "\nAmout to withdraw is: " << Amount << "\n";
			std::cout << "\nThe Current Balance is: " << client.accountBalance << "\n";
		}
	}
};
