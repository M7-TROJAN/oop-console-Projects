#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Global.h"
#include "clsUser.h"
class clsScreen
{
private:
	static void _Draw_Date_Time() {
		time_t currentTime = time(0);    // time(0) returns number of secs since jan. 1, 1970 midnight

		tm Now;
		localtime_s(&Now, &currentTime);

		short hour12 = Now.tm_hour % 12;
		const char* amPmIndicator = (Now.tm_hour < 12) ? "AM" : "PM";

		// check if hour12 is equal  0
		if (hour12 == 0)
			hour12 = 12; // Convert 0 to 12 in the 12-hour time format

		// print Date
		std::cout << std::setw(37) << std::left << "";
		printf("\t\t    %.2d/%.2d/%.4d\n", Now.tm_mday, Now.tm_mon + 1, Now.tm_year + 1900);

		// print time
		std::cout << std::setw(37) << std::left << "";
		printf("\t\t     %.2d:%.2d %s\n", hour12, Now.tm_min, amPmIndicator);

		// print the userName Of tthe CurrentUser
		std::cout << std::setw(40) << std::left << "\t\t" << CurrentUser.GetUserName() << std::endl;
	}
protected:
	static void _DrawScreenHeader(std::string title, std::string subTitle = "") {
		_Draw_Date_Time();

		std::cout << std::setw(37) << std::left << "" << "___________________________________________";
		std::cout << "\n\n" << std::setw(37) << std::left << "\t" << title;
		if (!subTitle.empty())
		{
			std::cout << "\n\n" << std::setw(37) << std::left << "\t" << subTitle;
		}
		std::cout << "\n" << std::setw(37) << std::left << "" << "___________________________________________\n\n";
	}

	static bool CheckAccessRights(clsUser::enPermissions Permission) {
		if (!CurrentUser.CheckAccessPermission(Permission))
		{
			std::cout << std::setw(40) << std::left << "" << "================================================\n";
			std::cout << std::setw(37) << std::left << "" << "\t\t\t Access Denied\n";
			std::cout << std::setw(40) << std::left << "" << "You don't have permission to perform this action.\n";
			std::cout << std::setw(40) << std::left << "" << "Please contact your administrator for assistance.\n";
			std::cout << std::setw(40) << std::left << "" << "=================================================\n";
			return false;
		}

		return true;
	}
};
