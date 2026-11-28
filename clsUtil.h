#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "clsDate.h"

using namespace std;

class clsUtil
{
public:   
    enum enCharType { SmallLetter = 1, CapitalLetter, SpecialCharacter, Digit, Mix };

	static void Swap(int& num1, int& num2)
	{
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}
  
	static void Swap(double& num1, double& num2)
	{
		double temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void Swap(bool& b1, bool& b2)
	{
		bool temp = b1;
		b1 = b2;
		b2 = temp;
	}

	static void Swap(char& c1, char& c2)
	{
		char temp = c1;
		c1 = c2;
		c2 = temp;
	}

	static void Swap(string& text1, string& text2)
	{
		string temp = text1;
		text1 = text2;
		text2 = temp;
	}

	static void Swap(clsDate& date1, clsDate& date2)
	{
		clsDate temp = date1;
		date1 = date2;
		date2 = temp;
	}

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int GetRandomNumber(int from, int to)
    {
        int randNumber = rand() % (to - from + 1) + from;
        return randNumber;
    }

	static char GetRandomCharacter(enCharType charType)
	{
		switch (charType)
		{
		case enCharType::SmallLetter:
			return char(GetRandomNumber(97, 122));

		case enCharType::CapitalLetter:
			return char(GetRandomNumber(65, 90));

		case enCharType::SpecialCharacter:
			return char(GetRandomNumber(33, 47));

		case enCharType::Digit:
			return char(GetRandomNumber(48, 57));

		case enCharType::Mix:
			short randomNumber = GetRandomNumber(1, 4);
			return GetRandomCharacter((enCharType)randomNumber);
		}
	}

	static string GenerateWord(enCharType charType, short wordLength)
	{
		string word = "";
		for (short i = 0; i < wordLength; i++)
		{
			word += GetRandomCharacter(charType);
		}
		return word;
	}

	static string GenerateKey(short keyLength)
	{
		string key = GenerateWord(enCharType::CapitalLetter, keyLength) + "-";
		key += GenerateWord(enCharType::CapitalLetter, keyLength) + "-";
		key += GenerateWord(enCharType::CapitalLetter, keyLength) + "-";
		key += GenerateWord(enCharType::CapitalLetter, keyLength);

		return key;
	}

	static void GenerateKeys(short keyNumbers)
	{
		for (short i = 0; i < keyNumbers; i++)
		{
			cout << "Key[" << i + 1 << "]: " << GenerateKey(4) << endl;
		}
	}

	static void FillArrayWithRandomNumbers(int arr[100], short arrLength)
	{
		for (short i = 0; i < arrLength; i++)
		{
			arr[i] = GetRandomNumber(1, 100);
		}
	}

	static void FillArrayWithOrderedNumbers(int arr[100], short arrLength)
	{
		for (short i = 0; i < arrLength; i++)
		{
			arr[i] = i + 1;
		}
	}

	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateWord(CharType, Wordlength);

	}

	static void FillArrayWithRandomKeys(string keysArray[100], short keyNumbers)
	{
		for (short i = 0; i < keyNumbers; i++)
		{
			keysArray[i] = GenerateKey(4);
		}
	}

	static void PrintArray(int arr[100], short arrLength)
	{
		for (short i = 0; i < arrLength; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	static void ShuffleOrderedArray(int array[100], short arrLength)
	{
		for (short i = 0; i < arrLength; i++)
		{
			int randomIndex = GetRandomNumber(0, arrLength - 1);
			Swap(array[i], array[randomIndex]);
		}
	}

	static string EncryptText(string text, short EncryptionKey)
	{
		string encryptedText = "";

		for (int i = 0; i < text.length(); i++)
		{
			encryptedText += char(text[i] + EncryptionKey);
		}
		return encryptedText;
	}

	static string DecryptText(string text, short DecryptionKey)
	{
		string DecryptedText = "";

		for (int i = 0; i < text.length(); i++)
		{
			DecryptedText += char(text[i] - DecryptionKey);
		}
		return DecryptedText;
	}

	static string  Tabs(short numberOfTabs)
	{
		string t = "";
		for (int i = 1; i < numberOfTabs; i++)
		{
			t = t + "\t";
			cout << t;
		}
		return t;
	}
};