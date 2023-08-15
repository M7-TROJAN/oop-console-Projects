#pragma once

#include <iostream>
#include "clsScreen.h"
#include "inputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include <iomanip>

class clsManageUsers :protected clsScreen
{
private:
	enum enManageUsersMenuOptions {
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMene = 6
	};

	static enManageUsersMenuOptions _ReadManageUsersMenuOption() {
		short Choice = clsInputValidate::getInputInRange(1, 6);
		return (enManageUsersMenuOptions)Choice;
	}

	static void _GoBackToManageUsersMenu()
	{
		std::cout << std::setw(50) << std::left << "" << "\n\tPress any key to go back to Main Menu...";
		system("pause > nul");
		ManageUsersMenu();
	}

	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::AddNewUser();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::DeleteUser();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::UpdateUser();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::FindUser();
	}

	static void _PerformManageUsersMenuOption(enManageUsersMenuOptions option) {
		switch (option)
		{
		case clsManageUsers::eListUsers:
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eAddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case clsManageUsers::eMainMene:
			// do nothing here the main screen will handle it :-) ;
			break;
		default:
			break;
		}
	}

public:
	static void ManageUsersMenu() {
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\tManage Users Screen");
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t\tManage Users Menu\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] List Users.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Add New User.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Delete User.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Update User.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] Find User.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menu.\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "Choose What DO You Want To DO [1 to 6]?: ";

		_PerformManageUsersMenuOption((_ReadManageUsersMenuOption()));
	}
};
