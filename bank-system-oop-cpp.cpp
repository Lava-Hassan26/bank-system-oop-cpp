#include <iostream>
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

void AddNewClient()
{
    string accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
    while (clsBankClient::IsClientExists(accountNumber))
    {
        cout << "\nInvalid! Account number already exists.\n";
        accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
    }

    clsBankClient newClient = clsBankClient::GetAddNewClientObject(accountNumber);
    cout << "\n\nAdd New Client:";
    cout << "\n____________________\n";
    ReadClientInfo(newClient);
    cout << "\n____________________\n";

    clsBankClient::enSaveResultsMode saveResultsMode = newClient.Save();

    switch (saveResultsMode)
    {
    case  clsBankClient::enSaveResultsMode::svSucceeded:
    {
        cout << "\nAccount added successfully.\n";
        newClient.Print();
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

void DeleteClient()
{
    string accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
    while (!clsBankClient::IsClientExists(accountNumber))
    {
        cout << "\nInvalid! Account number not found!\n";
        accountNumber = clsInputValidation::ReadString("\nEnter account number: ");
    }

    clsBankClient client = clsBankClient::Find(accountNumber);
    client.Print();

    char answer = 'y';
    cout << "\nAre you sure you want to delete this client? [Y/N]? ";
    cin >> answer;

    if (tolower(answer) == 'y')
    {
        if (client.Delete())
        {
            cout << "\nClient deleted successfully.\n";
            client.Print();
        }
        else
            cout << "\nError! Account cannot be deleted.\n";
    }
    else
        cout << "\nDeletion cancelled.\n";
}

void PrintClientsListHeader()
{
    cout << "\n____________________________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(16) << "Account Number";
    cout << "| " << left << setw(25) << "Client Name";
    cout << "| " << left << setw(15) << "Phone Number";  
    cout << "| " << left << setw(25) << "Email";  
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(16) << "Balance";
    cout << "\n____________________________________________________________________________________________________________________\n\n";
}

void ShowClientsList()
{
    vector<clsBankClient> vClients = clsBankClient::GetClientsList();
    cout << "\n\n\t\t\t\t\tList Of (" << vClients.size() << ") Clients\n";
    PrintClientsListHeader();

    if(vClients.empty())
    {
        cout << "\n\n\t\t\t\tNo Client Available in the System.\n\n";
    }
    else
    {
        for (clsBankClient& client : vClients)
        {
            cout << "| " << left << setw(16) << client.GetAccountNumber();
            cout << "| " << left << setw(25) << client.GetFullName();
            cout << "| " << left << setw(15) << client.GetPhone();
            cout << "| " << left << setw(25) << client.GetEmail();
            cout << "| " << left << setw(10) << client.GetPinCode();
            cout << "| " << left << setw(16) << client.GetBalance() << endl;
        }
    }
    cout << "____________________________________________________________________________________________________________________\n\n";
}

int main()
{ 
    ShowClientsList();
  
    return 0;
}