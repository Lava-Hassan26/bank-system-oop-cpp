#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsString.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsTransferRegisterScreen : protected clsScreen
{
private:
    static void PrintRegistersInfoHeader()
    {
        cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________________________________\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(22) << "DateTime";
        cout << "| " << left << setw(15) << "Source Account";
        cout << "| " << left << setw(20) << "Destination Account";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(15) << "Source Balance";
        cout << "| " << left << setw(20) << "Destination Balance";
        cout << "| " << left << setw(10) << "Username";
        cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________________________________\n";
    }

public:
	static void TransferRegisterScreen()
	{
        vector <clsBankClient::stTransferRegister> vTransferRegisterRecord = clsBankClient::GetTransferRegisterRecord();

        string title = "\tTransfer Register List Screen";
        string subTitle = "\t    (" + to_string(vTransferRegisterRecord.size()) + ") Register(s)";

        _DrawScreenHeader(title, subTitle);

        PrintRegistersInfoHeader();

        if (vTransferRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Register Available In the System!\n";

        else
        {
            for (clsBankClient::stTransferRegister& record : vTransferRegisterRecord)
            {
                cout << setw(8) << left << "" << "| " << setw(22) << left << record.dateTime;
                cout << "| " << setw(15) << left << record.sourceAccountNo;
                cout << "| " << setw(20) << left << record.destinationAccountNo;
                cout << "| " << setw(10) << left << record.amount;
                cout << "| " << setw(15) << left << record.sourceBalance;
                cout << "| " << setw(20) << left << record.destinationBalance;
                cout << "| " << setw(10) << left << record.username << endl;
            }
        }
        cout << setw(8) << left << "" << "__________________________________________________________________________________________________________________________________\n\n";
	}
};