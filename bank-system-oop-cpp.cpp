#include <iostream>
#include "clsMainScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"
using namespace std;

void ReadClientInfo(clsBankClient& client)
{
    client.SetFirstName(clsInputValidation::ReadString("\nEnter first name: "));
    client.SetLastName(clsInputValidation::ReadString("\nEnter last name: "));
    client.SetEmail(clsInputValidation::ReadString("\nEnter email: "));
    client.SetPhone(clsInputValidation::ReadString("\nEnter phone number: "));
    client.SetPinCode(clsInputValidation::ReadString("\nEnter pin code: "));
    cout << "\nEnter balance: ";
    client.SetBalance(clsInputValidation::ReadDoubleNumber());
}

void Update()
{
    string accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
    while (!clsBankClient::IsClientExists(accountNumber))
    {
        cout << "\nInvalid! Account number not found!\n";
        accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
    }

    clsBankClient client = clsBankClient::Find(accountNumber);
    client.Print();

    cout << "\n\nUpdate Client Info:";
    cout << "\n____________________\n";
    ReadClientInfo(client);
    cout << "\n____________________\n";

    clsBankClient::enSaveResultsMode saveResultsMode = client.Save();

    if (saveResultsMode == clsBankClient::enSaveResultsMode::svSucceeded)
        cout << "\nClient info updated successfully\n";

    if (saveResultsMode == clsBankClient::enSaveResultsMode::svFailedEmptyObject)
        cout << "\nUpdating client info failed\n";
}

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