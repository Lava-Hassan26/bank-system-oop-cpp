#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsInputValidation.h"

class clsUser : public clsPerson
{
private:
    enum enMode { EmptyMode, UpdateMode, AddNewMode };

    enMode _mode;
    string _username = "";
    string _password = "";
    int _userPermissions = 0;
    bool _isMarkedForDelete = false;

    struct stLoginRegisterRecord;

    static string _ConvertUserRecordToDataLine(clsUser user, string delim = "#//#")
    {
        string userDataLine = "";
        userDataLine += user.GetFirstName() + delim;
        userDataLine += user.GetLastName() + delim;
        userDataLine += user.GetEmail() + delim;
        userDataLine += user.GetPhone() + delim;
        userDataLine += user._username + delim;
        userDataLine += user._password + delim;
        userDataLine += to_string(user._userPermissions);
        return userDataLine;
    }

    static clsUser _ConvertDataLineToUserRecord(string dataLine, string delim = "#//#")
    {
        if (dataLine.empty())
            return _GetEmptyUserObject();

        vector<string> vUser =clsString::SplitString(dataLine, delim);
        
        if (vUser.size() < 7)
            return _GetEmptyUserObject();

        return clsUser(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], vUser[5], stoi(vUser[6]));
    }

    static void _AddUserToFile(clsUser user, string fileName, string delim = "#//#")
    {
        fstream usersFile;
        usersFile.open(fileName, ios::out | ios::app);
        if (usersFile.is_open())
        {
            string line = _ConvertUserRecordToDataLine(user, delim);
            usersFile << line << endl;
            usersFile.close();
        }
    }

    static void _SaveAllUsersToFile(vector<clsUser>& vUsers, string fileName, string delim = "#//#")
    {
        fstream usersFile;
        usersFile.open(fileName, ios::out);

        if (usersFile.is_open())
        {
            string currentline = "";
            for (clsUser& user : vUsers)
            {
                if (!user._isMarkedForDelete)
                {
                    currentline = _ConvertUserRecordToDataLine(user, delim);
                    usersFile << currentline << endl;
                }
            }
            usersFile.close();
        }
    }

    static vector<clsUser> _LoadAllUsersFromFile(string fileName, string delim = "#//#")
    {
        vector<clsUser> vUsers;

        fstream usersFile;
        usersFile.open(fileName, ios::in);

        if (usersFile.is_open())
        {
            string currentline = "";
            while (getline(usersFile, currentline))
            {
                clsUser user = _ConvertDataLineToUserRecord(currentline, delim);
                if (!user.IsEmpty())
                    vUsers.push_back(user);
            }
            usersFile.close();
        }
        return vUsers;
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    void _AddNewUser()
    {
        _AddUserToFile(*this, "Users.txt");
    }

    void  _Update()
    {
        vector<clsUser> _vUsers = _LoadAllUsersFromFile("Users.txt");

        for (clsUser& user : _vUsers)
        {
            if (user._username == this->_username)
            {
                user = *this;
                break;
            }
        }

        _SaveAllUsersToFile(_vUsers, "Users.txt");
    }

    string _PrepareLoginRecord(string delim = "#//#")
    {
        string loginRecord = "";

        loginRecord += clsDate::GetStringSystemDateTime() + delim;
        loginRecord += GetUserName() + delim;
        loginRecord += GetPassword() + delim;
        loginRecord += to_string(GetPermissions());

        return loginRecord;
    }

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string dataLine, string delim = "#//#")
    {
        stLoginRegisterRecord loginRegisterRecord;

        if (dataLine.empty())
            return loginRegisterRecord;

        vector<string> vLoginRegister = clsString::SplitString(dataLine, delim);

        if (vLoginRegister.size() == 0)
            return loginRegisterRecord;

        loginRegisterRecord.dateTime = vLoginRegister[0];
        loginRegisterRecord.username = vLoginRegister[1];
        loginRegisterRecord.password = vLoginRegister[2];
        loginRegisterRecord.permissions = stoi(vLoginRegister[3]);

        return loginRegisterRecord;
    }

