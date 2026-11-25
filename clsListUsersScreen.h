#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsString.h"
#include "clsUser.h"
#include "clsInputValidation.h"

class clsListUsersScreen : protected clsScreen
{
private:
    static void PrintUsersInfoHeader()
    {
        cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n";
    }

public:
    static void ShowUsersListScreen()
    {
        vector<clsUser> vUsers = clsUser::GetUsersList();

        string title = "\t  User List Screen";
        string subTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";
        _DrawScreenHeader(title, subTitle);

        PrintUsersInfoHeader();
        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else
        {
            for (clsUser& user : vUsers)
            {
                cout << setw(8) << left << "" << "| " << setw(12) << left << user.GetUserName();
                cout << "| " << setw(20) << left << user.GetFullName();
                cout << "| " << setw(12) << left << user.GetPhone();
                cout << "| " << setw(25) << left << user.GetEmail();
                cout << "| " << setw(10) << left << user.GetPassword();
                cout << "| " << setw(12) << left << user.GetPermissions() << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n\n";
    }
};