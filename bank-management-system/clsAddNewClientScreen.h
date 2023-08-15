#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "InputValidate.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen {
private:
	static void _ReadClientInfo(clsBankClient& client)
	{
		client.FirstName = clsInputValidate::get_string("Please Enter FirstName: ");
		client.FirstName = clsInputValidate::trim(client.FirstName);

		client.LastName = clsInputValidate::get_string("Please Enter LastName: ");
		client.LastName = clsInputValidate::trim(client.LastName);

		client.Email = clsInputValidate::get_string("Please Enter Email: ");
		client.Email = clsInputValidate::trim(client.Email);
		client.Email = clsInputValidate::lowerAllStringLetters(client.Email);
		client.Email = clsInputValidate::removeSpaces(client.Email);

		client.Phone = clsInputValidate::readPhoneNumber();

		client.pinCode = clsInputValidate::readPinCode();

		client.accountBalance = clsInputValidate::get_float("Please Enter Account Ballance: ");
	}

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
	static void AddNewClient() {
		if (!CheckAccessRights(clsUser::pAddNewClient))
		{
			return;
		}

		_DrawScreenHeader("\t Add New Client Screen");

		std::string accountNumber = clsInputValidate::get_string("Please Enter Client Account Number: ");
		accountNumber = clsInputValidate::removeSpaces(accountNumber);

		// check if the acc bumber is already exist.
		while (clsBankClient::isClientExist(accountNumber))
		{
			system("cls");
			_DrawScreenHeader("\t Add New Client Screen");

			char tryAgain = 'n';
			std::cout << "Account Number (" << accountNumber << ") Is Already Exist, Do You Want to Try Again ? (Y / N) : ";
			tryAgain = clsInputValidate::get_char();
			if (std::tolower(tryAgain) != 'y')
			{
				return;
			}

			system("cls");
			_DrawScreenHeader("\t Add New Client Screen");
			accountNumber = clsInputValidate::get_string("Please Enter Client Account Number: ");
			accountNumber = clsInputValidate::removeSpaces(accountNumber);
		}

		system("cls");
		_DrawScreenHeader("\t Add New Client Screen");

		clsBankClient newClient = clsBankClient::createNewClient(accountNumber);

		_ReadClientInfo(newClient);

		system("cls");
		_DrawScreenHeader("\t Add New Client Screen");

		_PrintClientInfo(newClient);

		char answer = 'n';
		std::cout << "\n\nAre You Sure you want to save this information? (Y / N): ";
		answer = clsInputValidate::get_char();

		if (tolower(answer) != 'y')
		{
			std::cout << "\nOperation canceled. The information was not saved.\n";
			return;
		}

		system("cls");
		_DrawScreenHeader("\t Add New User Screen");

		clsBankClient::enSaveResults saveResult = newClient.Save();

		switch (saveResult)
		{
		case clsBankClient::svSucceeded:
			std::cout << "\nAccount Added Successfully :)\n";
			_PrintClientInfo(newClient);
			break;
		case clsBankClient::svFailedEmptyObj:
			std::cout << "Error Account Was Not Saved Because it's Empty :(\n";
			break;
		case clsBankClient::svFailedAccountNumberExist:
			std::cout << "\nError Account Was Not Saved Because Account Number is used!\n";
			break;
		default:
			break;
		}
	}
};
