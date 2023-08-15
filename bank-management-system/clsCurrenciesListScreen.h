#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsCurrenciesListScreen : protected clsScreen
{
private:
	static void _PrintCurrencyRecordLine(const clsCurrency& currency)
	{
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(30) << currency.Country();
		std::cout << "| " << std::left << std::setw(8) << currency.CurrencyCode();
		std::cout << "| " << std::left << std::setw(45) << currency.CurrencyName();
		std::cout << "| " << std::left << std::setw(10) << currency.Rate();
	}
public:
	static void ShowCurrenciesList()
	{
		std::vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		std::string title = "\tCurrencies List Screen";
		std::string subTitle = "\t  (" + std::to_string(vCurrencies.size()) + ") Currency.";

		_DrawScreenHeader(title, subTitle);
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(30) << "Country";
		std::cout << "| " << std::left << std::setw(8) << "Code";
		std::cout << "| " << std::left << std::setw(45) << "Name";
		std::cout << "| " << std::left << std::setw(10) << "Rate/(1$)";
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
		if (vCurrencies.size() == 0 || vCurrencies.empty())
			std::cout << "\t\t\t\tNo Users Available In the System!";
		else
			for (const clsCurrency& currency : vCurrencies)
			{
				_PrintCurrencyRecordLine(currency);
				std::cout << std::endl;
			}
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "___________________________________________________\n" << std::endl;
	}
};
