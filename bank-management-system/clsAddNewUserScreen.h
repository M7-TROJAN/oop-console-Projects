#pragma once

#include "clsScreen.h"
#include "clsUser.h"
#include "InputValidate.h"
#include <iomanip>
class clsAddNewUserScreen : protected clsScreen {
private:
	static void _ReadUserInfo(clsUser& user)
	{
		user.FirstName = clsInputValidate::get_string("Please Enter FirstName: ");
		user.FirstName = clsInputValidate::trim(user.FirstName);

		user.LastName = clsInputValidate::get_string("Please Enter LastName: ");
		user.LastName = clsInputValidate::trim(user.LastName);

		user.Email = clsInputValidate::get_string("Please Enter Email: ");
		user.Email = clsInputValidate::trim(user.Email);
		user.Email = clsInputValidate::lowerAllStringLetters(user.Email);
		user.Email = clsInputValidate::removeSpaces(user.Email);

		user.Phone = clsInputValidate::readPhoneNumber();

		user.Password = clsInputValidate::readPassword();

		std::cout << "\nEnter Permissions: ";
		user.Permissions = _ReadPermissionsToSet();
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
	static void AddNewUser() {
		_DrawScreenHeader("\t Add New User Screen");

		std::string userName = clsInputValidate::get_string("Please enter a new username (all letters in lowercase, without spaces): ");
		userName = clsInputValidate::lowerAllStringLetters(userName);
		userName = clsInputValidate::removeSpaces(userName);

		// check if the userName is already existin the database.
		while (clsUser::ISUserExist(userName))
		{
			system("cls");
			_DrawScreenHeader("\t Add New User Screen");

			char tryAgain = 'n';
			std::cout << "\nA user with the username '" << userName << "' already exists.\n";
			std::cout << "Do you want to try a different username? (Y / N): ";
			tryAgain = clsInputValidate::get_char();
			if (std::tolower(tryAgain) != 'y')
			{
				std::cout << "The Operation has been Canceled.\n";
				return;
			}

			system("cls");
			_DrawScreenHeader("\t Add New User Screen");

			userName = clsInputValidate::get_string("Please enter a new username (all letters in lowercase, without spaces): ");
			userName = clsInputValidate::lowerAllStringLetters(userName);
			userName = clsInputValidate::removeSpaces(userName);
		}

		system("cls");
		_DrawScreenHeader("\t Add New User Screen");

		clsUser newUser = clsUser::CreateNewUser(userName);

		_ReadUserInfo(newUser);

		system("cls");
		_DrawScreenHeader("\t Add New User Screen");

		std::cout << "\n\nUser Information:\n";
		_PrintUserInfo(newUser);

		char answer = 'n';
		std::cout << "\n\nDo you want to save this information? (Y / N): ";
		answer = clsInputValidate::get_char();

		if (tolower(answer) != 'y')
		{
			std::cout << "\nOperation canceled. The information was not saved.\n";
			return;
		}

		system("cls");
		_DrawScreenHeader("\t Add New User Screen");

		clsUser::enSaveResults saveResult = newUser.Save();

		switch (saveResult)
		{
		case clsUser::svSucceeded:
			std::cout << "\nUser Added Successfully :)\n";
			_PrintUserInfo(newUser);
			break;
		case clsUser::svFailedEmptyObj:
			std::cout << "Error User Was Not Saved Because it's Empty :(\n";
			break;
		case clsUser::svFailedUserExists:
			std::cout << "\nError User Was Not Saved Because UserName is used!\n";
			break;
		default:
			break;
		}
	}
};
