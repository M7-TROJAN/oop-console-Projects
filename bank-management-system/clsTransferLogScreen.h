#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsTransferLogScreen : protected clsScreen
{
	static void _PrintTransferLogRecordLine(const clsBankClient::stTrnsferLogRecord& TransferLogRecord)
	{
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(23) << TransferLogRecord.DateTime;
		std::cout << "| " << std::setw(8) << std::left << TransferLogRecord.SourceAccountNumber;
		std::cout << "| " << std::setw(8) << std::left << TransferLogRecord.DestinationAccountNumber;
		std::cout << "| " << std::setw(8) << std::left << TransferLogRecord.Amount;
		std::cout << "| " << std::setw(10) << std::left << TransferLogRecord.srcBalanceAfter;
		std::cout << "| " << std::setw(10) << std::left << TransferLogRecord.destBalanceAfter;
		std::cout << "| " << std::setw(8) << std::left << TransferLogRecord.UserName;
	}

public:

	static void TransferLogScreen()
	{
		std::vector <clsBankClient::stTrnsferLogRecord> vTrnsferLogRecord = clsBankClient::GetTransfersLogList();
		std::string title = "  Transfer Log List Screen";
		std::string subTitle = "\t   (" + to_string(vTrnsferLogRecord.size()) + ") Record(s).";

		_DrawScreenHeader(title, subTitle);
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(23) << "Date/Time";
		std::cout << "| " << std::left << std::setw(8) << "s.Acct";
		std::cout << "| " << std::left << std::setw(8) << "d.Acct";
		std::cout << "| " << std::left << std::setw(8) << "Amount";
		std::cout << "| " << std::left << std::setw(10) << "s.Balance";
		std::cout << "| " << std::left << std::setw(10) << "d.Balance";
		std::cout << "| " << std::left << std::setw(8) << "User";
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
		if (vTrnsferLogRecord.size() == 0 || vTrnsferLogRecord.empty())
			std::cout << "\t\t\t\t\tNo Transfers Available In the System!";
		else
			for (clsBankClient::stTrnsferLogRecord record : vTrnsferLogRecord)
			{
				_PrintTransferLogRecordLine(record);
				std::cout << std::endl;
			}
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
	}
};