public:
    enum enUserPermissions {
        eAll = -1, pShowClientsList = 1, pAddClient = 2, pDeleteClient = 4,
        pUpdateClientInfo = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64
    };

    clsUser(enMode mode, string firstName, string lastName,
        string email, string phone, string username,
        string password, int userPermissions) :clsPerson(firstName, lastName, email, phone)
    {
        _mode = mode;
        _username = username;
        _password = password;
        _userPermissions = userPermissions;
    }

    struct stLoginRegisterRecord
    {
        string dateTime = "";
        string username = "";
        string password = "";
        int permissions = 0;
    };

    bool IsEmpty()
    {
        return _mode == enMode::EmptyMode;
    }

    void SetUserName(string userName)
    {
        _username = userName;
    }

    string GetUserName()
    {
        return _username;
    }

    void SetPassword(string password)
    {
        _password = password;
    }

    string GetPassword()
    {
        return _password;
    }

    void SetPermissions(int userPermissions)
    {
        _userPermissions = userPermissions;
    }

    int GetPermissions()
    {
        return _userPermissions;
    }

    bool IsMarkedForDelete()
    {
        return _isMarkedForDelete;
    }

    static clsUser Find(string username)
    {
        fstream usersFile;
        usersFile.open("Users.txt", ios::in);//Read Mode

        if (usersFile.is_open())
        {
            string line;
            while (getline(usersFile, line))
            {
                clsUser user = _ConvertDataLineToUserRecord(line, "#//#");
                if (user._username == username)
                {
                    usersFile.close();
                    return user;
                }
            }
            usersFile.close();
        }
        return _GetEmptyUserObject();
    }

    static clsUser Find(string username, string password)
    {
        fstream usersFile;
        usersFile.open("Users.txt", ios::in);//Read Mode

        if (usersFile.is_open())
        {
            string line;
            while (getline(usersFile, line))
            {
                clsUser user = _ConvertDataLineToUserRecord(line, "#//#");
                if (user._username == username && user._password == password)
                {
                    usersFile.close();
                    return user;
                }
            }
            usersFile.close();
        }
        return _GetEmptyUserObject();
    }

    static bool IsUserExists(string username)
    {
        clsUser user = Find(username);

        return !user.IsEmpty();
    }

    enum enSaveResultsMode { svFailedEmptyObject, svSucceeded, svFailedUsernameExists };

    enSaveResultsMode Save()
    {
        switch (_mode)
        {
        case enMode::EmptyMode:
            return enSaveResultsMode::svFailedEmptyObject;

        case enMode::UpdateMode:
            _Update();
            return enSaveResultsMode::svSucceeded;

        case enMode::AddNewMode:
            if (!IsUserExists(_username))
            {
                _AddNewUser();
                _mode = enMode::UpdateMode;
                return enSaveResultsMode::svSucceeded;
            }
            else
                return enSaveResultsMode::svFailedUsernameExists;
        }
    }

    static clsUser GetAddNewUserObject(string username)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", username, "", 0);
    }

    bool Delete()
    {
        vector<clsUser> _vUsers = _LoadAllUsersFromFile("Users.txt");

        for (clsUser& user : _vUsers)
        {
            if (user._username == this->_username)
            {
                user._isMarkedForDelete = true;
                _SaveAllUsersToFile(_vUsers, "Users.txt");
                *this = _GetEmptyUserObject();
                return true;
            }
        }

        return false;
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadAllUsersFromFile("Users.txt");
    }

    bool CheckAccessPermission(enUserPermissions permission)
    {
        if (this->_userPermissions == enUserPermissions::eAll)
            return true;
        if ((permission & this->_userPermissions) == permission)
            return true;
        else
            return false;
    }

    void LoginRegister()
    {
        string loginDataLine = _PrepareLoginRecord();

        fstream loginRegisterFile;
        loginRegisterFile.open("LoginRegister.txt", ios::out | ios::app);

        if (loginRegisterFile.is_open())
        {
            loginRegisterFile << loginDataLine << endl;
            loginRegisterFile.close();
        }
    }

    static vector <stLoginRegisterRecord> GetLoginRegisterRecord()
    {
        vector <stLoginRegisterRecord> vLoginRegister;
        fstream loginRegisterFile;

        loginRegisterFile.open("LoginRegister.txt", ios::in);

        if (loginRegisterFile.is_open())
        {               
            stLoginRegisterRecord loginRegRecord;
            string dataLine = "";

            while (getline(loginRegisterFile, dataLine))
            {
                if (dataLine != "")
                {
                    loginRegRecord = _ConvertLoginRegisterLineToRecord(dataLine);
                    vLoginRegister.push_back(loginRegRecord);
                }
            }
            loginRegisterFile.close();
        }
        return vLoginRegister;
    }
};