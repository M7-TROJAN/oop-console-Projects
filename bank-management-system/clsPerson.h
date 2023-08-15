#pragma once
#include <iostream>
#include "inputValidate.h"
//#include <string>

class clsPerson
{
private:
	std::string _FirstName;
	std::string _LastName;
	std::string _Email;
	std::string _Phone;
public:
	clsPerson(std::string fName, std::string lName, std::string email, std::string phone) : _FirstName(std::move(fName)),
		_LastName(std::move(lName)), _Email(std::move(email)), _Phone(std::move(phone)) {}

	// Setter and Getter methods for modifying and accessing the first name
	void setFirstName(std::string fName) {
		_FirstName = fName;
	}
	std::string getFirstName() const {
		return _FirstName;
	}
	_declspec(property(get = getFirstName, put = setFirstName)) std::string FirstName;

	// Setter and Getter methods for modifying and accessing the last name
	void setLastName(std::string lName) {
		_LastName = lName;
	}
	std::string getLastName() const {
		return _LastName;
	}
	_declspec(property(get = getLastName, put = setLastName)) std::string LastName;

	// Setter and Getter methods for modifying and accessing the email
	void setEmail(std::string email) {
		_Email = clsInputValidate::trim(email);
	}
	std::string getEmail() const {
		return _Email;
	}
	__declspec(property(get = getEmail, put = setEmail)) std::string Email;

	// Setter and Getter methods for modifying and accessing the phone number
	void setPhone(std::string phone) {
		_Phone = phone;
	}
	std::string getPhone() const {
		return _Phone;
	}
	__declspec(property(get = getPhone, put = setPhone)) std::string Phone;

	// Method to get the full name of the person by concatenating first and last name
	std::string fullName() const {
		return _FirstName + " " + _LastName;
	}

	// Method to send an email message
	void sendMessage(const std::string& Subject, const std::string& Body) {
		std::cout << "The Following Message Sent Successfully To Email: " << _Email << std::endl;
		std::cout << "Subject: " << Subject << std::endl;
		std::cout << "Body: " << Body << std::endl;
	}

	// Method to send an SMS message
	void sendSMS(const std::string& TextMessage) {
		std::cout << "The Following SMS Sent Successfully To Phone: " << _Phone << std::endl;
		std::cout << TextMessage << "\n";
	}
};
