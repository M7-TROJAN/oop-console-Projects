#pragma once
#include <iostream>
#include <vector>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "Global.h"
#include <iomanip>
class clsClientListScreen : protected clsScreen {
	static void printClientRecordLine(const clsBankClient& client)
	{
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(15) << client.accountNumber();
		std::cout << "| " << std::left << std::setw(20) << client.fullName();
		std::cout << "| " << std::left << std::setw(12) << client.getPhone();
		std::cout << "| " << std::left << std::setw(20) << client.getEmail();
		std::cout << "| " << std::left << std::setw(10) << client.getPinCode();
		std::cout << "| " << std::left << std::setw(12) << client.getAccountBalance();
	}
public:
	static void ShowClientsList()
	{
		if (!CheckAccessRights(clsUser::pListClients))
		{
			return;
		}

		std::vector<clsBankClient> vClients = clsBankClient::getClientsList();
		std::string title = "\tClient List Screen";
		std::string subTitle = "\t  (" + std::to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(title, subTitle);
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(15) << "Account Number";
		std::cout << "| " << std::left << std::setw(20) << "Client Name";
		std::cout << "| " << std::left << std::setw(12) << "Phone";
		std::cout << "| " << std::left << std::setw(20) << "Email";
		std::cout << "| " << std::left << std::setw(10) << "Pin Code";
		std::cout << "| " << std::left << std::setw(12) << "Balance";
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;
		if (vClients.size() == 0 || vClients.empty())
			std::cout << "\t\t\t\tNo Clients Available In the System!";
		else
			for (const clsBankClient& Client : vClients)
			{
				printClientRecordLine(Client);
				std::cout << std::endl;
			}
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;
	}
};
