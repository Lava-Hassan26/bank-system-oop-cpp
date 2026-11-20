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
        cout << "\nINVALID! Account number NOT found!\n";
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

int main()
{ 
    AddNewClient();
  
    return 0;
}