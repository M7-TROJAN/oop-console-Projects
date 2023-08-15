#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "inputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:

	// Print Currency information
	static void _PrintCurrency(clsCurrency Currency)
	{
		std::cout << "\nCurrency Card:\n";
		std::cout << "_____________________________\n";
		std::cout << "\nCountry    : " << Currency.Country();
		std::cout << "\nCode       : " << Currency.CurrencyCode();
		std::cout << "\nName       : " << Currency.CurrencyName();
		std::cout << "\nRate(1$) = : " << Currency.Rate();
		std::cout << "\n_____________________________\n";
	}

public:
	static void FindCurrency() {
		_DrawScreenHeader("\tFind Currency Screen");

		std::string searchQuery = clsInputValidate::get_string("Please Enter CurrencyCode Or Country: ");

		// check if the Currency is not exist.
		while (!clsCurrency::IsCurrencyExist(searchQuery))
		{
			system("cls");
			_DrawScreenHeader("\tFind Currency Screen");
			char tryAgain = 'n';
			std::cout << "Currency (" << searchQuery << ") Is Not Found.\n";
			std::cout << "Do You Want to Try Again ? (Y / N) : ";
			tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				return;
			}
			system("cls");
			_DrawScreenHeader("\tFind Currency Screen");
			searchQuery = clsInputValidate::get_string("Please Enter CurrencyCode Or Country: ");
		}

		clsCurrency currency = clsCurrency::FindCurrencyByCodeOrCountry(searchQuery);

		system("cls");
		_DrawScreenHeader("\tFind Currency Screen");
		_PrintCurrency(currency);
	}
};
