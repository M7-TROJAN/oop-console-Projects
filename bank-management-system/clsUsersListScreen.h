#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsListUsersScreen :protected clsScreen {
	static void _PrintUserRecordLine(const clsUser& user)
	{
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(15) << user.GetUserName();
		std::cout << "| " << std::left << std::setw(20) << user.fullName();
		std::cout << "| " << std::left << std::setw(12) << user.getPhone();
		std::cout << "| " << std::left << std::setw(25) << user.getEmail();
		std::cout << "| " << std::left << std::setw(10) << user.GetPassword();
		std::cout << "| " << std::left << std::setw(12) << user.GetPermissions();
	}
public:
	static void ShowUsersList()
	{
		std::vector<clsUser> vUsers = clsUser::GetUsersList();
		std::string title = "\tUsers List Screen";
		std::string subTitle = "\t  (" + std::to_string(vUsers.size()) + ") User(s).";

		_DrawScreenHeader(title, subTitle);
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(15) << "UserName";
		std::cout << "| " << std::left << std::setw(20) << "Full Name";
		std::cout << "| " << std::left << std::setw(12) << "Phone";
		std::cout << "| " << std::left << std::setw(25) << "Email";
		std::cout << "| " << std::left << std::setw(10) << "Password";
		std::cout << "| " << std::left << std::setw(12) << "Permissions";
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
		if (vUsers.size() == 0 || vUsers.empty())
			std::cout << "\t\t\t\tNo Users Available In the System!";
		else
			for (const clsUser& user : vUsers)
			{
				_PrintUserRecordLine(user);
				std::cout << std::endl;
			}
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
	}
};
