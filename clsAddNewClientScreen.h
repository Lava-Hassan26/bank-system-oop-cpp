#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsInputValidation.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsAddNewClientScreen :protected clsScreen
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
    static void ShowAddNewClientScreen()
    {
        _DrawScreenHeader("\tAdd New Client Screen");
        string accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
        while (clsBankClient::IsClientExists(accountNumber))
        {
            cout << "\nInvalid! Account number already exists.\n";
            accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
        }

        clsBankClient newClient = clsBankClient::GetAddNewClientObject(accountNumber);
        cout << "\n\nAdd New Client:";
        cout << "\n____________________\n";
        _ReadClientInfo(newClient);
        cout << "\n____________________\n";

        clsBankClient::enSaveResultsMode saveResultsMode = newClient.Save();

        switch (saveResultsMode)
        {
        case  clsBankClient::enSaveResultsMode::svSucceeded:
        {
            cout << "\nAccount added successfully.\n";
            _PrintClientCard(newClient);
            break;
        }
        case clsBankClient::enSaveResultsMode::svFailedEmptyObject:
        {
            cout << "\nError! Account cannot be saved because it is empty.\n";
            break;
        }
        case clsBankClient::enSaveResultsMode::svFailedAccountExists:
        {
            cout << "\nError! Account cannot be saved because the account number is already used!\n";
            break;
        }
        }
    }
};