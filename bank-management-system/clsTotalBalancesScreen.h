#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsTotalBalancesScreen : protected clsScreen {
private:
	static void _PrintClientRecordBalanceLine(const clsBankClient& client) {
		std::cout << std::setw(25) << std::left << "" << "| " << std::setw(15) << std::left << client.accountNumber();
		std::cout << "| " << std::setw(40) << std::left << client.fullName();
		std::cout << "| " << std::setw(12) << std::left << client.getAccountBalance();
	}

public:
	static void ShowTotalBalances()
	{
		std::vector <clsBankClient> vClients = clsBankClient::getClientsList();

		std::string Title = "\t  Balances List Screen";
		std::string SubTitle = "\t    (" + std::to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << std::setw(25) << std::left << "" << "\n\t\t_____________________________________________";
		std::cout << "_________________________________________\n" << std::endl;
		std::cout << std::setw(25) << std::left << "" << "| " << std::left << std::setw(15) << "Account Number";
		std::cout << "| " << std::left << std::setw(40) << "Client Name";
		std::cout << "| " << std::left << std::setw(12) << "Balance\n";
		std::cout << std::setw(25) << std::left << "" << "\n\t\t_____________________________________________";
		std::cout << "_________________________________________\n" << std::endl;

		double totalBalances = clsBankClient::getTotalBalances();
		if (vClients.size() == 0)
			std::cout << "\t\t\t\tNo Clients Available In the System!";
		else
			for (clsBankClient Client : vClients)
			{
				_PrintClientRecordBalanceLine(Client);
				std::cout << std::endl;
			}
		std::cout << std::setw(25) << std::left << "" << "\n\t\t_____________________________________________";
		std::cout << "_________________________________________\n" << std::endl;
		std::cout << std::setw(8) << std::left << "" << "\t\t\t\t\tTotal Balances = " << totalBalances << std::endl;
		std::cout << std::setw(8) << std::left << "" << "\t\t\t( " << util::convertNumberToText(totalBalances) << ")";
	}
};
