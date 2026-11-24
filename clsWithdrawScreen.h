#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

class clsWithdrawScreen : protected clsScreen
{
private:
    static string _ReadAccountNumber()
    {
        string accountNumber = "";
        accountNumber = clsInputValidation::ReadString("Enter the account number: ");

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
    static void WithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

        string accountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExists(accountNumber))
        {
            cout << "\nClient with account number " << accountNumber << " not found!\n\n";
            accountNumber = _ReadAccountNumber();
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClientCard(client);

        cout << "\nEnter Withdraw Amount: ";
        double depositAmount = clsInputValidation::ReadDoubleNumber();

        char userChoice = 'y';
        cout << "Are you sure you want to withdraw this amount? [y/n]? ";
        cin >> userChoice;

        if (tolower(userChoice) == 'y')
        {
            client.Withdraw(depositAmount);
            cout << "\nWithdraw Done successfully!\n\n";
        }
        else
            cout << "\nWithdraw Cancelled!\n\n";
    }
};