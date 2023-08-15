#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "inputValidate.h"

class clsUpdateUserScreen : protected clsScreen {
private:
	enum enUbdateMenuOptions {
		eFirstName = 1, eLastName = 2, eEmail = 3,
		ePhone = 4, eUserName = 5, ePassword = 6,
		ePermissions = 7, eAll = 8
	};

	static enUbdateMenuOptions _ReadUbdateMenueOption() {
		short Choice = clsInputValidate::getInputInRange(1, 8);
		return (enUbdateMenuOptions)Choice;
	}

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;

		char Answer;

		Answer = clsInputValidate::get_char("\nDo you want to give full access (y/n)? ");
		if (Answer == 'y' || Answer == 'Y')
		{
			return -1; // Return -1 to indicate full access
		}

		std::cout << "\nPlease choose the permissions to grant:\n";
		std::cout << "---------------------------------------\n";

		Answer = clsInputValidate::get_char("Show Clients List? (y/n) ");
		if (std::tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::pListClients;
		}

		Answer = clsInputValidate::get_char("Add New Clients? (y/n) ");
		if (std::tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		Answer = clsInputValidate::get_char("Delete Clients? (y/n) ");
		if (std::tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		Answer = clsInputValidate::get_char("Update Client? (y/n) ");
		if (std::tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::pUpdateClients;
		}

		Answer = clsInputValidate::get_char("Find Client? (y/n) ");
		if (std::tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}

		Answer = clsInputValidate::get_char("Perform Transactions? (y/n) ");
		if (std::tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::pTransactions;
		}

		Answer = clsInputValidate::get_char("Manage Users? (y/n) ");
		if (std::tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		Answer = clsInputValidate::get_char("Show Login Register? (y/n) ");
		if (std::tolower(Answer) == 'y')
		{
			Permissions += clsUser::enPermissions::pLoginRegisterScreen;
		}

		return Permissions;
	}

	static void _ReadUserInfo(clsUser& user, enUbdateMenuOptions option)
	{
		switch (option)
		{
		case enUbdateMenuOptions::eFirstName:
			user.FirstName = clsInputValidate::get_string("Please Enter FirstName: ");
			return;
		case enUbdateMenuOptions::eLastName:
			user.LastName = clsInputValidate::get_string("Please Enter LastName: ");
			return;
		case enUbdateMenuOptions::eEmail:
			user.Email = clsInputValidate::get_string("Please Enter Email: ");
			user.Email = clsInputValidate::lowerAllStringLetters(user.Email);
			user.Email = clsInputValidate::removeSpaces(user.Email);
			return;
		case enUbdateMenuOptions::ePhone:
			user.Phone = clsInputValidate::readPhoneNumber();
			return;
		case enUbdateMenuOptions::ePassword:
			user.Password = clsInputValidate::readPassword();
			return;
		case enUbdateMenuOptions::ePermissions:
			std::cout << "\nEnter Permissions: ";
			user.Permissions = _ReadPermissionsToSet();
			return;
		default:
			break;
		}

		// if you reach here then the user choose eAll (All user's Information).

		user.FirstName = clsInputValidate::get_string("Please Enter FirstName: ");

		user.LastName = clsInputValidate::get_string("Please Enter LastName: ");

		user.Email = clsInputValidate::get_string("Please Enter Email: ");
		user.Email = clsInputValidate::lowerAllStringLetters(user.Email);
		user.Email = clsInputValidate::removeSpaces(user.Email);

		user.Phone = clsInputValidate::readPhoneNumber();

		user.Password = clsInputValidate::readPassword();

		std::cout << "\nEnter Permissions: ";
		user.Permissions = _ReadPermissionsToSet();
	}

	static void _PerformReadUserInfo(clsUser& user)
	{
		system("cls");
		_DrawScreenHeader("\tUpdate User Screen");
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] First Name.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Last Name.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Email.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Phone Number.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] UserName.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[6] Password.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[7] Permissions.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[8] All.\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "Choose What DO You Want To Ubdate [1 to 8]?: ";

		_ReadUserInfo(user, _ReadUbdateMenueOption());
	}

	// Print User information
	static void _PrintUserInfo(const clsUser& user) {
		std::cout << "\nUser details:";
		std::cout << "\n____________________________________";
		std::cout << "\nFirstName   : " << user.getFirstName();
		std::cout << "\nLastName    : " << user.getLastName();
		std::cout << "\nFull Name   : " << user.fullName();
		std::cout << "\nEmail       : " << user.getEmail();
		std::cout << "\nPhone       : " << user.getPhone();
		std::cout << "\nUserName    : " << user.GetUserName();
		std::cout << "\nPassword    : " << user.GetPassword();
		std::cout << "\nPermissions : " << user.GetPermissions();
		std::cout << "\n____________________________________\n";
	}

public:
	static void UpdateUser() {
		_DrawScreenHeader("\tUpdate User Screen");

		std::string userName = clsInputValidate::get_string("Please enter the username you want to Update: ");
		userName = clsInputValidate::lowerAllStringLetters(userName);

		// check if the User name is not exist.
		while (!clsUser::ISUserExist(userName))
		{
			system("cls");
			_DrawScreenHeader("\tUpdate User Screen");

			char tryAgain = 'n';
			std::cout << "\nA user with the username '" << userName << "' Is Not Found.\n";
			std::cout << "Do you want to try a different username? (Y / N): ";
			tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				return;
			}

			system("cls");
			_DrawScreenHeader("\tUpdate User Screen");
			userName = clsInputValidate::get_string("Please enter the username you want to Update: ");
			userName = clsInputValidate::lowerAllStringLetters(userName);
		}

		system("cls");
		_DrawScreenHeader("\tUpdate User Screen");

		clsUser user = clsUser::Find(userName);
		_PrintUserInfo(user);

		char answer = clsInputValidate::get_char("\nAre you sure you want to update this user? (Y / N): ");
		if (tolower(answer) != 'y')
		{
			std::cout << "\nOperation canceled. The user with the username '" << userName << "' was not updated.\n";
			return;
		}

		_PerformReadUserInfo(user);

		system("cls");
		_DrawScreenHeader("\tUpdate User Screen");

		std::cout << "The Follwing Are user Informations after Updated.\n";
		_PrintUserInfo(user);

		answer = clsInputValidate::get_char("\nAre you sure you want to Save? (Y / N): ");
		if (tolower(answer) != 'y')
		{
			std::cout << "\nOperation canceled. The user with the username '" << userName << "' was not updated.\n";
			return;
		}

		clsUser::enSaveResults saveResult;

		saveResult = user.Save();

		switch (saveResult)
		{
		case clsBankClient::svSucceeded:
			std::cout << "user With userName (" << userName << ") has been updated successfully.\n";
			break;
		case clsBankClient::svFailedEmptyObj:
			std::cout << "Error user Was Not Saved Because it's Empty :(\n";
			break;
		default:
			break;
		}
	}
};
