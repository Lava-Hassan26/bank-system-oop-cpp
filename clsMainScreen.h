#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsUser.h"
#include "Global.h"

using namespace std;

class clsMainScreen :protected clsScreen
{
private:
	enum enMainMenu { ClientsList = 1, AddClient, DeleteClient, UpdateClient, FindClient, Transactions, ManageUsers, Logout };

    static void _Logout()
    {
        currentUser = clsUser::Find("", "");
    }

    static void _ManageUsersMenuScreen()
    {
        clsManageUsersScreen::ManageUsersMenuScreen();
    }

    static void _TransactionsMenuScreen()
    {
        clsTransactionsScreen::TransactionsMenuScreen();
    }

    static void _FindClientScreen()
    {
        clsFindClientScreen::FindClientScreen();
    }

    static void _UpdateClientScreen()
    {
        clsUpdateClientScreen::UpdateClientScreen();
    }

    static void _DeleteClientScreen()
    {
        clsDeleteClientScreen::DeleteClientScreen();
    }

    static void _AddNewClientsScreen()
    {
        clsAddNewClientScreen::AddNewClientScreen();
    }

    static void _ShowClientsListScreen()
    {
        clsClientsListScreen::ShowClientsList();
    }

    static void _GoBackToMainMenu()
    {
        system("cls");
        cout << setw(37) << left << "" << "Press any key to go back to main menu . . . ";
        system("pause>0");
        MainMenuScreen();
    }

    static void _ExecuteMainMenu(enMainMenu userChoice)
    {
        switch (userChoice)
        {
        case enMainMenu::ClientsList:
            system("cls");
            _ShowClientsListScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::AddClient:
            system("cls");
            _AddNewClientsScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::DeleteClient:
            system("cls");
            _DeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::UpdateClient:
            system("cls");
            _UpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::FindClient:
            system("cls");
            _FindClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::Transactions:
            system("cls");
            _TransactionsMenuScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::ManageUsers:
            system("cls");
            _ManageUsersMenuScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::Logout:
            system("cls");
           _Logout();
            break;
        }
    }

    static enMainMenu _ReadMainMenuUserChoice()
    {
        short userChoice = 0;

        cout << setw(37) << left << "" << "Enter your choice [1-8]: ";
        userChoice = clsInputValidation::ReadNumberBetween(1, 8);

        return (enMainMenu)userChoice;
    }

    public:
    static void MainMenuScreen()
    {
        system("cls");
        _DrawScreenHeader("\t      Main Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t   Main Menu Screen\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Clients List\n";
        cout << setw(37) << left << "" << "\t[2] Add New Clients\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info\n";
        cout << setw(37) << left << "" << "\t[5] Find Client\n";
        cout << setw(37) << left << "" << "\t[6] Transactions\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users\n";
        cout << setw(37) << left << "" << "\t[8] Logout\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _ExecuteMainMenu(_ReadMainMenuUserChoice());
    }
};