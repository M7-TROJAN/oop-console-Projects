#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "inputValidate.h"

class clsUpdateClientScreen :protected clsScreen
{
private:
	enum enUbdateMenuOptions {
		eFirstName = 1,
		eLastName = 2,
		eEmail = 3,
		ePhone = 4,
		ePin = 5,
		eBalance = 6,
		eAll = 7
	};

	static enUbdateMenuOptions _ReadUbdateMenueOption() {
		short Choice = clsInputValidate::getInputInRange(1, 7);
		return (enUbdateMenuOptions)Choice;
	}

	static void _ReadClientInfo(clsBankClient& client, enUbdateMenuOptions option)
	{
		switch (option)
		{
		case clsUpdateClientScreen::eFirstName:
			client.FirstName = clsInputValidate::get_string("Please Enter FirstName: ");
			client.FirstName = clsInputValidate::trim(client.FirstName);
			return;
		case clsUpdateClientScreen::eLastName:
			client.LastName = clsInputValidate::get_string("Please Enter LastName: ");
			client.LastName = clsInputValidate::trim(client.LastName);
			return;
		case clsUpdateClientScreen::eEmail:
			client.Email = clsInputValidate::get_string("Please Enter Email: ");
			client.Email = clsInputValidate::trim(client.Email);
			client.Email = clsInputValidate::lowerAllStringLetters(client.Email);
			client.Email = clsInputValidate::removeSpaces(client.Email);
			return;
		case clsUpdateClientScreen::ePhone:
			client.Phone = clsInputValidate::readPhoneNumber();
			return;
		case clsUpdateClientScreen::ePin:
			client.pinCode = clsInputValidate::readPinCode();
			return;
		case clsUpdateClientScreen::eBalance:
			client.accountBalance = clsInputValidate::get_float("Please Enter Account Ballance: ");
			return;
		default:
			break;
		}

		// if you reach here then the user choose eAll (All Clients's Information).
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

	static void _PerformReadClientInfo(clsBankClient& client)
	{
		system("cls");
		_DrawScreenHeader("\tUpdate Client Screen");
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] First Name.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Last Name.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Email.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Phone Number.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] Pin Code.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[6] Balance.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[7] All.\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "Choose What DO You Want To Ubdate [1 to 7]?: ";

		_ReadClientInfo(client, _ReadUbdateMenueOption());
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
	static void UpdateClient() {
		if (!CheckAccessRights(clsUser::pUpdateClients))
		{
			return;
		}

		_DrawScreenHeader("\tUpdate Client Screen");

		std::string accountNumber = clsInputValidate::get_string("Please Enter Client Account Number: ");
		accountNumber = clsInputValidate::removeSpaces(accountNumber);

		// check if the acc bumber is not exist.
		while (!clsBankClient::isClientExist(accountNumber))
		{
			system("cls");
			_DrawScreenHeader("\tUpdate Client Screen");
			char tryAgain = 'n';
			std::cout << "Account Number (" << accountNumber << ") Is Not Found, Do You Want to Try Again ? (Y / N) : ";
			tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				return;
			}
			system("cls");
			_DrawScreenHeader("\tUpdate Client Screen");
			accountNumber = clsInputValidate::get_string("Please Enter Client Account Number: ");
			accountNumber = clsInputValidate::removeSpaces(accountNumber);
		}

		system("cls");
		_DrawScreenHeader("\tUpdate Client Screen");

		clsBankClient client = clsBankClient::find(accountNumber);
		_PrintClientInfo(client);

		char answer = clsInputValidate::get_char("\nAre you sure you want update this client (y/n)?: ");
		if (tolower(answer) != 'y')
			return;

		_PerformReadClientInfo(client);

		clsBankClient::enSaveResults saveResult;
		saveResult = clsBankClient::enSaveResults::svFailedEmptyObj;

		saveResult = client.Save();

		switch (saveResult)
		{
		case clsBankClient::svSucceeded:
			system("cls");
			std::cout << "\nAccount updated Successfully :)\n";
			_PrintClientInfo(client);
			break;
		case clsBankClient::svFailedEmptyObj:
			std::cout << "Error Account Was Not Saved Because it's Empty :(\n";
			break;
		default:
			break;
		}
	}
};
