#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsScreen.h"
#include "clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:
	static void _Login()
	{
        bool isLoginFaild = false;
        string username = "", password = "";
        do
        {
            if (isLoginFaild)
            {
                system("cls");
                _DrawScreenHeader("\t     Login Screen");
                cout << "Invalid Username/Password!\n";
            }

            cout << "\nEnter username: ";
            cin >> username;

            cout << "\nEnter Password: ";
            cin >> password;

            currentUser = clsUser::Find(username, password);
            isLoginFaild = currentUser.IsEmpty();

        } while (isLoginFaild);
        clsMainScreen::MainMenuScreen();
	}

public:
	static void LoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     Login Screen");
		_Login();
	}
};