#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

class clsBankClient : public clsPerson
{
private:
	// private members
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	std::string _AccountNumber;
	std::string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;

	// private methods

	// Get an empty clsBankClient object
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0.0);
	}

	struct stTrnsferLogRecord;

	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTrnsferLogRecord TrnsferLogRecord;

		vector<string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;
	}

	std::string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string UserName,
		string Separator = "#//#")
	{
		std::string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemDateTimeString() + Separator;
		TransferLogRecord += accountNumber() + Separator;
		TransferLogRecord += DestinationClient.accountNumber() + Separator;
		TransferLogRecord += to_string(Amount) + Separator;
		TransferLogRecord += to_string(accountBalance) + Separator;
		TransferLogRecord += to_string(DestinationClient.getAccountBalance()) + Separator;
		TransferLogRecord += UserName;
		return TransferLogRecord;
	}

	// Convert a line of text to a clsBankClient object
	static clsBankClient _ConvertLineToClientObj(const std::string& line, const std::string& separator = "#//#")
	{
		std::vector<std::string> vClients = clsString::Split(line, separator);
		if (vClients.size() != 7)
			return _GetEmptyClientObject();

		return clsBankClient(enMode::UpdateMode, vClients[0], vClients[1], vClients[2], vClients[3], vClients[4],
			vClients[5], std::stof(vClients[6]));
	}

	// Convert a clsBankClient object to a line of text
	static std::string _ConvertClientObjToLine(clsBankClient client, const std::string& separator = "#//#")
	{
		std::string line;
		line += client.getFirstName() + separator;
		line += client.getLastName() + separator;
		line += client.getEmail() + separator;
		line += client.getPhone() + separator;
		line += client._AccountNumber + separator;
		line += client._PinCode + separator;
		line += std::to_string(client._AccountBalance) + separator;
		return line;
	}

	// Load clients' data from file
	static std::vector<clsBankClient> _LoadClientsDataFromFile()
	{
		std::vector<clsBankClient> vClients;

		std::ifstream file("Clients.txt");
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				clsBankClient client = _ConvertLineToClientObj(line, "#//#");
				vClients.push_back(client);
			}
			file.close();
		}
		else
		{
			std::cerr << "Error opening file: " << "Clients.txt" << std::endl;
		}
		return vClients;
	}

	// Save clients' data to file
	static void _SaveClientsDataToFile(std::vector<clsBankClient> vClients)
	{
		std::fstream file;
		file.open("Clients.txt", std::ios::out); // overwrite
		std::string dataLine;
		if (file.is_open())
		{
			for (clsBankClient client : vClients)
			{
				if (!client._MarkedForDelete) {
					// we are only write records that are not marked for delete.
					dataLine = _ConvertClientObjToLine(client, "#//#");
					file << dataLine << std::endl;
				}
			}
			file.close();
		}
		else
		{
			std::cerr << "Error opening file: " << "Clients.txt" << std::endl;
		}
	}

	// Update client data
	void _Update()
	{
		std::vector<clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& c : vClients)
		{
			if (c.accountNumber() == accountNumber())
			{
				c = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}

	// Add new client data
	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjToLine(*this));
	}

	// Add data line to file
	void _AddDataLineToFile(std::string dataLine) {
		std::fstream file;
		file.open("Clients.txt", std::ios::out | std::ios::app);

		if (file.is_open())
		{
			file << dataLine << std::endl;

			file.close();
		}
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName) {
		std::string dataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		std::fstream file;
		file.open("TransfersLog.txt", std::ios::out | std::ios::app);

		if (file.is_open())
		{
			file << dataLine << std::endl;

			file.close();
		}
	}

public:
	clsBankClient(enMode mode, std::string fName, std::string lName,
		std::string email, std::string phone, std::string accountNumber, std::string pin, float accountBalance) :
		clsPerson(fName, lName, email, phone)
	{
		_Mode = mode;
		_AccountNumber = accountNumber;
		_PinCode = pin;
		_AccountBalance = accountBalance;
	}

	struct stTrnsferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;
	};

	// Check if the clsBankClient object is empty.
	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	// Get the account number associated with the clsBankClient.
	std::string accountNumber() const {
		return _AccountNumber;
	}

	// Setter and Getter methods for modifying and accessing PinCode
	void setPinCode(std::string PinCode)
	{
		_PinCode = PinCode;
	}
	std::string getPinCode() const {
		return _PinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) std::string pinCode;

	// Setter and Getter methods for modifying and accessing Account Balance
	void setAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	double getAccountBalance() const {
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) double accountBalance;

	// Find a client by account number and optional pin code
	static clsBankClient find(std::string accountNumber, std::string pinCode = "")
	{
		std::vector<clsBankClient> vClients;

		std::ifstream file("Clients.txt");

		if (file.is_open())
		{
			std::string line;
			while (getline(file, line))
			{
				clsBankClient client = _ConvertLineToClientObj(line);
				if (pinCode.empty())
				{
					if (client._AccountNumber == accountNumber)
					{
						file.close();
						return client;
					}
				}
				else
				{
					if (client._AccountNumber == accountNumber && client._PinCode == pinCode)
					{
						file.close();
						return client;
					}
				}
			}
			file.close();
		}
		return _GetEmptyClientObject();
	}

	// Enumeration for save results
	enum enSaveResults { svFailedEmptyObj = 0, svSucceeded = 1, svFailedAccountNumberExist };

	// Save the client data
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			return enSaveResults::svFailedEmptyObj;

		case clsBankClient::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;

		case clsBankClient::AddNewMode:
			// this will add New Record to the file or database
			if (clsBankClient::isClientExist(_AccountNumber)) {
				return enSaveResults::svFailedAccountNumberExist;
			}
			else {
				_AddNew();

				// set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		default:
			break;
		}
	}

	// Check if a client with a specific account number exists
	static bool isClientExist(std::string accountNumber) {
		clsBankClient client = clsBankClient::find(accountNumber);
		return (!client.isEmpty());
	}

	// Get a new client object with AddNew mode
	static clsBankClient createNewClient(std::string accountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
	}

	bool Delete() {
		std::vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& client : vClients)
		{
			if (client.accountNumber() == _AccountNumber)
			{
				client._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static std::vector<clsBankClient> getClientsList() {
		return _LoadClientsDataFromFile();
	}

	static double getTotalBalances() {
		std::vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		double totalBalances = 0.0;

		for (const clsBankClient& client : vClients)
		{
			totalBalances += client.getAccountBalance();
		}

		return totalBalances;
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient, string user_name) {
		if (Amount > accountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, user_name);
		return true;
	}

	static vector<stTrnsferLogRecord> GetTransfersLogList()
	{
		vector<stTrnsferLogRecord> vTransferLogRecord;

		std::ifstream file("TransfersLog.txt");
		if (file.is_open())
		{
			std::string line;
			stTrnsferLogRecord TransferRecord;
			while (std::getline(file, line))
			{
				TransferRecord = _ConvertTransferLogLineToRecord(line);
				vTransferLogRecord.push_back(TransferRecord);
			}
			file.close();
		}
		return vTransferLogRecord;
	}
};
