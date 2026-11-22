#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"

using namespace std;

class clsMainScreen :protected clsScreen
{
	enum enMainMenu { ShowClientsList = 1, AddClient, ShowDeleteClientScreen, UpdateClientInfo, FindClient, Transactions, ManageUsers, Logout };

    static void _Login()
    {
        cout << "\nLogin Screen Will be Here Soon...\n";
    }

    static void _ManageUsersMenuScreen()
    {
        cout << "\nManage Users Menu Screen Will be Here Soon...\n";
    }

    static void _TransactionsMenuScreen()
    {
        cout << "\nTransactions Menu Screen Will be Here Soon...\n";
    }

    static void _FindClientScreen()
    {
        cout << "\nFind Client Screen Will be Here Soon...\n";
    }

    static void _UpdateClientScreen()
    {
        cout << "\nUpdate Client Screen Will be Here Soon...\n";
    }

    static void _DeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _AddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowClientsListScreen()
    {
        clsClientsListScreen::ShowClientsList();
    }

    static void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "Press any key to go back to main menu . . . ";
        system("pause>0");
        MainMenuScreen();
    }

    static void _ExecuteMainMenu(enMainMenu userChoice)
    {
        switch (userChoice)
        {
        case enMainMenu::ShowClientsList:
            system("cls");
            _ShowClientsListScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::AddClient:
            system("cls");
            _AddNewClientsScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::ShowDeleteClientScreen:
            system("cls");
            _DeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenu::UpdateClientInfo:
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
            break;

        case enMainMenu::ManageUsers:
            system("cls");
            _ManageUsersMenuScreen();
            break;

        case enMainMenu::Logout:
            system("cls");
           // _Login();
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
        _DrawScreenHeader("\t\tMain Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tMain Menu Screen\n";
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