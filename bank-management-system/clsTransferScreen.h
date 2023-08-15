#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "inputValidate.h"
#include "Global.h"

class clsTransferScreen : protected clsScreen {
private:

	static std::string ReadClientAccountNumber(const std::string& prompt) {
		std::string accountNumber;
		do {
			accountNumber = clsInputValidate::get_string(prompt);
			if (!clsBankClient::isClientExist(accountNumber)) {
				std::cout << "\nClient with account number [" << accountNumber << "] does not exist."
					<< " Do you want to try again? (Y / N) : ";
				char tryAgain = clsInputValidate::get_char();
				if (tolower(tryAgain) != 'y') {
					return "";
				}
				system("cls");
				_DrawScreenHeader("\t   Transfer Screen");
			}
			else {
				break;
			}
		} while (true);
		return accountNumber;
	}

	static void PrintClientInfo(const clsBankClient& client) {
		std::cout << "\nClient details:";
		std::cout << "\n____________________________________";
		std::cout << "\nFull Name   : " << client.fullName();
		std::cout << "\nAcc. Number : " << client.accountNumber();
		std::cout << "\nBalance     : " << client.getAccountBalance();
		std::cout << "\n____________________________________\n";
	}

public:

	static void Transfer() {
		_DrawScreenHeader("\t   Transfer Screen");

		std::string sourceAccountNumber = ReadClientAccountNumber("\nPlease Enter Source Client Account Number: ");
		if (sourceAccountNumber.empty()) {
			return;
		}

		clsBankClient sourceClient = clsBankClient::find(sourceAccountNumber);
		PrintClientInfo(sourceClient);

		if (sourceClient.accountBalance == 0) {
			std::cout << "Client balance is currently zero. You are unable to make transfers at this time.\n";
			return;
		}

		std::string destAccountNumber = ReadClientAccountNumber("\nPlease Enter Destination Client Account Number: ");
		if (destAccountNumber.empty()) {
			return;
		}

		clsBankClient destClient = clsBankClient::find(destAccountNumber);
		PrintClientInfo(destClient);

		double amount = clsInputValidate::get_Positive_double("\nPlease Enter The Amount: ");

		while (amount > sourceClient.accountBalance) {
			std::cout << "\nAmount exceeds the available balance. You can make a transfer up to: "
				<< sourceClient.accountBalance << std::endl;

			std::cout << "Do you want to try again? (Y / N) : ";
			char tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y') {
				std::cout << "\nOperation was cancelled.\n";
				return;
			}
			system("cls");
			_DrawScreenHeader("\t   Transfer Screen");
			PrintClientInfo(sourceClient);
			PrintClientInfo(destClient);
			amount = clsInputValidate::get_Positive_double("\nPlease Enter The Amount: ");
		}

		char answer = clsInputValidate::get_char("\nAre you sure you want to perform this transaction? (Y / N) : ");
		if (tolower(answer) != 'y') {
			std::cout << "\nOperation was cancelled.\n";
			return;
		}

		if (sourceClient.Transfer(amount, destClient, CurrentUser.GetUserName())) {
			system("cls");
			_DrawScreenHeader("\t   Transfer Screen");
			std::cout << "\nTransfer done successfully\n";
		}
		else {
			std::cout << "\nTransfer failed\n";
		}

		PrintClientInfo(sourceClient);
		PrintClientInfo(destClient);
	}
};
