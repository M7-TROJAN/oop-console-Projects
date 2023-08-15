#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "inputValidate.h"
#include "clsUtil.h"
#include "clsCurrency.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:
	enum enCurrencyExchangeMenuOptions
	{
		eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
		eCurrencyCalculator = 4, eMainMenu = 5
	};

	static enCurrencyExchangeMenuOptions _ReadCurrenciesMenueOptions() {
		short Choice = clsInputValidate::getInputInRange(1, 5);
		return (enCurrencyExchangeMenuOptions)Choice;
	}

	static void _GoBackToCurrenciesMenu() {
		std::cout << std::setw(50) << std::left << "" << "\n\tPress any key to go back to Currency Exchange Menue...";
		system("pause > nul");
		CurrenciesMenue();
	}

	static void _ShowCurrenciesListScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesList();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::FindCurrency();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::UpdateCurrencyRate();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::CurrencyCalculatorScreen();
	}

	static void _PerfromCurrenciesMenueOption(enCurrencyExchangeMenuOptions option) {
		switch (option)
		{
		case clsCurrencyExchangeMainScreen::eListCurrencies:
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrenciesMenu();
			break;
		case clsCurrencyExchangeMainScreen::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenu();
			break;
		case clsCurrencyExchangeMainScreen::eUpdateRate:
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrenciesMenu();
			break;
		case clsCurrencyExchangeMainScreen::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrenciesMenu();
			break;
		case clsCurrencyExchangeMainScreen::eMainMenu:
			//do nothing here the main screen will handle it :-) ;
		default:
			break;
		}
	}

public:
	static void CurrenciesMenue() {
		system("cls");
		_DrawScreenHeader(" Currency Exchange Main Screen");
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t\tCurrency Exchange Menue\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] List Currencies.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Find Currency.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Update Rate.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Currency Calculator.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] Main Menu.\n";
		std::cout << std::setw(37) << std::left << "" << "===========================================\n";
		std::cout << std::setw(37) << std::left << "" << "Choose What DO You Want To DO [1 to 5]?: ";

		_PerfromCurrenciesMenueOption((_ReadCurrenciesMenueOptions()));
	}
};
