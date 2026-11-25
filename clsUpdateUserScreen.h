#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidation.h"

class clsUpdateUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& user)
    {
        user.SetFirstName(clsInputValidation::ReadString("Enter first name: "));
        user.SetLastName(clsInputValidation::ReadString("Enter last name: "));
        user.SetPhone(clsInputValidation::ReadString("Enter phone: "));
        user.SetEmail(clsInputValidation::ReadString("Enter email: "));
        user.SetPassword(clsInputValidation::ReadString("Enter password: "));
        user.SetPermissions(_ReadPermissions());
    }

    static int _ReadPermissions()
    {
        int permissions = 0;
        char answer = 'n';
        cout << "\nDo you want to give full access? [Y/N]? ";
        cin >> answer;

        if (tolower(answer) == 'y')
            return -1;
        else
        {
            cout << "\nDo you want to give access to:\n";
            cout << "\nShow Clients List? [Y/N]? ";
            cin >> answer;
            if (tolower(answer) == 'y')
                permissions += clsUser::enUserPermissions::pShowClientsList;

            cout << "\nAdd New Clients? [Y/N]? ";
            cin >> answer;
            if (tolower(answer) == 'y')
                permissions += clsUser::enUserPermissions::pAddClient;

            cout << "\nDelete Client? [Y/N]? ";
            cin >> answer;
            if (tolower(answer) == 'y')
                permissions += clsUser::enUserPermissions::pDeleteClient;

            cout << "\nUpdate Client? [Y/N]? ";
            cin >> answer;
            if (tolower(answer) == 'y')
                permissions += clsUser::enUserPermissions::pUpdateClientInfo;

            cout << "\nFind Client? [Y/N]? ";
            cin >> answer;
            if (tolower(answer) == 'y')
                permissions += clsUser::enUserPermissions::pFindClient;

            cout << "\nTransactions? [Y/N]? ";
            cin >> answer;
            if (tolower(answer) == 'y')
                permissions += clsUser::enUserPermissions::pTransactions;

            cout << "\nManage Users? [Y/N]? ";
            cin >> answer;
            if (tolower(answer) == 'y')
                permissions += clsUser::enUserPermissions::pManageUsers;
        }
        return permissions;

    }

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
    static void UpdateUserScreen()
    {
        _DrawScreenHeader("\t  Update User Screen");
        string username = clsInputValidation::ReadString("\nEnter username: ");

        while (!clsUser::IsUserExists(username))
        {
            cout << "\nInvalid! Username not found.\n";
            username = clsInputValidation::ReadString("\nEnter username: ");
        }

        clsUser user = clsUser::Find(username);
        _PrintUserCard(user);

        char answer = 'y';
        cout << "\nAre you sure you want to update this user? [Y/N]? ";
        cin >> answer;

        if (toupper(answer) == 'Y')
        {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";
            _ReadUserInfo(user);

            clsUser::enSaveResultsMode saveResult;
            saveResult = user.Save();

            switch (saveResult)
            {
            case  clsUser::enSaveResultsMode::svSucceeded:
                cout << "\nUser updated successfully.\n";
                _PrintUserCard(user);
                break;

            case clsUser::enSaveResultsMode::svFailedEmptyObject:
                cout << "\nError! User not saved because it's empty.\n";
                break;
            }
        }
        else
            cout << "\nUpdate cancelled.\n";
    }
};