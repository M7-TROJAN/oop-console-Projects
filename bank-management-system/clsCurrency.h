#pragma once
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>

class clsCurrency
{
private:
	enum enMode
	{
		EmptyMode = 0,
		UpdateMode = 1
	};
	enMode _Mode;

	std::string _Country;
	std::string _CurrencyCode;
	std::string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(std::string Line, std::string Separator = "#//#")
	{
		std::vector<std::string> vCurrencyData = clsString::Split(Line, Separator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
			std::stod(vCurrencyData[3]));
	}

	static std::string _ConvertCurrencyObjectToLine(clsCurrency Currency, std::string Separator = "#//#")
	{
		std::string str_CurrencyRecord = "";
		str_CurrencyRecord += Currency.Country() + Separator;
		str_CurrencyRecord += Currency.CurrencyCode() + Separator;
		str_CurrencyRecord += Currency.CurrencyName() + Separator;
		str_CurrencyRecord += std::to_string(Currency.Rate()) + Separator;

		return str_CurrencyRecord;
	}

	static std::vector<clsCurrency> _LoadCurrencyDataFromFile()
	{
		std::vector<clsCurrency> vCurrencies;

		std::ifstream file("Currencies.txt");

		if (file.is_open())
		{
			std::string line;

			while (std::getline(file, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line);
				vCurrencies.push_back(currency);
			}

			file.close();
		}
		return vCurrencies;
	}

	static void _SaveCurrencyDataToFile(std::vector<clsCurrency> vCurrencies)
	{
		std::fstream file;
		file.open("Currencies.txt", std::ios::out); // overwrite

		if (file.is_open())
		{
			std::string dataLine;
			for (clsCurrency currency : vCurrencies)
			{
				dataLine = _ConvertCurrencyObjectToLine(currency);

				file << dataLine << std::endl;
			}
			file.close();
		}
	}

	void _UpdateDatabase()
	{
		std::vector<clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();

		for (clsCurrency& currency : vCurrencies)
		{
			if (currency.CurrencyCode() == CurrencyCode())
			{
				currency = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObj()
	{
		return clsCurrency(EmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode mode, std::string country, std::string currency_Code, std::string currency_Name, float rate)
		: _Mode(std::move(mode)), _Country(std::move(country)), _CurrencyCode(std::move(currency_Code)),
		_CurrencyName(std::move(currency_Name)), _Rate(std::move(rate)) {}

	bool IsEmpty() const
	{
		return _Mode == enMode::EmptyMode;
	}

	std::string Country() const
	{
		return _Country;
	}

	std::string CurrencyCode() const
	{
		return _CurrencyCode;
	}

	std::string CurrencyName() const
	{
		return _CurrencyName;
	}

	void UpdateRate(float newRate)
	{
		_Rate = newRate;
		_UpdateDatabase();
	}

	float Rate() const
	{
		return _Rate;
	}

	static clsCurrency FindCurrencyByCodeOrCountry(const std::string& searchQuery)
	{
		std::string normalizedQuery = clsString::UpperAllString(searchQuery);

		std::ifstream currencyFile("Currencies.txt");

		if (currencyFile.is_open())
		{
			std::string line;

			while (std::getline(currencyFile, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line);

				if (clsString::UpperAllString(currency.CurrencyCode()) == normalizedQuery)
				{
					currencyFile.close();
					return currency;
				}

				if (clsString::UpperAllString(currency.Country()) == normalizedQuery)
				{
					currencyFile.close();
					return currency;
				}
			}

			currencyFile.close();
		}

		// Return an Empty currency object if not found
		return _GetEmptyCurrencyObj();
	}

	static bool IsCurrencyExist(std::string searchQuery)
	{
		clsCurrency C = clsCurrency::FindCurrencyByCodeOrCountry(searchQuery);
		return (!C.IsEmpty());
	}

	static std::vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	float ConvertTo_USD(float amount)
	{
		return float(amount / Rate());
	}

	float ConvertTo_otherCurrency(float amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertTo_USD(amount);

		if (Currency2.CurrencyCode() == "USD")
			return AmountInUSD;

		return float(AmountInUSD * Currency2.Rate());
	}
};
