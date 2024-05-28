#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

template <class T > class  clsInputValidation
{
public:

	static bool IsNumberBetween(T LowestNumber, T HighestNumber, T Number)
	{
		return (LowestNumber < Number&& HighestNumber > Number);
	}
	static bool IsDateBetween(clsDate Date, clsDate FirstDate, clsDate SecondDate)
	{
		return (clsDate::IsDate1AfterThanDate2(Date, FirstDate) && clsDate::IsDate1BeforeThanDate2(Date, SecondDate));
	}
	static T ReadNumber(string Message = "Please Enter Int Number: ", string ErrorMessage = "Try Again Babe,")
	{
		T Number = 0;

		cout << Message;
		cin >> Number;


		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage << "\n";
			cin >> Number;
		}

		return Number;
	}
	static string ReadString(string Message = "Plese Enter A String: ")
	{
		string String;

		cout << Message;
		getline(cin >> ws, String);

		return String;
	}
	static T ReadNumberBetween(int LowestNumber, int HighestNumber, string Message = "Please Enter Int Number: ", string ErrorMessage = "Try Again Babe,")
	{
		T Number = ReadNumber(Message, ErrorMessage);

		while (!IsNumberBetween(LowestNumber, HighestNumber, Number))
		{
			cout << ErrorMessage << "\n";
			Number = ReadNumber(Message, ErrorMessage);
		};

		return Number;
	}
	static bool ISValidDate(clsDate Date)
	{
		if (Date.Day > clsDate::NumberOfDaysInMonth(Date.Year, Date.Month))
			return false;

		if (Date.Month > 12)
			return false;

		return true;
	}
};


