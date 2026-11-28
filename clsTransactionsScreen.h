#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsInputValidation.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferRegisterScreen.h"


class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenu { Deposit = 1, Withdraw, TotalBalances, Transfer, TransferRegister, MainMenu };

    static enTransactionsMenu _ReadTransactionsMenuUserChoice()
    {
        cout << setw(37) << left << "" << "Enter your choice [1-6]: ";
        short userChoice = clsInputValidation::ReadNumberBetween(1, 6);
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
        clsTotalBalancesScreen::TotalBalancesListScreen();
    }

    static void _DepositScreen()
    {
        clsDepositScreen::DepositScreen();
    }

    static void _WithdrawScreen()
    {
        clsWithdrawScreen::WithdrawScreen();
    }

    static void _TransferScreen()
    {
        clsTransferScreen::TransferScreen();
    }

    static void _TransferRegisterScreen()
    {
        clsTransferRegisterScreen::TransferRegisterScreen();
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

        case enTransactionsMenu::Transfer:
            system("cls");
            _TransferScreen();
            _GoBackToTransactionsMenu();
            break;

        case enTransactionsMenu::TransferRegister:
            system("cls");
            _TransferRegisterScreen(); 
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
        if (!CheckAccessRights(clsUser::pTransactions))
            return;
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t      Transactions Menu Screen\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances\n";
        cout << setw(37) << left << "" << "\t[4] Transfer\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Register\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _ExecuteTransactionsMenu(_ReadTransactionsMenuUserChoice());
    }
};