#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "inputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOptions {
		eListClients = 1,
		eAddNewClient = 2,
		eDeleteClient = 3,
		eUpdateClient = 4,
		eFindClient = 5,
		eTransactions = 6,
		eManageUsers = 7,
		eLoginRegister = 8,
		eCurrencyExchange = 9,
		eLogOut = 10
	};

	static enMainMenuOptions _ReadMainMenueOption() {
		short Choice = clsInputValidate::getInputInRange(1, 10);
		return (enMainMenuOptions)Choice;
	}

	static void _GoBackToMainMenu() {
		std::cout << std::setw(50) << std::left << "" << "\n\tPress any key to go back to Main Menu...";
		system("pause > nul");
		ShowMainMenu();
	}

	static void _ShowAllClientsScreen() {
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen() {
		clsAddNewClientScreen::AddNewClient();
	}

	static void _ShowDeleteClientScreen() {
		clsDeleteClientScreen::DeleteClient();
	}

	static void _ShowUpdateClientScreen() {
		clsUpdateClientScreen::UpdateClient();
	}

	static void _ShowFindClientScreen() {
		clsFindClientScreen::FindClient();
	}

	static void _ShowTransactionsMenue() {
		clsTransactionsScreen::TransactionsMenue();
	}

	static void _ShowManageUsersMenue() {
		clsManageUsers::ManageUsersMenu();
	}

	static void _ShowLoginRegisterScreen() {
		clsLoginRegisterScreen::LoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeMainMenue() {
		clsCurrencyExchangeMainScreen::CurrenciesMenue();
	}

	static void _Logout() {
		CurrentUser = clsUser::Find("", "");

		/*
		clsLoginScreen::ShowLoginScreen()
		No mahmoud this is will make 'circular reference ⛔' don't be stupid
		*/
	}

	static void _PerfromMainMenueOption(enMainMenuOptions MainMenuOption) {
		switch (MainMenuOption)
		{
		case enMainMenuOptions::eListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOptions::eAddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOptions::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOptions::eTransactions:
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenu();
			break;
		case enMainMenuOptions::eManageUsers:
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenu();
			break;
		case enMainMenuOptions::eLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOptions::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeMainMenue();
			_GoBackToMainMenu();
			break;
		case enMainMenuOptions::eLogOut:
			system("cls");
			_Logout();
			break;
		}
	}

public:
	static void ShowMainMenu()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain");
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t\t   Main Menu Screen\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1]  Show Client List.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2]  Add New Client.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3]  Delete Client.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4]  Update Client Info.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5]  Find Client.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[6]  Transactions.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[7]  Manage Users.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[8]  Login Register Screen.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[9]  Currency Exchange.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[10] Logout.\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "Choose What DO You Want To DO [1 to 10]?: ";

		_PerfromMainMenueOption((_ReadMainMenueOption()));
	}
};
