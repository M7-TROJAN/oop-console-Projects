#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "inputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	// Print Currency information
	static void _PrintCurrencyCard(clsCurrency Currency, std::string Title = "Currency Card:")
	{
		std::cout << "\n" << Title << "\n";
		std::cout << "_____________________________\n";
		std::cout << "\nCountry    : " << Currency.Country();
		std::cout << "\nCode       : " << Currency.CurrencyCode();
		std::cout << "\nName       : " << Currency.CurrencyName();
		std::cout << "\nRate(1$) = : " << Currency.Rate();
		std::cout << "\n_____________________________\n";
	}

	static clsCurrency _GetCurrency(std::string message) {
		std::string CurrencyCode = clsInputValidate::get_string(message);

		// check if the Currency is not exist.
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			system("cls");
			_DrawScreenHeader("\tCurrency Calculator Screen");
			char tryAgain = 'n';
			std::cout << "Currency (" << CurrencyCode << ") Is Not Found.\n";
			std::cout << "Do You Want to Try Again ? (Y / N) : ";
			tryAgain = clsInputValidate::get_char();
			if (tolower(tryAgain) != 'y')
			{
				clsCurrency currency = clsCurrency::FindCurrencyByCodeOrCountry(CurrencyCode); // this will return empty obj
				return currency;
			}
			system("cls");
			_DrawScreenHeader("\tCurrency Calculator Screen");
			CurrencyCode = clsInputValidate::get_string("Please Enter CurrencyCode Or Country: ");
		}

		clsCurrency currency = clsCurrency::FindCurrencyByCodeOrCountry(CurrencyCode);

		return currency;
	}

	static float _ReadAmount()
	{
		float Amount = clsInputValidate::get_float("\nEnter Amount to Exchange: ");
		return Amount;
	}

	static void _PrintCalculationsResults(float amount, clsCurrency currency1, clsCurrency currency2)
	{
		_PrintCurrencyCard(currency1, "Convert From:");
		_PrintCurrencyCard(currency2, "Convert To:");

		float AmountInCurrrency2 = currency1.ConvertTo_otherCurrency(amount, currency2);

		std::cout << "\n" << amount << " " << currency1.CurrencyCode()
			<< " = " << AmountInCurrrency2 << " " << currency2.CurrencyCode() << std::endl;
	}

public:
	static void CurrencyCalculatorScreen()
	{
		_DrawScreenHeader("  Currency Calculator Screen");

		char Continue = 'y';

		while (std::tolower(Continue) == 'y')
		{
			system("cls");

			_DrawScreenHeader("Currency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
			if (CurrencyFrom.IsEmpty())
			{
				std::cout << "\nOperation was cancelled.\n";
				return;
			}

			clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
			if (CurrencyTo.IsEmpty())
			{
				std::cout << "\nOperation was cancelled.\n";
				return;
			}

			float Amount = _ReadAmount();

			// clear screen
			system("cls");
			_DrawScreenHeader("Currency Calculator Screen");

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

			Continue = clsInputValidate::get_char("\nDo You Want to perform another calculation ? (Y / N) : ");
		}
	}
};
