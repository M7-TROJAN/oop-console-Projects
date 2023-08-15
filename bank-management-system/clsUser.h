#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>

class clsUser : public clsPerson {
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	std::string _UserName;
	std::string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector<string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = LoginRegisterDataLine[2];
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

	std::string _PrepareLogInRecord(std::string Seperator = "#//#")
	{
		std::string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += util::encryptText(Password) + Seperator;
		LoginRecord += std::to_string(Permissions);
		return LoginRecord;
	}

	// Get an empty clsBankClient object
	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	// Convert a line of text to a clsBankClient object
	static clsUser _ConvertLineToUserObj(const std::string& line, const std::string& separator = "#//#")
	{
		std::vector<std::string> vUsers = clsString::Split(line, separator);
		if (vUsers.size() != 7)
			return _GetEmptyUserObject();

		return clsUser(enMode::UpdateMode, vUsers[0], vUsers[1], vUsers[2], vUsers[3], vUsers[4],
			util::decryptText(vUsers[5]), std::stoi(vUsers[6]));
	}

	// Convert a clsBankClient object to a line of text
	static std::string _ConvertUserObjToLine(clsUser user, const std::string& separator = "#//#")
	{
		std::string userRecord = "";
		userRecord += user.FirstName + separator;
		userRecord += user.LastName + separator;
		userRecord += user.Email + separator;
		userRecord += user.Phone + separator;
		userRecord += user.UserName + separator;
		userRecord += util::encryptText(user.Password) + separator;
		userRecord += std::to_string(user.Permissions);

		return userRecord;
	}

	// Add data line to file
	void _AddDataLineToFile(const std::string& dataLine) {
		std::fstream file;
		file.open("Users.txt", std::ios::out | std::ios::app);

		if (file.is_open())
		{
			file << dataLine << std::endl;

			file.close();
		}
	}

	// Load clients' data from file
	static std::vector<clsUser> _LoadUsersDataFromFile()
	{
		std::vector<clsUser> vUsers;

		std::ifstream file("Users.txt");
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				clsUser user = _ConvertLineToUserObj(line, "#//#");
				vUsers.push_back(user);
			}
			file.close();
		}
		else
		{
			std::cerr << "Error opening file: " << "Clients.txt" << std::endl;
		}
		return vUsers;
	}

	// Save User's data to file
	static void _SaveUsersDataToFile(std::vector<clsUser> vUsers)
	{
		std::fstream file;
		file.open("Users.txt", std::ios::out); // overwrite
		std::string dataLine;
		if (file.is_open())
		{
			for (clsUser user : vUsers)
			{
				if (!user._MarkedForDelete) {
					// we are only write records that are not marked for delete.
					dataLine = _ConvertUserObjToLine(user, "#//#");
					file << dataLine << std::endl;
				}
			}
			file.close();
		}
		else
		{
			std::cerr << "Error opening file: " << "Users.txt" << std::endl;
		}
	}

	// Update user data
	void _Update()
	{
		std::vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& user : vUsers)
		{
			if (user.GetUserName() == _UserName)
			{
				user = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	// Add new client data
	void _AddNew() {
		_AddDataLineToFile(_ConvertUserObjToLine(*this));
	}

public:

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTransactions = 32,
		pManageUsers = 64, pLoginRegisterScreen = 128
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode mode, std::string fName, std::string lName,
		std::string email, std::string phone, std::string userName, std::string password, int permissions) :
		clsPerson(fName, lName, email, phone)
	{
		_Mode = mode;
		_UserName = userName;
		_Password = password;
		_Permissions = permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool ISMarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	std::string GetUserName() const {
		return _UserName;
	}

	void SetUserName(std::string UserName)
	{
		_UserName = UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) std::string UserName;

	void SetPassword(std::string Password)
	{
		_Password = Password;
	}

	std::string GetPassword() const {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) std::string Password;

	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	int GetPermissions() const {
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	// Find a client by account number and optional pin code
	static clsUser Find(const std::string& user_name, const std::string& pass = "")
	{
		std::ifstream file("Users.txt");

		if (file.is_open())
		{
			std::string line;
			while (getline(file, line))
			{
				clsUser user = _ConvertLineToUserObj(line);
				if (pass.empty())
				{
					if (user._UserName == user_name)
					{
						file.close();
						return user;
					}
				}
				else
				{
					if (user.GetUserName() == user_name && user.GetPassword() == pass)
					{
						file.close();
						return user;
					}
				}
			}
			file.close();
		}
		return _GetEmptyUserObject();
	}

	// Enumeration for save results
	enum enSaveResults { svFailedEmptyObj = 0, svSucceeded = 1, svFailedUserExists = 2 };

	// Save the client data
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			return enSaveResults::svFailedEmptyObj;

		case clsUser::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;

		case clsUser::AddNewMode:
			// this will add New Record to the file or database
			if (clsUser::ISUserExist(_UserName)) {
				return enSaveResults::svFailedUserExists;
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
	static bool ISUserExist(std::string user_name) {
		clsUser user = clsUser::Find(user_name);
		return (!user.IsEmpty());
	}

	// Get a new client object with AddNew mode
	static clsUser CreateNewUser(std::string user_name) {
		return clsUser(enMode::AddNewMode, "", "", "", "", user_name, "", 0);
	}

	bool Delete() {
		std::vector<clsUser> vCUsers = _LoadUsersDataFromFile();

		for (clsUser& user : vCUsers)
		{
			if (user.GetUserName() == _UserName)
			{
				user._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vCUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static std::vector<clsUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		// first check if the user have all access
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogin()
	{
		std::string dateTime = _PrepareLogInRecord();

		std::fstream file;
		file.open("LoginRegister.txt", std::ios::out | std::ios::app);

		if (file.is_open())
		{
			file << dateTime << std::endl;
			file.close();
		}
	}

	static std::vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		std::vector <stLoginRegisterRecord> vLoginRegisterRecord;

		std::ifstream file("LoginRegister.txt");

		if (file.is_open())
		{
			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (std::getline(file, Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			file.close();
		}
		return vLoginRegisterRecord;
	}
};