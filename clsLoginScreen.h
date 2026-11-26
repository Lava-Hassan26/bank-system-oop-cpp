#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsScreen.h"
#include "clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
        bool isLoginFaild = false;
        short counter = 3;
        string username = "", password = "";
        do
        {
            if (isLoginFaild)
            {
                system("cls");
                _DrawScreenHeader("\t     Login Screen");
                cout << "Invalid Username/Password!\n";
                counter--;
                cout << "You have " << counter << " trails\n";
                if (counter == 0)
                {
                    cout << "\n\nYour account locked after 3 login faild trail(s)!\n\n\n";
                    return false;
                }
            }

            cout << "\nEnter username: ";
            cin >> username;

            cout << "\nEnter Password: ";
            cin >> password;

            currentUser = clsUser::Find(username, password);
            isLoginFaild = currentUser.IsEmpty();

        } while (isLoginFaild);
        currentUser.LoginRegister();
        clsMainScreen::MainMenuScreen();
        return true;
	}

public:
	static bool LoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     Login Screen");
        return _Login();
	}
};