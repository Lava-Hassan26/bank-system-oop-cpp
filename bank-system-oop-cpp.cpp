#include <iostream>
#include "clsMainScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"
using namespace std;

void TotalBalancesList()
{
    vector<clsBankClient> vClients = clsBankClient::GetClientsList();
    cout << "\n\n\t\tList Of (" << vClients.size() << ") Balances Client\n";
    cout << "\n_____________________________________________________________\n\n";
    cout << "| " << left << setw(16) << "Account Number";
    cout << "| " << left << setw(25) << "Client Name";
    cout << "| " << left << setw(15) << "Balance";
    cout << "\n_____________________________________________________________\n";
    double totalBalances = clsBankClient::GetTotalBalances();

    for (clsBankClient& client : vClients)
    {
        cout << "| " << left << setw(16) << client.GetAccountNumber();
        cout << "| " << left << setw(25) << client.GetFullName();
        cout << "| " << left << setw(15) << client.GetBalance() << endl;
    }
    cout << "_____________________________________________________________";
    cout << "\n\n\t\tTotal Balances= " << totalBalances << "\n\n";
}

int main()
{ 
    clsMainScreen::MainMenuScreen();
  
    return 0;
}