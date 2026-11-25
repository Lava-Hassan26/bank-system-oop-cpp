#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsListUsersScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsersMenu { ShowUsersList = 1, AddUser, DeleteUser, UpdateUserInfo, FindUser, MainMenuUser };

    static enManageUsersMenu _ReadManageUsersMenuUserChoice()
    {
        short userChoice = 0;

        cout << setw(37) << left << "" << "Enter your choice [1-6]: ";
        userChoice = clsInputValidation::ReadNumberBetween(1, 6);

        return (enManageUsersMenu)userChoice;
    }

    static void _ShowUsersListScreen()
    {
        clsListUsersScreen::ShowUsersListScreen();
    }

    static void _AddNewUsersScreen()
    {

    }

    static void _DeleteUserScreen()
    {

    }

    static void _UpdateUserScreen()
    {

    }

    static void _FindUserScreen()
    {

    }

    static void _GoBackToManageUsersMenu()
    {
        cout << setw(37) << left << "" << "Press any key to go back to manage users menu . . . ";
        system("pause>0");
        system("cls");
        ManageUsersMenuScreen();
    }

    static void _ExecuteManageUsersMenu(enManageUsersMenu userChoise)
    {
        switch (userChoise)
        {
        case enManageUsersMenu::ShowUsersList:
            system("cls");
            _ShowUsersListScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenu::AddUser:
            system("cls");
            _AddNewUsersScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenu::DeleteUser:
            system("cls");
            _DeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenu::UpdateUserInfo:
            system("cls");
            _UpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenu::FindUser:
            system("cls");
            _FindUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenu::MainMenuUser:
            break;
        }
    }

public:
    static void ManageUsersMenuScreen()
    {
        _DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tManage Users Menu Screen\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Users List\n";
        cout << setw(37) << left << "" << "\t[2] Add New User\n";
        cout << setw(37) << left << "" << "\t[3] Delete User\n";
        cout << setw(37) << left << "" << "\t[4] Update User Info\n";
        cout << setw(37) << left << "" << "\t[5] Find User\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _ExecuteManageUsersMenu(_ReadManageUsersMenuUserChoice());
    }
};