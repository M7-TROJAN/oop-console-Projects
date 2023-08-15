#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "InputValidate.h"

class clsDeleteUserScreen : protected clsScreen {
private:
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
	static void DeleteUser() {
		_DrawScreenHeader("\tDelete User Screen");

		std::string userName = clsInputValidate::get_string("Please enter the username you want to delete: ");
		userName = clsInputValidate::lowerAllStringLetters(userName);
		userName = clsInputValidate::removeSpaces(userName);

		// check if the User name is not exist.
		while (!clsUser::ISUserExist(userName))
		{
			system("cls");
			_DrawScreenHeader("\tDelete User Screen");

			char tryAgain = 'n';
			std::cout << "\nA user with the username '" << userName << "' Is Not Found.\n";
			std::cout << "Do you want to try a different username? (Y / N): ";
			tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				return;
			}

			system("cls");
			_DrawScreenHeader("\tDelete User Screen");
			userName = clsInputValidate::get_string("Please enter the username you want to delete: ");
		}

		system("cls");
		_DrawScreenHeader("\tDelete User Screen");

		clsUser user = clsUser::Find(userName);
		_PrintUserInfo(user);

		char answer = clsInputValidate::get_char("\nAre you sure you want to delete this user? (Y / N): ");
		if (tolower(answer) != 'y')
		{
			std::cout << "\nOperation canceled. The user with the username '" << userName << "' was not deleted.\n";
			return;
		}

		if (user.Delete()) {
			std::cout << "user With userName (" << userName << ") has been deleted successfully.\n";
		}
		else {
			std::cout << "An unexpected error occurred. The user was not deleted.\n";
		}
	}
};
