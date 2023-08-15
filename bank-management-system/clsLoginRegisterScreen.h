#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginRegisterScreen : protected clsScreen {
private:

	static void _PrintLoginRegisterRecordLine(const clsUser::stLoginRegisterRecord& record)
	{
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(35) << record.DateTime;
		std::cout << "| " << std::left << std::setw(20) << record.UserName;
		std::cout << "| " << std::left << std::setw(20) << record.Password;
		std::cout << "| " << std::left << std::setw(10) << record.Permissions;
	}

public:

	static void LoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::pLoginRegisterScreen))
		{
			return;
		}

		std::vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();
		std::string title = "  Login Register List Screen";
		std::string subTitle = "\t   (" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

		_DrawScreenHeader(title, subTitle);
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(35) << "Date/Time";
		std::cout << "| " << std::left << std::setw(20) << "UserName";
		std::cout << "| " << std::left << std::setw(20) << "Password";
		std::cout << "| " << std::left << std::setw(10) << "Permissions";
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
		if (vLoginRegisterRecord.size() == 0 || vLoginRegisterRecord.empty())
			std::cout << "\t\t\t\tNo Logins Available In the System!";
		else
			for (clsUser::stLoginRegisterRecord record : vLoginRegisterRecord)
			{
				_PrintLoginRegisterRecordLine(record);
				std::cout << std::endl;
			}
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
	}
};
