#pragma once
#include <iostream>
#include "clsScreen.h"
#include "inputValidate.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsDepositScreen.h"
#include "clsWithDrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>

class clsTransactionsScreen :protected clsScreen
{
private:
	enum enTransactionsMenuOptions
	{
		eDeposit = 1, eWithdraw = 2, eTotalBalances = 3,
		eTransfer = 4, eTransferLog = 5, eMainMenu = 6
	};

	static enTransactionsMenuOptions _ReadTransactionsMenueOption() {
		short Choice = clsInputValidate::getInputInRange(1, 6);
		return (enTransactionsMenuOptions)Choice;
	}

	static void _GoBackToTransactionsMenu() {
		std::cout << std::setw(50) << std::left << "" << "\n\tPress any key to go back to Transactions Menu...";
		system("pause > nul");
		TransactionsMenue();
	}

	static void _ShowDepositScreen() {
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithDrawScreen() {
		clsWithDrawScreen::ShowWithDrawScreen();
	}

	static void _ShowTotalBalances() {
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _PerfromTransactionsMenueOption(enTransactionsMenuOptions option) {
		switch (option)
		{
		case enTransactionsMenuOptions::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOptions::eWithdraw:
			system("cls");
			_ShowWithDrawScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOptions::eTotalBalances:
			system("cls");
			_ShowTotalBalances();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOptions::eTransfer:
			system("cls");
			clsTransferScreen::Transfer();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOptions::eTransferLog:
			system("cls");
			clsTransferLogScreen::TransferLogScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenuOptions::eMainMenu:
			// do nothing here the main screen will handle it :-) ;
			break;
		}
	}
public:
	static void TransactionsMenue() {
		if (!CheckAccessRights(clsUser::pTransactions))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\tTransactions Screen");
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t\tTransactions Menue\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] Deposit.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Withdraw.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Total Balances.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Transfer.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] Transfer Log.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menu.\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "Choose What DO You Want To DO [1 to 6]?: ";

		_PerfromTransactionsMenueOption((_ReadTransactionsMenueOption()));
	}
};
