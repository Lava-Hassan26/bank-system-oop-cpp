#pragma once
#include <iostream>
#include <vector>

using namespace std;

class clsString
{
	string _text = "";
public:
	clsString()
	{
		string _text = "";
	}

	clsString(string text)
	{
		_text = text;
	}

	void SetText(string text)
	{
		_text = text;
	}

	string GetText()
	{
		return _text;
	}

	static void PrintFirstLetterOfEachWord(string text)
	{
		bool isFirstLetter = true;
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] != ' ' && isFirstLetter == true)
			{
				cout << text[i] << endl;
			}
			if (text[i] == ' ')
				isFirstLetter = true;
			else
				isFirstLetter = false;
		}
	}

	void PrintFirstLetterOfEachWord()
	{
		PrintFirstLetterOfEachWord(_text);
	}

	static string UpperFirstLetterOfEachWord(string text)
	{
		bool isFirstLetter = true;
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] != ' ' && isFirstLetter == true)
				text[i] = toupper(text[i]);

			isFirstLetter = (text[i] == ' ') ? true : false;
		}
		return text;
	}

	void UpperFirstLetterOfEachWord()
	{
		_text = UpperFirstLetterOfEachWord(_text);
	}

	static string LowerFirstLetterOfEachWord(string text)
	{
		bool isFirstLetter = true;
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] != ' ' && isFirstLetter == true)
				text[i] = tolower(text[i]);

			isFirstLetter = (text[i] == ' ') ? true : false;
		}
		return text;
	}

	void LowerFirstLetterOfEachWord()
	{
		_text = LowerFirstLetterOfEachWord(_text);
	}

	static string LowerAllLetters(string text)
	{
		for (int i = 0; i < text.length(); i++)
			text[i] = tolower(text[i]);
		return text;
	}

	void LowerAllLetters()
	{
		_text = LowerAllLetters(_text);
	}

	static string UpperAllLetters(string text)
	{
		for (int i = 0; i < text.length(); i++)
			text[i] = toupper(text[i]);
		return text;
	}

	void UpperAllLetters()
	{
		_text = UpperAllLetters(_text);
	}

	static char InvertLetterCase(char C)
	{
		return isupper(C) ? tolower(C) : toupper(C);
	}

	static string InvertAllLettersCase(string text)
	{
		for (int i = 0; i < text.length(); i++)
			text[i] = InvertLetterCase(text[i]);
		return text;
	}

	void InvertAllLettersCase()
	{
		_text = InvertAllLettersCase(_text);
	}

	static int CountSmallLetters(string text)
	{
		int counter = 0;
		for (int i = 0; i < text.length(); i++)
			if (islower(text[i]))
				counter++;
		return counter;
	}

	int CountSmallLetters()
	{
		return CountSmallLetters(_text);
	}

	static int CountCapitalLetters(string text)
	{
		int counter = 0;
		for (int i = 0; i < text.length(); i++)
			if (isupper(text[i]))
				counter++;
		return counter;
	}

	int CountCapitalLetters()
	{
		return CountCapitalLetters(_text);
	}

	static int CountLetter(string text, char letterToCount)
	{
		int counter = 0;
		for (int i = 0; i < text.length(); i++)
			if (text[i] == letterToCount)
				counter++;
		return counter;
	}

	int CountLetter(char letterToCount)
	{
		return CountLetter(_text, letterToCount);
	}

	static int CountLetter(string text, char letterToCount, bool matchCase)
	{
		int counter = 0;
		for (int i = 0; i < text.length(); i++)
		{
			if (matchCase)
			{
				if (text[i] == letterToCount)
					counter++;
			}
			else
			{
				if (tolower(text[i]) == tolower(letterToCount))
					counter++;
			}
		}
		return counter;
	}

	int CountLetter(char letterToCount, bool matchCase = 1)
	{
		return CountLetter(_text, letterToCount, matchCase);
	}

	static bool IsVowel(char c)
	{
		c = tolower(c);
		return (c == 'a' || c == 'e' || c == 'o' || c == 'u' || c == 'i');
	}

	static int CountVowels(string text)
	{
		int counter = 0;
		for (int i = 0; i < text.length(); i++)
			if (IsVowel(text[i]))
				counter++;
		return counter;
	}

	int CountVowels()
	{
		return CountVowels(_text);
	}

	static void PrintAllVowels(string text)
	{
		cout << "Vowels in text: ";
		int counter = 0;
		for (int i = 0; i < text.length(); i++)
			if (IsVowel(text[i]))
				cout << text[i] << "  ";
	}

	void PrintAllVowels()
	{
		PrintAllVowels(_text);
	}

	static void PrintEachWordInString(string text, string delim)
	{
		string word = "";
		short pos = 0;

		while ((pos = text.find(delim)) != std::string::npos)
		{
			word = text.substr(0, pos);

			if (word != "")
				cout << word << endl;

			text.erase(0, pos + delim.length());
		}
		if (text != "")
			cout << text << endl;
	}

	void PrintEachWordInString(string delim = " ")
	{
		PrintEachWordInString(_text, delim);
	}

	static int CountWords(string text, string delim)
	{
		string word = "";
		short pos = 0;
		short counter = 0;

		pos = text.find(delim);
		while ((pos) != std::string::npos)
		{
			word = text.substr(0, pos);
			if (word != "")
				counter++;
			text.erase(0, pos + delim.length());
			pos = text.find(delim);
		}
		if (text != "")
			counter++;
		return counter;
	}

	int CountWords(string delim = " ")
	{
		return CountWords(_text, delim);
	}

	static vector<string> SplitString(string text, string delim)
	{
		vector<string> vWords;
		string word = "";
		short pos = 0;
		pos = text.find(delim);

		while ((pos) != std::string::npos)
		{
			word = text.substr(0, pos);
			//if (word != "")
				vWords.push_back(word);
			text.erase(0, pos + delim.length());
			pos = text.find(delim);
		}
		if (text != "")
			vWords.push_back(text);
		return vWords;
	}

	vector<string> SplitString(string delim = " ")
	{
		return SplitString(_text, delim);
	}

	static string TrimLeft(string text)
	{
		for (short i = 0; i < text.length(); i++)
			if (text[i] != ' ')
				return text.erase(0, i);
	}

	void TrimLeft()
	{
		_text = TrimLeft(_text);
	}

	static string TrimRight(string text)
	{
		for (short i = text.length() - 1; i >= 0; i--)
			if (text[i] != ' ')
				return text.erase(i + 1, text.length() - 1 - i);
	}

	void TrimRight()
	{
		_text = TrimRight(_text);
	}

	static string Trim(string text)
	{
		return TrimRight(TrimLeft(text));
	}

	void Trim()
	{
		_text = Trim(_text);
	}

	static string JoinString(vector<string>& vWords, string delim = " ")
	{
		string text = "";
		for (string& word : vWords)
			text += word + delim;

		return text = text.substr(0, text.length() - delim.length());
	}

	static string JoinString(string arrWords[], short length, string delim = " ")
	{
		string text = "";
		for (short i = 0; i < length; i++)
			text += arrWords[i] + delim;

		return text = text.substr(0, text.length() - delim.length());
	}

	static string ReverseWords(string text, string delim)
	{
		vector<string> vWords = SplitString(text, delim);
		vector<string> vReversedWords;

		for (short i = 0; i < vWords.size(); i++)
			vReversedWords.push_back(vWords[vWords.size() - i - 1]);

		return JoinString(vReversedWords, delim);
	}

	void ReverseWords(string delim = " ")
	{
		_text = ReverseWords(_text, delim);
	}

	static string ReplaceWords(string text, string currentWord, string replacementWord, string delim)
	{
		vector<string> vWords = SplitString(text, delim);

		for (string& word : vWords)
			if (word == currentWord)
				word = replacementWord;

		return JoinString(vWords, delim);
	}

	void ReplaceWords(string currentWord, string replacementWord, string delim = " ")
	{
		_text = ReplaceWords(_text, currentWord, replacementWord, delim);
	}

	static string ReplaceWords(string text, string currentWord, string replacementWord, bool isMatchCase, string delim)
	{
		vector<string> vWords = SplitString(text, delim);

		for (string& word : vWords)
		{
			if (isMatchCase)
			{
				if (word == currentWord)
					word = replacementWord;
			}
			else
			{
				if (LowerAllLetters(word) == LowerAllLetters(currentWord))
					word = replacementWord;
			}
		}
		return JoinString(vWords, delim);
	}

	void ReplaceWords(string currentWord, string replacementWord, bool isMatchCase = true, string delim = " ")
	{
		_text = ReplaceWords(_text, currentWord, replacementWord, isMatchCase, delim);
	}

	static string RemovePunctuations(string text)
	{
		string newText = "";

		for (short i = 0; i < text.length(); i++)
			if (!ispunct(text[i]))
				newText += text[i];

		return newText;
	}

	void RemovePunctuations()
	{
		_text = RemovePunctuations(_text);
	}
};