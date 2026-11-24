#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsInputValidation.h"

class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenu { Deposit = 1, Withdraw, TotalBalances, MainMenu };

    static enTransactionsMenu _ReadTransactionsMenuUserChoice()
    {
        cout << setw(37) << left << "" << "Enter your choice [1-4]: ";
        short userChoice = clsInputValidation::ReadNumberBetween(1, 4);
        return (enTransactionsMenu)userChoice;
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << setw(37) << left << "" << "Press any key to go back to transactions menu . . . ";
        system("pause>0");
        system("cls");
        TransactionsMenuScreen();
    }

    static void _TotalBalancesListScreen()
    {

    }

    static void _DepositScreen()
    {
        clsDepositScreen::DepositScreen();
    }

    static void _WithdrawScreen()
    {
        clsWithdrawScreen::WithdrawScreen();
    }

    static void _ExecuteTransactionsMenu(enTransactionsMenu userChoice)
    {
        switch (userChoice)
        {
        case enTransactionsMenu::Deposit:
            system("cls");
            _DepositScreen();
            _GoBackToTransactionsMenu();
            break;

        case enTransactionsMenu::Withdraw:
            system("cls");
            _WithdrawScreen();
            _GoBackToTransactionsMenu();
            break;

        case enTransactionsMenu::TotalBalances:
            system("cls");
            _TotalBalancesListScreen();
            _GoBackToTransactionsMenu();
            break;

        case enTransactionsMenu::MainMenu:
            //do nothing here the main screen will handle it
            break;

        default:
            system("cls");
            TransactionsMenuScreen();
        }
    }

public:
    static void TransactionsMenuScreen()
    {
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\tTransactions Menu Screen\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances\n";
        cout << setw(37) << left << "" << "\t[4] Main Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _ExecuteTransactionsMenu(_ReadTransactionsMenuUserChoice());
    }
};