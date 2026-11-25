#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidation.h"

class clsDeleteUserScreen : protected clsScreen
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
    static void DeleteUserScreen()
    {
        _DrawScreenHeader("\t  Delete User Screen");

        string username = clsInputValidation::ReadString("\nEnter username: ");

        while (!clsUser::IsUserExists(username))
        {
            cout << "\nInvalid! Username not found.\n";
            username = clsInputValidation::ReadString("\nEnter username: ");
        }

        clsUser user = clsUser::Find(username);
        _PrintUserCard(user);

        char answer = 'y';

        cout << "\nAre you sure you want to delete this user? [Y/N]? ";
        cin >> answer;

        if (tolower(answer) == 'y')
        {
            if (user.Delete())
            {
                cout << "\nUser deleted successfully.\n";
                _PrintUserCard(user);
            }
            else
                cout << "\nError! User cannot be deleted.\n";
        }
        else
            cout << "\nDeletion cancelled.\n";      
    }
};