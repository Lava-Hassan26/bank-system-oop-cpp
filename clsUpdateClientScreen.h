#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& client)
    {
        client.SetFirstName(clsInputValidation::ReadString("\nEnter first name: "));
        client.SetLastName(clsInputValidation::ReadString("\nEnter last name: "));
        client.SetEmail(clsInputValidation::ReadString("\nEnter email: "));
        client.SetPhone(clsInputValidation::ReadString("\nEnter phone number: "));
        client.SetPinCode(clsInputValidation::ReadString("\nEnter pin code: "));
        cout << "\nEnter balance: ";
        client.SetBalance(clsInputValidation::ReadDoubleNumber());
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
    static void UpdateClientScreen()
    {
        _DrawScreenHeader("\tUpdate Client Screen");
        string accountNumber = clsInputValidation::ReadString("\nEnter account number: ");

        while (!clsBankClient::IsClientExists(accountNumber))
        {
            cout << "\nInvalid! Account number not found!\n";
            accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClientCard(client);

        cout << "\n\nUpdate Client Info:";
        cout << "\n____________________\n";
        _ReadClientInfo(client);
        cout << "\n____________________\n";

        clsBankClient::enSaveResultsMode saveResultsMode = client.Save();

        if (saveResultsMode == clsBankClient::enSaveResultsMode::svSucceeded)
        {
            cout << "\nClient info updated successfully\n";
            _PrintClientCard(client);
        }

        if (saveResultsMode == clsBankClient::enSaveResultsMode::svFailedEmptyObject)
            cout << "\nUpdating client info failed\n";
    }
};