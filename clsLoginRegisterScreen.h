#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void PrintRegistersInfoHeader()
    {
        cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(30) << "DateTime";
        cout << "| " << left << setw(20) << "User Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n";
    }

public:
    static void ShowLoginRegistersListScreen()
    {
        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterRecord();

        string title = "\t Login Register List Screen";
        string subTitle = "\t    (" + to_string(vLoginRegisterRecord.size()) + ") Register(s).";
        _DrawScreenHeader(title, subTitle);

        PrintRegistersInfoHeader();
        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Register Available In the System!";
        else
        {
            for (clsUser::stLoginRegisterRecord& user : vLoginRegisterRecord)
            {
                cout << setw(8) << left << "" << "| " << setw(30) << left << user.dateTime;
                cout << "| " << setw(20) << left << user.username;
                cout << "| " << setw(10) << left << user.password;
                cout << "| " << setw(12) << left << user.permissions<< endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n\n";

    }
};