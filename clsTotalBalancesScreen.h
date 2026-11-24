#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

class clsTotalBalancesScreen : protected clsScreen
{
public:
    static void TotalBalancesList()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string title = "\t  Balances List Screen";

        string subTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(title, subTitle);

        cout << setw(30) << left << "" << "\n\t\t\t__________________________________________________________________\n\n";
        cout << setw(30) << left << "" << "| " << left << setw(16) << "Account Number";
        cout << "| " << left << setw(25) << "Client Name";
        cout << "| " << left << setw(15) << "Balance";
        cout << setw(30) << left << "" << "\n\t\t\t__________________________________________________________________\n";

        double totalBalances = clsBankClient::GetTotalBalances();

        for (clsBankClient& client : vClients)
        {
            cout << setw(30) << left << "" << "| " << left << setw(16) << client.GetAccountNumber();
            cout << "| " << left << setw(25) << client.GetFullName();
            cout << "| " << left << setw(15) << client.GetBalance() << endl;
        }

        cout << setw(13) << left << "" << "\t\t__________________________________________________________________\n\n";

        cout << setw(13) << left << "" << "\t\t\t\t\tTotal Balances = " << totalBalances << "\n\n";
    }
};