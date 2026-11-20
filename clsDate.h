#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <iomanip>
#include <string>
#include "clsString.h"

using namespace std;

class clsDate
{
	short _year = 1900;
	short _month = 1;
	short _day = 1;

public:
	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_year = now->tm_year + 1900;
		_month = now->tm_mon + 1;
		_day = now->tm_mday;
	}

	clsDate(string strDate)
	{
		clsDate date = StringToDate(strDate);
		_day = date._day;
		_month = date._month;
		_year = date._year;
	}

	clsDate(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
	}

	clsDate(int dayOrderInYear, short year)
	{
		clsDate date = GetDateFromDayOrderInYear(dayOrderInYear, year);
		_day = date._day;
		_month = date._month;
		_year = date._year;
	}

	void SetDay(short day)
	{
		_day = day;
	}

	short GetDay()
	{
		return _day;
	}

	void SetMonth(short month)
	{
		_month = month;
	}

	short GetMonth()
	{
		return _month;
	}

	void SetYear(short year)
	{
		_year = year;
	}

	short GetYear()
	{
		return _year;
	}

	static short ReadNumber(string message)
	{
		short number = 0;
		cout << message;
		cin >> number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "INVALID! Enter a valid number: ";
			cin >> number;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return number;
	}

	short ReadYear()
	{
		short year = ReadNumber("Enter a year: ");
		return year;
	}

	short ReadMonth()
	{
		short month = 0;
		month = ReadNumber("Enter a month: ");

		while (month < 1 || month > 12)
		{
			cout << "\nINVALID! Month must be between 1 and 12.\n";
			month = ReadNumber("Enter a month: ");
		}
		return month;
	}

	short ReadDay(short month, short year)
	{
		short day = 0;
		short maxDaysInMonth = DaysInMonth(month, year);
		day = ReadNumber("Enter a day: ");

		while (day < 1 || day>maxDaysInMonth)
		{
			cout << "\nINVALID! Day for month " << month << " must be between 1 and " << maxDaysInMonth << endl;
			day = ReadNumber("Enter a day: ");
		}
		return day;
	}

	clsDate ReadDate()
	{
		clsDate date;
		date._year = ReadYear();
		date._month = ReadMonth();
		date._day = ReadDay(date._month, date._year);
		return date;
	}

	void Print()
	{
		cout << DateToString() << endl;
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short year = now->tm_year + 1900;
		short month = now->tm_mon + 1;
		short day = now->tm_mday;

		return clsDate(day, month, year);
	}

	static clsDate StringToDate(string strDate)
	{
		vector <string> vDate = clsString::SplitString(strDate, "/");

		short day = stoi(vDate[0]);
		short month = stoi(vDate[1]);
		short year = stoi(vDate[2]);
		return clsDate(day, month, year);
	}

	static bool IsLeapYear(short year)
	{
		return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	}

    bool IsLeapYear()
	{
		return IsLeapYear(_year);
	}

	static short DaysInYear(short year)
	{
		return IsLeapYear(year) ? 366 : 365;
	}

	short DaysInYear()
	{
		return DaysInYear(_year);
	}

	static short HoursInYear(short year)
	{
		return DaysInYear(year) * 24;
	}

	short HoursInYear()
	{
		return HoursInYear(_year);
	}

	static int MinutesInYear(short year)
	{
		return HoursInYear(year) * 60;
	}

	int MinutesInYear()
	{
		return MinutesInYear(_year);
	}

	static int SecondsInYear(short year)
	{
		return MinutesInYear(year) * 60;
	}

	int SecondsInYear()
	{
		return SecondsInYear(_year);
	}

	static short DaysInMonth(short month, short year)
	{
		if (month < 1 || month > 12)
			return 0;
		short daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (month == 2)
			return IsLeapYear(year) ? 29 : 28;

		return daysOfMonth[month - 1];
	}

	short DaysInMonth()
	{
		return DaysInMonth(_month, _year);
	}

	static short HoursInMonth(short month, short year)
	{
		return DaysInMonth(month, year) * 24;
	}

	short HoursInMonth()
	{
		return HoursInMonth(_month, _year);
	}

	static int MinutesInMonth(short month, short year)
	{
		return HoursInMonth(month, year) * 60;
	}

	int MinutesInMonth()
	{
		return MinutesInMonth(_year, _month);
	}

	static int SecondsInMonth(short month, short year)
	{
		return MinutesInMonth(month, year) * 60;
	}

	int SecondsInMonth()
	{
		return SecondsInMonth(_year, _month);
	}

	static bool IsValidDate(clsDate date) 
	{
		if (date._month < 1 || date._month > 12)
			return false;

		if (date._day < 1 || date._day > 31)
			return false;

		short daysInMonth = DaysInMonth(date._month, date._year);
		if (date._day > daysInMonth)
			return false;

		return true;
	}

	bool IsValidDate()
	{
		return IsValidDate(*this);
	}	
	
	static short DayOrderOfWeek(short day, short month, short year)
	{
		float a = (14 - month) / 12;
		float y = year - a;
		float m = month + 12 * a - 2;
		short k = day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12);

		return k % 7;
	}

	short DayOrderOfWeek()
	{
		return DayOrderOfWeek(_day, _month, _year);
	}

	static string GetDayName(short day, short month, short year)
	{
		string arrDayName[] = { "Sunday", "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };

		return arrDayName[DayOrderOfWeek(day, month, year)];
	}

	string GetDayName()
	{
		return GetDayName(_day, _month, _year);
	}

	static string GetMonthName(short month)
	{
		string arrMonthName[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return arrMonthName[month - 1];
	}

	string GetMonthName()
	{
		return GetMonthName(_month);
	}

	static void PrintMonthCalendar(short month, short year)
	{
		short dayOrderOfWeek = DayOrderOfWeek(1, month, year);
		short numberOfDaysInMonth = DaysInMonth(month, year);
		cout << "\n   _________________{" << GetMonthName(month) << "}_________________\n\n";
		cout << "   Sun   Mon   Tue   Wed   Thu   Fri   Sat   \n";

		for (short i = 0; i < dayOrderOfWeek; i++)
			cout << "      ";

		for (short i = 1; i <= numberOfDaysInMonth; i++)
		{
			printf("%6d", i);
			if ((i + dayOrderOfWeek) % 7 == 0)
				cout << endl;
		}
		cout << "\n   _______________________________________\n";
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_month, _year);
	}

	static void PrintYearCalendar(short year)
	{
		cout << "\n   _______________________________________\n\n";
		cout << "\t\t" << year << " - Calendar";
		cout << "\n   _______________________________________\n";
		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, year);
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(_year);
	}

	static short DaysFromYearStart(short day, short month, short year)
	{
		short days = 0;
		for (short i = 1; i < month; i++)
			days += DaysInMonth(i, year);
		days += day;

		return days;
	}

	short DaysFromYearStart()
	{
		return DaysFromYearStart(_day, _month, _year);
	}

	static clsDate GetDateFromDayOrderInYear(short dayOrderInYear, short Year)
	{
		short counter = 0;
		while (dayOrderInYear > 0)
		{
			counter++;
			short currentMonthDays = DaysInMonth(counter, Year);
			if (dayOrderInYear > currentMonthDays)
				dayOrderInYear -= DaysInMonth(counter, Year);
			else
				break;
		}
		short year = Year;
		short month = counter;
		short day = dayOrderInYear;

		return clsDate(day, month, year);
	}

	clsDate GetDateFromDayOrderInYear(short dayOrderInYear)
	{
		return GetDateFromDayOrderInYear(dayOrderInYear, _year);
	}

	static clsDate AddDaysToDate(clsDate& date, int daysToAdd)
	{
		int totalDays = daysToAdd + DaysFromYearStart(date._day, date._month, date._year);
		date._month = 1;

		while (true)
		{
			short daysInMonth = DaysInMonth(date._month, date._year);
			if (totalDays > daysInMonth)
			{
				totalDays -= daysInMonth;
				date._month++;
				if (date._month > 12)
				{
					date._month = 1;
					date._year++;
				}
			}
			else
			{
				date._day = totalDays;
				break;
			}
		}
		return date;
	}

	clsDate AddDaysToDate(int daysToAdd)
	{
		return AddDaysToDate(*this, daysToAdd);
	}

	static bool IsDate1BeforeDate2(clsDate date1, clsDate date2)
	{
		if (date1._year < date2._year)
			return true;
		if ((date1._year <= date2._year) && (date1._month < date2._month))
			return true;
		if ((date1._year <= date2._year) && (date1._month <= date2._month) && (date1._day < date2._day))
			return true;
		return false;
	}

	bool IsDate1BeforeDate2(clsDate date2)
	{
		return IsDate1BeforeDate2(*this, date2);
	}

	static bool IsDate1EqualToDate2(clsDate date1, clsDate date2)
	{
		if ((date1._year == date2._year) && (date1._month == date2._month) && (date1._day == date2._day))
			return true;
		return false;
	}

	bool IsDate1EqualToDate2(clsDate date2)
	{
		return IsDate1EqualToDate2(*this, date2);
	}

	static bool IsDate1AfterDate2(clsDate date1, clsDate date2)
	{
		return !IsDate1BeforeDate2(date1, date2) && !IsDate1EqualToDate2(date1, date2);
	}

	bool IsDate1AfterDate2(clsDate date2)
	{
		return IsDate1AfterDate2(*this, date2);
	}

	static bool IsLastDayInMonth(clsDate date)
	{
		return date._day == DaysInMonth(date._month, date._year);
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(clsDate date)
	{
		return date._month == 12;
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(*this);
	}

	static void IncreaseDateByOne(clsDate& date)
	{
		if (IsLastDayInMonth(date))
		{
			if (IsLastMonthInYear(date))
			{
				date._day = 1;
				date._month = 1;
				date._year++;
			}
			else
			{
				date._day = 1;
				date._month++;
			}
		}
		else
			date._day++;
	}

	void IncreaseDateByOne()
	{
		IncreaseDateByOne(*this);
	}

	static int AgeInDays(clsDate date)
	{
		clsDate systemDate = GetSystemDate();
		return DifferenceInDaysBetweenDates(date, systemDate, true);
	}

	int AgeInDays()
	{
		clsDate systemDate = GetSystemDate();
		return DifferenceInDaysBetweenDates(*this, systemDate, true);
	}

	static void SwapDates(clsDate& date1, clsDate& date2)
	{
		clsDate tempDate;
		tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}

	void SwapDates(clsDate& date2)
	{
		SwapDates(*this, date2);
	}

	static int DifferenceInDaysBetweenDates(clsDate date1, clsDate date2, bool isEndDayInclude = true)
	{
		if (IsDate1EqualToDate2(date1, date2))
			return 0;

		int diffDays = 0;
		short negativeFlag = 1;

		if (!IsDate1BeforeDate2(date1, date2))
		{
			SwapDates(date1, date2);
			negativeFlag = -1;
		}
		while (date1._year < date2._year)
		{
			diffDays += IsLeapYear(date1._year) ? 366 : 365;
			date1._year++;
		}

		diffDays += DaysFromYearStart(date2._day, date2._month, date2._year) - DaysFromYearStart(date1._day, date1._month, date1._year);
		return isEndDayInclude ? (++diffDays) * negativeFlag : diffDays * negativeFlag;
	}

	int DifferenceInDaysBetweenDates(clsDate date2, bool isEndDayInclude = true)
	{
		return DifferenceInDaysBetweenDates(*this, date2, isEndDayInclude);
	}

	static void IncreaseDateByXDays(clsDate& date, int days)
	{
		for (int i = 0; i < days; i++)
			IncreaseDateByOne(date);
	}

	void IncreaseDateByXDays(int days)
	{
		IncreaseDateByXDays(*this, days);
	}

	static void IncreaseDateByOneWeek(clsDate& date)
	{
		IncreaseDateByXDays(date, 7);
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static void IncreaseDateByXWeeks(clsDate& date, int weeks)
	{
		for (int i = 0; i < weeks; i++)
			IncreaseDateByOneWeek(date);
	}

	void IncreaseDateByXWeeks(int weeks)
	{
		IncreaseDateByXWeeks(*this, weeks);
	}

	static void IncreaseDateByOneMonth(clsDate& date)
	{
		if (date._month == 12)
		{
			date._month = 1;
			date._year++;
		}
		else
			date._month++;

		short maxDaysInCurrentMonth = DaysInMonth(date._month, date._year);
		if (date._day > maxDaysInCurrentMonth)
			date._day = maxDaysInCurrentMonth;
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static void IncreaseDateByXMonths(clsDate& date, short months)
	{
		for (short i = 0; i < months; i++)
			IncreaseDateByOneMonth(date);
	}

	void IncreaseDateByXMonths(short months)
	{
		IncreaseDateByXMonths(*this, months);
	}

	static void IncreaseDateByOneYear(clsDate& date)
	{
		date._year++;
		if (date._month == 2 && date._day == 29 && !IsLeapYear(date._year))
			date._day = 28;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static void IncreaseDateByXYears(clsDate& date, short years)
	{
		for (short i = 0; i < years; i++)
			IncreaseDateByOneYear(date);
	}

	void IncreaseDateByXYears(short years)
	{
		IncreaseDateByXYears(*this, years);
	}

	static void IncreaseDateByOneDecade(clsDate& date)
	{
		IncreaseDateByXYears(date, 10);
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static void IncreaseDateByXDecades(clsDate& date, short decades)
	{
		for (short i = 0; i < decades; i++)
			IncreaseDateByOneDecade(date);
	}

	void IncreaseDateByXDecades(short decades)
	{
		IncreaseDateByXDecades(*this, decades);
	}

	static void IncreaseDateByOneCentury(clsDate& date)
	{
		IncreaseDateByXYears(date, 100);
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static void IncreaseDateByXCentury(clsDate& date, short centuries)
	{
		for (short i = 0; i < centuries; i++)
			IncreaseDateByOneCentury(date);
	}

	void IncreaseDateByXCentury(short centuries)
	{
		IncreaseDateByXCentury(*this, centuries);
	}

	static void IncreaseDateByOneMillennium(clsDate& date)
	{
		IncreaseDateByXYears(date, 1000);
	}

	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	static void IncreaseDateByXMillenniums(clsDate& date, short millenniums)
	{
		for (short i = 0; i < millenniums; i++)
			IncreaseDateByOneMillennium(date);
	}

	void IncreaseDateByXMillenniums(short millenniums)
	{
		IncreaseDateByXMillenniums(*this, millenniums);
	}

	static void DecreaseDateByOneDay(clsDate& date)
	{
		if (date._day == 1)
		{
			if (date._month == 1)
			{
				date._day = 31;
				date._month = 12;
				date._year--;
			}
			else
			{
				date._month--;
				date._day = DaysInMonth(date._month, date._year);
			}
		}
		else
			date._day--;
	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static void DecreaseDateByXDays(clsDate& date, int days)
	{
		for (int i = 0; i < days; i++)
			DecreaseDateByOneDay(date);
	}

	void DecreaseDateByXDays(int days)
	{
		DecreaseDateByXDays(*this, days);
	}

	static void DecreaseDateByOneWeek(clsDate& date)
	{
		DecreaseDateByXDays(date, 7);
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static void DecreaseDateByXWeeks(clsDate& date, int weeks)
	{
		for (int i = 0; i < weeks; i++)
			DecreaseDateByOneWeek(date);
	}

	void DecreaseDateByXWeeks(int weeks)
	{
		DecreaseDateByXWeeks(*this, weeks);
	}

	static void DecreaseDateByOneMonth(clsDate& date)
	{
		if (date._month == 1)
		{
			date._month = 12;
			date._year--;
		}
		else
			date._month--;

		short maxDaysInCurrentMonth = DaysInMonth(date._month, date._year);
		if (date._day > maxDaysInCurrentMonth)
			date._day = maxDaysInCurrentMonth;
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static void DecreaseDateByXMonths(clsDate& date, short months)
	{
		for (short i = 0; i < months; i++)
			DecreaseDateByOneMonth(date);
	}

	void DecreaseDateByXMonths(short months)
	{
		DecreaseDateByXMonths(*this, months);
	}

	static void DecreaseDateByOneYear(clsDate& date)
	{
		date._year--;
		if (date._month == 2 && date._day == 29 && !IsLeapYear(date._year))
			date._day = 28;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static void DecreaseDateByXYears(clsDate& date, short years)
	{
		for (short i = 0; i < years; i++)
			DecreaseDateByOneYear(date);
	}

	void DecreaseDateByXYears(short years)
	{
		DecreaseDateByXYears(*this, years);
	}

	static void DecreaseDateByOneDecade(clsDate& date)
	{
		DecreaseDateByXYears(date, 10);
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static void DecreaseDateByXDecades(clsDate& date, short decades)
	{
		for (short i = 0; i < decades; i++)
			DecreaseDateByOneDecade(date);
	}

	void DecreaseDateByXDecades(short decades)
	{
		DecreaseDateByXDecades(*this, decades);
	}

	static void DecreaseDateByOneCentury(clsDate& date)
	{
		DecreaseDateByXYears(date, 100);
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static void DecreaseDateByXCentury(clsDate& date, short centuries)
	{
		for (short i = 0; i < centuries; i++)
			DecreaseDateByOneCentury(date);
	}

	void DecreaseDateByXCentury(short centuries)
	{
		DecreaseDateByXCentury(*this, centuries);
	}

	static void DecreaseDateByOneMillennium(clsDate& date)
	{
		DecreaseDateByXYears(date, 1000);
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	static void DecreaseDateByXMillenniums(clsDate& date, short millenniums)
	{
		for (short i = 0; i < millenniums; i++)
			DecreaseDateByOneMillennium(date);
	}

	void DecreaseDateByXMillenniums(short millenniums)
	{
		DecreaseDateByXMillenniums(*this, millenniums);
	}

	static string DateToString(clsDate date)
	{
		return to_string(date._day) + "/" + to_string(date._month) + "/" + to_string(date._year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static void PrintTodayDate()
	{
		clsDate date = GetSystemDate();
		string dayName = GetDayName(date._day, date._month, date._year);
		cout << "Today's Date is: " << dayName << ", " << DateToString(date) << endl;
	}

	static bool IsEndOfWeek(clsDate date)
	{
		return DayOrderOfWeek(date._day, date._month, date._year) == 5;
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate date)
	{
		short dayOrder = DayOrderOfWeek(date._day, date._month, date._year);
		return dayOrder == 0 || dayOrder == 6;
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate date)
	{
		return !IsWeekEnd(date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate date)
	{
		return 6 - DayOrderOfWeek(date._day, date._month, date._year);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate date)
	{
		return DaysInMonth(date._month, date._year) - date._day;
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate date)
	{
		return DaysInYear(date._year) - DaysFromYearStart(date._day, date._month, date._year);
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateVacationDays(clsDate startDate, clsDate endDate)
	{
		if (IsDate1EqualToDate2(startDate, endDate))
			return 0;

		if (!IsDate1BeforeDate2(startDate, endDate))
		{
			cout << "\nInvalid! must start date be before end date\n";
			return 0;
		}
		short vacationDays = 0;

		while (IsDate1BeforeDate2(startDate, endDate))
		{
			if (IsBusinessDay(startDate))
			{
				vacationDays++;
			}
			IncreaseDateByOne(startDate);
		}
		if (IsBusinessDay(endDate))
			vacationDays++;

		return vacationDays;
	}

	static clsDate CalculateVacationReturnDate(clsDate startDate, short vacationDays)
	{
		while (vacationDays > 0)
		{
			if (IsBusinessDay(startDate))
				vacationDays--;
			IncreaseDateByOne(startDate);
		}
		while (IsWeekEnd(startDate))
			IncreaseDateByOne(startDate);
		return startDate;
	}

	enum enCompareDates { Before = -1, Equal = 0, After = 1 };

	static enCompareDates CompareDates(clsDate date1, clsDate date2)
	{
		if (IsDate1BeforeDate2(date1, date2))
			return enCompareDates::Before;

		if (IsDate1EqualToDate2(date1, date2))
			return enCompareDates::Equal;

		return enCompareDates::After;
	}

	enCompareDates CompareDates(clsDate date2)
	{
		return CompareDates(*this, date2);
	}

	static string FormatDate(clsDate date, string DateFormat = "dd/mm/yyyy")
	{
		string formattedStringDate = DateFormat;
		formattedStringDate = clsString::ReplaceWordInString(formattedStringDate, "dd", to_string(date._day));
		formattedStringDate = clsString::ReplaceWordInString(formattedStringDate, "mm", to_string(date._month));
		formattedStringDate = clsString::ReplaceWordInString(formattedStringDate, "yyyy", to_string(date._year));

		return formattedStringDate;
	}

	string FormatDate(string DateFormat = "dd/mm/yyyy")
	{
		return FormatDate(*this, DateFormat);
	}
};