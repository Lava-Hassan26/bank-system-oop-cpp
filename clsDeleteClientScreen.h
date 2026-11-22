#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

class clsDeleteClientScreen : clsScreen
{
private:
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
    static void ShowDeleteClientScreen()
    {
        _DrawScreenHeader("\tDelete Client Screen");

        string accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
        while (!clsBankClient::IsClientExists(accountNumber))
        {
            cout << "\nInvalid! Account number not found!\n";
            accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClientCard(client);

        char answer = 'y';
        cout << "\nAre you sure you want to delete this client? [Y/N]? ";
        cin >> answer;

        if (tolower(answer) == 'y')
        {
            if (client.Delete())
            {
                cout << "\nClient deleted successfully.\n";
                _PrintClientCard(client);
            }
            else
                cout << "\nError! Account cannot be deleted.\n";
        }
        else
            cout << "\nDeletion cancelled.\n";
    }
};