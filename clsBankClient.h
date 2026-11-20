#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };

	enMode _mode;
	string _accountNumber = "";
	string _pinCode = "";
	double _balance = 0.0;

	static clsBankClient _ConvertDataLineToClientObject(string dataLine, string delim = "#//#")
	{
		if (dataLine.empty())
			return _GetEmptyClientObject();

		vector<string> vClient = clsString::SplitString(dataLine, delim);

		if (vClient.size() < 7)
			return _GetEmptyClientObject();

		return clsBankClient(
			enMode::UpdateMode,
			vClient[0],
			vClient[1],
			vClient[2],
			vClient[3],
			vClient[4],
			vClient[5],
			stod(vClient[6])
		);
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0.0);
	}

public:

	clsBankClient(enMode mode, string firstName, string lastName,
		string email, string phone, string accountNumber, string pinCode,
		double balance) :clsPerson(firstName, lastName, email, phone)
	{
		_mode = mode;
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_balance = balance;
	}

	string GetAccountNumber()
	{
		return _accountNumber;
	}

	void SetPinCode(string pinCode)
	{
		_pinCode = pinCode;
	}

	string GetPinCode()
	{
		return _pinCode;
	}

	void SetBalance(double balance)
	{
		_balance = balance;
	}

	double GetBalance()
	{
		return _balance;
	}

	bool IsEmpty()
	{
		return _mode == enMode::EmptyMode;
	}

	static clsBankClient Find(string accountNumber)
	{
		fstream clientsFile;
		clientsFile.open("Clients.txt", ios::in);//read Mode
		if (clientsFile.is_open())
		{
			string Line;
			while (getline(clientsFile, Line))
			{
				clsBankClient Client = _ConvertDataLineToClientObject(Line, "#//#");
				if (Client._accountNumber == accountNumber)
				{
					clientsFile.close();
					return Client;
				}
			}
			clientsFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string accountNumber, string pinCode)
	{
		fstream clientsFile;
		clientsFile.open("Clients.txt", ios::in);//read Mode
		if (clientsFile.is_open())
		{
			string Line;
			while (getline(clientsFile, Line))
			{
				clsBankClient Client = _ConvertDataLineToClientObject(Line, "#//#");
				if (Client._accountNumber == accountNumber && Client._pinCode == pinCode)
				{
					clientsFile.close();
					return Client;
				}
			}
			clientsFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExists(string accountNumber)
	{
		clsBankClient client = Find(accountNumber);

		return !client.IsEmpty();
	}

	void Print()
	{
		cout << "\nThe Followings are the Client Details";
		cout << "\n***************************************";
		cout << "\nAccount Number : " << GetAccountNumber();
		cout << "\nPin Code       : " <<GetPinCode();
		cout << "\nFull Name      : " << GetFullName();
		cout << "\nPhone Number   : " << GetPhone();
		cout << "\nEmail          : " << GetEmail();
		cout << "\nAccount Balance: " << GetBalance();
		cout << "\n***************************************\n\n";
	}
};