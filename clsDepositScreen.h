#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

class clsDepositScreen : protected clsScreen
{
private:
    static string _ReadAccountNumber()
    {
        string accountNumber = "";
        accountNumber =clsInputValidation::ReadString("Enter the account number: ");
        return accountNumber;
    }

    static void _PrintClientCard(clsBankClient& client)
    {
        cout << "\nThe Following are the Client Details";
        cout << "\n***************************************";
        cout << "\nFirst Name     : " << client.GetFirstName();
        cout << "\nLast Name      : " << client.GetLastName();
        cout << "\nFull Name      : " << client.GetFullName();
        cout << "\nEmail          : " << client.GetEmail();
        cout << "\nPhone Number   : " << client.GetPhone();
        cout << "\nAccount Number : " << client.GetAccountNumber();
        cout << "\nPin Code       : " << client.GetPinCode();
        cout << "\nAccount Balance: " << client.GetBalance();
        cout << "\n***************************************\n\n";
    }

public:
    static void DepositScreen()
    {
        _DrawScreenHeader("\t   Deposit Screen");
        
        string accountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExists(accountNumber))
        {
            cout << "\nClient with account number " << accountNumber << " not found!\n\n";
            accountNumber = _ReadAccountNumber();
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClientCard(client);

        cout << "\nEnter Deposit Amount: ";
        double depositAmount = clsInputValidation::ReadDoubleNumber();
        
        char userChoice = 'y';
        cout << "Are you sure you want to deposit this amount? [y/n]? ";
        cin >> userChoice;

        if (tolower(userChoice) == 'y')
        {
            client.Deposite(depositAmount);
            cout << "\nDeposit Done successfully!\n\n";
        }
        else
            cout << "\nDeposit Cancelled!\n\n";
    }
};