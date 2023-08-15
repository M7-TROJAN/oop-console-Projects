#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "inputValidate.h"

class clsFindUserScreen : protected clsScreen {
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
	static void FindUser()
	{
		_DrawScreenHeader("\tFind User Screen");

		std::string userName = clsInputValidate::get_string("Please enter the username you want to Search: ");

		// check if the User name is not exist.
		while (!clsUser::ISUserExist(userName))
		{
			system("cls");
			_DrawScreenHeader("\tFind User Screen");

			char tryAgain = 'n';
			std::cout << "\nA user with the username '" << userName << "' Is Not Found.\n";
			std::cout << "Do you want to try a different username? (Y / N): ";
			tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				return;
			}

			system("cls");
			_DrawScreenHeader("\tFind User Screen");
			userName = clsInputValidate::get_string("Please enter the username you want to Search: ");
		}

		clsUser user = clsUser::Find(userName);

		if (!user.IsEmpty())
		{
			std::cout << "\nUser Found :-)\n";
			_PrintUserInfo(user);
		}
		else
		{
			std::cout << "\nUser Was not Found :-(\n";
		}
	}
};
