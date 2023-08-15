#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "inputValidate.h"

class clsDepositScreen : protected clsScreen {
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
	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t   Deposit Screen");

		std::string AccountNumber = _ReadClientAccountNumber();

		while (!clsBankClient::isClientExist(AccountNumber)) {
			std::cout << "\nClient with [" << AccountNumber << "] does not exist, Do You Want to Try Again ? (Y / N) : ";
			char tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				return;
			}
			system("cls");
			_DrawScreenHeader("\t   Deposit Screen");
			AccountNumber = _ReadClientAccountNumber();
		}

		clsBankClient client = clsBankClient::find(AccountNumber);
		_PrintClientInfo(client);

		double Amount = clsInputValidate::get_Positive_double("Please Enter Deposit Amount: ");

		char Answer = 'n';
		std::cout << "\n\nAre you sure you want perform this transaction? (Y / N) : ";
		Answer = clsInputValidate::get_char();

		if (tolower(Answer) != 'y')
		{
			std::cout << "\nOperation was cancelled.\n";
			return;
		}

		client.Deposit(Amount);

		system("cls");
		_DrawScreenHeader("\t   Deposit Screen");
		_PrintClientInfo(client);
		std::cout << "\nAmount Deposited Successfully.\n";
		std::cout << "\nNew Balance Is: " << client.accountBalance << std::endl;
	}
};
