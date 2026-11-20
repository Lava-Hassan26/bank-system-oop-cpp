#pragma once
#include <iostream>
#include <limits>
#include "clsDate.h"
using namespace std;

class clsInputValidation
{
public:

	static short ReadShortNumber(string errorMessage = "INVALID! Enter a valid number: ")
	{
		short number = 0;
		cin >> number;

		while (cin.fail())
		{
			cin.clear(); // resets the error state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static int ReadIntNumber(string errorMessage = "INVALID! Enter a valid number: ")
	{
		int number = 0;
		cin >> number;

		while (cin.fail())
		{
			cin.clear(); // resets the error state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static float ReadFloatNumber(string errorMessage = "INVALID! Enter a valid number: ")
	{
		float number = 0;
		cin >> number;

		while (cin.fail())
		{
			cin.clear(); // resets the error state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static double ReadDoubleNumber(string errorMessage = "INVALID! Enter a valid number: ")
	{
		double number = 0;
		cin >> number;

		while (cin.fail())
		{
			cin.clear(); // resets the error state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << errorMessage;
			cin >> number;
		}
		return number;
	}

	static bool IsNumberBetween(short number, short from, short to)
	{
		if (number<from || number>to)
			return false;
		return true;
	}

	static bool IsNumberBetween(int number, int from, int to)
	{
		if (number<from || number>to)
			return false;
		return true;
	}

	static bool IsNumberBetween(float number, float from, float to)
	{
		if (number<from || number>to)
			return false;
		return true;
	}

	static bool IsNumberBetween(double number, double from, double to)
	{
		if (number<from || number>to)
			return false;
		return true;
	}

	static bool IsValidDate(clsDate date)
	{
		return clsDate::IsValidDate(date);
	}

	static bool IsDateBetween(clsDate date, clsDate dateFrom, clsDate dateTo)
	{
		if (!IsValidDate(date) || !IsValidDate(dateFrom) || !IsValidDate(dateTo))
			return false;

		if (clsDate::IsDate1AfterDate2(dateFrom, dateTo))
			clsDate::SwapDates(dateFrom, dateTo);

		if (clsDate::IsDate1BeforeDate2(date, dateFrom) || clsDate::IsDate1AfterDate2(date, dateTo))
			return false;
		return true;
	}

	static short ReadNumberBetween(short from, short to, string errorMessage = "Number is not within range, enter again: ")
	{
		short number = 0;
		do
		{
			number = ReadShortNumber(errorMessage);
		} while (!IsNumberBetween(number, from, to));

		return number;
	}

	static int ReadNumberBetween(int from, int to, string errorMessage = "Number is not within range, enter again: ")
	{
		int number = 0;
		do
		{
			number = ReadIntNumber(errorMessage);
		} while (!IsNumberBetween(number, from, to));

		return number;
	}

	static float ReadNumberBetween(float from, float to, string errorMessage = "Number is not within range, enter again: ")
	{
		float number = 0;
		do
		{
			number = ReadFloatNumber(errorMessage);
		} while (!IsNumberBetween(number, from, to));

		return number;
	}

	static double ReadNumberBetween(double from, double to, string errorMessage = "Number is not within range, enter again: ")
	{
		double number = 0;
		do
		{
			number = ReadDoubleNumber(errorMessage);
		} while (!IsNumberBetween(number, from, to));

		return number;
	}

	static string ReadString(string message)
	{
		string text = "";

		cout << message;
		getline(cin >> ws, text);

		return text;
	}
};