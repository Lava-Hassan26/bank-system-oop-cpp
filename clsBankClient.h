#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode, UpdateMode, AddNewMode };

	enMode _mode;
	string _accountNumber = "";
	string _pinCode = "";
	double _balance = 0.0;
	bool _isMarkedForDelete = false;

	struct stTransferRegister;

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

	static string _ConvertClientObjectToDataLine(clsBankClient client, string delim = "#//#")
	{
		string line = "";
		line += client.GetFirstName() + delim;
		line += client.GetLastName() + delim;
		line += client.GetEmail() + delim;	
		line += client.GetPhone() + delim;
		line += client.GetAccountNumber() + delim;
		line += client.GetPinCode() + delim;
		line += to_string(client.GetBalance());
		return line;
	}

	static void _AddClientToFile(clsBankClient client, string fileName, string delim = "#//#")
	{
		fstream clientsFile;
		clientsFile.open(fileName, ios::out | ios::app);
		if (clientsFile.is_open())
		{
			string line = _ConvertClientObjectToDataLine(client, delim);
			clientsFile << line << endl;
			clientsFile.close();
		}
	}

	static void _SaveAllClientsToFile(vector<clsBankClient>& vClients, string fileName, string delim = "#//#")
	{
		fstream clientsFile;
		clientsFile.open(fileName, ios::out);

		if (clientsFile.is_open())
		{
			string currentLine = "";
			for (clsBankClient& client : vClients)
			{
				if (client._isMarkedForDelete == false)
				{
					currentLine = _ConvertClientObjectToDataLine(client, delim);
					clientsFile << currentLine << endl;
				}
			}
			clientsFile.close();
		}
	}

	static vector<clsBankClient> _LoadAllClientsFromFile(string fileName, string delim = "#//#")
	{
		vector<clsBankClient> vClients;
		fstream clientsFile;
		clientsFile.open(fileName, ios::in);

		if (clientsFile.is_open())
		{
			string currentLine = "";
			while (getline(clientsFile, currentLine))
			{
				clsBankClient client = _ConvertDataLineToClientObject(currentLine, delim);
				if (!client.IsEmpty())
					vClients.push_back(client);
			}
			clientsFile.close();
		}
		return vClients;
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0.0);
	}

	void _AddNewClient()
	{
		_AddClientToFile(*this, "Clients.txt");
	}

	void  _Update()
	{
		vector<clsBankClient> _vClients = _LoadAllClientsFromFile("Clients.txt");
		
		for (clsBankClient& c : _vClients)
		{
			if (c._accountNumber == this->_accountNumber)
			{
				c = *this;
				break;
			}
		}
		_SaveAllClientsToFile(_vClients, "Clients.txt");
	}

	string _PrepareTransferRecord(double amount, clsBankClient& destinationClient, string delim = "#//#")
	{
		string transferRecord = "";

		transferRecord += clsDate::GetStringSystemDateTime() + delim;
		transferRecord += GetAccountNumber() + delim;
		transferRecord += destinationClient.GetAccountNumber() + delim;
		transferRecord += to_string(amount) + delim;
		transferRecord += to_string(GetBalance()) + delim;
		transferRecord += to_string(destinationClient.GetBalance()) + delim;
		transferRecord += currentUser.GetUserName();

		return transferRecord;
	}

	void _TransferRegister(double amount, clsBankClient& destinationClient)
	{
		string transferRegister = _PrepareTransferRecord(amount, destinationClient);

		fstream transferRegisterFile;
		transferRegisterFile.open("TransferRegister.txt", ios::out | ios::app);

		if (transferRegisterFile.is_open())
		{
			transferRegisterFile << transferRegister << endl;
			transferRegisterFile.close();
		}
	}

	static stTransferRegister _ConvertTransferRegisterLineToRecord(string dataLine, string delim = "#//#")
	{
		stTransferRegister transferRegisterRecord;

		if (dataLine.empty())
			return transferRegisterRecord;

		vector<string> vTransferRecord = clsString::SplitString(dataLine, delim);

		if (vTransferRecord.size() == 0)
			return transferRegisterRecord;

		transferRegisterRecord.dateTime = vTransferRecord[0];
		transferRegisterRecord.sourceAccountNo = vTransferRecord[1];
		transferRegisterRecord.destinationAccountNo = vTransferRecord[2];
		transferRegisterRecord.amount = stod(vTransferRecord[3]);
		transferRegisterRecord.sourceBalance = stod(vTransferRecord[4]);
		transferRegisterRecord.destinationBalance = stod(vTransferRecord[5]);
		transferRegisterRecord.username = vTransferRecord[6];

		return transferRegisterRecord;
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

	struct stTransferRegister
	{
		string dateTime = "";
		string sourceAccountNo = "";
		string destinationAccountNo = "";
		double amount = 0;
		double sourceBalance = 0;
		double destinationBalance = 0;
		string username = "";
	};

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
		clientsFile.open("Clients.txt", ios::in);//Read Mode
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
		clientsFile.open("Clients.txt", ios::in);//Read Mode
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
		cout << "\nThe Following are the Client Details";
		cout << "\n***************************************";
		cout << "\nFirst Name     : " << GetFirstName();
		cout << "\nLast Name      : " << GetLastName();	
		cout << "\nFull Name      : " << GetFullName();
		cout << "\nEmail          : " << GetEmail();
		cout << "\nPhone Number   : " << GetPhone();
		cout << "\nAccount Number : " << GetAccountNumber();
		cout << "\nPin Code       : " <<GetPinCode();
		cout << "\nAccount Balance: " << GetBalance();
		cout << "\n***************************************\n\n";
	}

	enum enSaveResultsMode { svFailedEmptyObject, svSucceeded, svFailedAccountExists};

	enSaveResultsMode Save()
	{
		switch (_mode)
		{
		case enMode::EmptyMode:
			return enSaveResultsMode::svFailedEmptyObject;

		case enMode::UpdateMode:
			_Update();
			return enSaveResultsMode::svSucceeded;

		case enMode::AddNewMode:
			if (!IsClientExists(_accountNumber))
			{
				_AddNewClient();
				_mode = enMode::UpdateMode;
				return enSaveResultsMode::svSucceeded;
			}
			else
				return enSaveResultsMode::svFailedAccountExists;
		}
	}	
	
	static clsBankClient GetAddNewClientObject(string accountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0.0);
	}

	bool Delete()
	{
		vector<clsBankClient> _vClients = _LoadAllClientsFromFile("Clients.txt");

		for (clsBankClient& c : _vClients)
		{
			if (c._accountNumber == this->_accountNumber)
			{
				c._isMarkedForDelete = true;
				_SaveAllClientsToFile(_vClients, "Clients.txt");
				*this = _GetEmptyClientObject();
				return true;
			}
		}
		return false;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadAllClientsFromFile("Clients.txt");
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadAllClientsFromFile("Clients.txt");
		double totalBalances = 0;

		for (clsBankClient& client : vClients)
			totalBalances += client._balance;

		return totalBalances;
	}

	void Deposite(double amount)
	{
		_balance += amount;
		Save();
	}

	bool Withdraw(double amount)
	{
		if (amount > _balance)
			return false;

		else
		{
			_balance -= amount;
			Save();
			return true;
		}
	}

	bool Transfer(double amount, clsBankClient& destinationClient)
	{
		if (amount <= 0 || amount > _balance || destinationClient.IsEmpty() || destinationClient.GetAccountNumber() == _accountNumber)
			return false;

		Withdraw(amount);
		destinationClient.Deposite(amount);
		_TransferRegister(amount, destinationClient);
		return true;
	}

	static vector <stTransferRegister> GetTransferRegisterRecord()
	{
		vector <stTransferRegister> vTransferRegister;
		fstream transferRegisterFile;

		transferRegisterFile.open("TransferRegister.txt", ios::in);

		if (transferRegisterFile.is_open())
		{
			stTransferRegister transferRegisterRecord;
			string dataLine = "";

			while (getline(transferRegisterFile, dataLine))
			{
				if (dataLine != "")
				{
					transferRegisterRecord = _ConvertTransferRegisterLineToRecord(dataLine);
					vTransferRegister.push_back(transferRegisterRecord);
				}
			}
			transferRegisterFile.close();
		}
		return vTransferRegister;
	}
};