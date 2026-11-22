#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

class clsFindClientScreen : protected clsScreen
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
    static void FindClientScreen()
    {
        _DrawScreenHeader("\tFind Client Screen");
        string accountNumber = clsInputValidation::ReadString("\nEnter account number: ");

        while (!clsBankClient::IsClientExists(accountNumber))
        {
            cout << "\nInvalid! Account number not found!\n";
            accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
        }

        clsBankClient client = clsBankClient::Find(accountNumber);

        if (!client.IsEmpty())
        {
            cout << "\nClient found:\n";
            _PrintClientCard(client);
        }
        else
            cout << "\nClient not found:\n";
    }
};