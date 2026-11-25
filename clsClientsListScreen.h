#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsClientsListScreen : protected clsScreen
{
private:
    static void _PrintClientsListHeader()
    {
        cout << "\n" << setw(8) << left << "" << "_______________________________________________________________________________________________________________\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(16) << "Account Number";
        cout << "| " << left << setw(25) << "Client Name";
        cout << "| " << left << setw(15) << "Phone Number";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(16) << "Balance";
        cout << "\n" << setw(8) << left << "" << "_______________________________________________________________________________________________________________\n\n";
    }

public:
    static void ShowClientsList()
    {
        if (!clsScreen::CheckAccessRights(clsUser::pShowClientsList))
            return;
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string title = "\tClients List Screen";
        string subTitle = "\tList Of (" + to_string(vClients.size()) + ") Clients";

        _DrawScreenHeader(title, subTitle);
        _PrintClientsListHeader();

        if (vClients.empty())
        {
            cout << setw(8) << left << "" << "No Client Available in the System.\n\n";
        }
        else
        {
            for (clsBankClient& client : vClients)
            {
                cout << setw(8) << left << "" << "| " << left << setw(16) << client.GetAccountNumber();
                cout << "| " << left << setw(25) << client.GetFullName();
                cout << "| " << left << setw(15) << client.GetPhone();
                cout << "| " << left << setw(25) << client.GetEmail();
                cout << "| " << left << setw(10) << client.GetPinCode();
                cout << "| " << left << setw(16) << client.GetBalance() << endl;
            }
        }

        cout << setw(8) << left << "" << "_______________________________________________________________________________________________________________\n\n";
    }
};