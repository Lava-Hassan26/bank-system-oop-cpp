#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

class clsTransferScreen : protected clsScreen
{
private:
    static double _ReadTransferAmount(clsBankClient& client)
    {
        double transferAmount = 0;

        cout << "\nEnter Transfer Amount: ";
        transferAmount = clsInputValidation::ReadDoubleNumber();

        while (transferAmount <= 0 || transferAmount > client.GetBalance())
        {
            if (transferAmount <= 0)
                cout << "\nInvalid Amount! Enter an amount greater than 0.\n";
            else
                cout << "\nThe Amount Exceeds the Balance!\n";

            cout << "\nEnter Transfer Amount: ";
            transferAmount = clsInputValidation::ReadDoubleNumber();
        }

        return transferAmount;
    }

    static string _ReadAccountNumber(string inputMessage)
    {
        string accountNumber = clsInputValidation::ReadString(inputMessage);

        while (!clsBankClient::IsClientExists(accountNumber))
        {
            cout << "\nClient with account number " << accountNumber << " not found!\n\n";
            accountNumber = clsInputValidation::ReadString(inputMessage);
        }

        return accountNumber;
    }

    static void _PrintClientCard(clsBankClient& client)
    {
        cout << "\nThe Following are the Client Details";
        cout << "\n***************************************";
        cout << "\nFull Name      : " << client.GetFullName();
        cout << "\nAccount Number : " << client.GetAccountNumber();
        cout << "\nAccount Balance: " << client.GetBalance();
        cout << "\n***************************************\n\n";
    }

public:
    static void TransferScreen()
    {
        _DrawScreenHeader("\t   Transfer Screen");

        string FromAccountNo = _ReadAccountNumber("Enter account number to transfer from: ");

        clsBankClient sourceClient = clsBankClient::Find(FromAccountNo);
        _PrintClientCard(sourceClient);


        string ToAccountNo = _ReadAccountNumber("Enter account number to transfer to: ");
        while (ToAccountNo == FromAccountNo)
        {
            cout << "\nCannot transfer to the same account. Enter a different account number.\n\n";
            ToAccountNo = _ReadAccountNumber("Enter account number to transfer to: ");
        }

        clsBankClient destinationClient = clsBankClient::Find(ToAccountNo);
        _PrintClientCard(destinationClient);

        double transferAmount = _ReadTransferAmount(sourceClient);
        
        char userChoice = 'y';
        cout << "Are you sure you want to transfer this amount? [y/n]? ";
        cin >> userChoice;

        if (tolower(userChoice) == 'y')
        {
            if (sourceClient.Transfer(transferAmount, destinationClient))
                cout << "\nTransfer Done successfully!\n\n";
            else
                cout << "\nTransfer Failed!\n\n";

            _PrintClientCard(sourceClient);
            _PrintClientCard(destinationClient);
        }
        else
            cout << "\nTransfer Cancelled!\n\n";
    }
};