#pragma once
#include <iostream>

using namespace std;

class clsPerson
{
private:
    string _firstName = "";
    string _lastName = "";
    string _email = "";
    string _phone = "";
public:
    clsPerson(string firstName, string lastName, string email, string phone)
    {
        _firstName = firstName;
        _lastName = lastName;
        _email = email;
        _phone = phone;
    }

    void SetFirstName(string firstName)
    {
        _firstName = firstName;
    }

    string GetFirstName()
    {
        return _firstName;
    }

    void SetLastName(string lastName)
    {
        _lastName = lastName;
    }

    string GetLastName()
    {
        return _lastName;
    }

    string GetFullName()
    {
        return _firstName + " " + _lastName;
    }

    void SetEmail(string email)
    {
        _email = email;
    }

    string GetEmail()
    {
        return _email;
    }

    void SetPhone(string phone)
    {
        _phone = phone;
    }

    string GetPhone()
    {
        return _phone;
    }
};