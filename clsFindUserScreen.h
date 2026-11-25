#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidation.h"

class clsFindUserScreen : protected clsScreen
{
private:
    static void _PrintUserCard(clsUser& user)
    {
        cout << "\nThe Following are the User Details";
        cout << "\n***************************************";
        cout << "\nFirstName   : " << user.GetFirstName();
        cout << "\nLastName    : " << user.GetLastName();
        cout << "\nFull Name   : " << user.GetFullName();
        cout << "\nEmail       : " << user.GetEmail();
        cout << "\nPhone       : " << user.GetPhone();
        cout << "\nUser Name   : " << user.GetUserName();
        cout << "\nPassword    : " << user.GetPassword();
        cout << "\nPermissions : " << user.GetPermissions();
        cout << "\n***************************************\n\n";
    }

public:
    static void FindUserScreen()
    {
        _DrawScreenHeader("\t  Find User Screen");
        string username = clsInputValidation::ReadString("\nEnter username: ");
        while (!clsUser::IsUserExists(username))
        {
            cout << "\nInvalid! Username not found.\n";
            username = clsInputValidation::ReadString("\nEnter username: ");
        }
        clsUser user = clsUser::Find(username);
        cout << "\nUser Found.\n";
        _PrintUserCard(user);
    }
};