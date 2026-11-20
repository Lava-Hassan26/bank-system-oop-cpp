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

int main()
{ 
    Update();

    return 0;
}