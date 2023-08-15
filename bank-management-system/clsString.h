#pragma once

#include <iostream>
#include <vector>

class clsString
{
private:
	std::string _Value;

public:

	clsString()
	{
		_Value = "";
	}

	clsString(std::string Value)
	{
		_Value = Value;
	}

	void SetValue(std::string Value) {
		_Value = Value;
	}

	std::string GetValue() {
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) std::string Value;

	static size_t Length(std::string S1)
	{
		return S1.length();
	};

	size_t Length()
	{
		return _Value.length();
	};

	static short CountWords(std::string S1)
	{
		std::string delim = " "; // delimiter
		short Counter = 0;
		size_t pos = 0;
		std::string sWord; // define a string variable

		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				Counter++;
			}

			//erase() until positon and move to next word.
			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			Counter++; // it counts the last word of the string.
		}

		return Counter;
	}

	short CountWords()
	{
		return CountWords(_Value);
	};

	static std::string  UpperFirstLetterOfEachWord(std::string S1)
	{
		bool isFirstLetter = true;

		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = toupper(S1[i]);
			}

			isFirstLetter = (S1[i] == ' ' ? true : false);
		}

		return S1;
	}

	void  UpperFirstLetterOfEachWord()
	{
		// no need to return value , this function will directly update the object value
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static std::string  LowerFirstLetterOfEachWord(std::string S1)
	{
		bool isFirstLetter = true;

		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = tolower(S1[i]);
			}

			isFirstLetter = (S1[i] == ' ' ? true : false);
		}

		return S1;
	}

	void  LowerFirstLetterOfEachWord()
	{
		// no need to return value , this function will directly update the object value
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static std::string  UpperAllString(std::string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}
		return S1;
	}

	void  UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	static std::string  LowerAllString(std::string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}

	void  LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char  InvertLetterCase(char char1)
	{
		return isupper(char1) ? tolower(char1) : toupper(char1);
	}

	static std::string  InvertAllLettersCase(std::string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = InvertLetterCase(S1[i]);
		}
		return S1;
	}

	void  InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };

	static short CountLetters(std::string S1, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		if (WhatToCount == enWhatToCount::All)
		{
			return S1.length();
		}

		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
				Counter++;

			if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
				Counter++;
		}

		return Counter;
	}

	static short  CountCapitalLetters(std::string S1)
	{
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (isupper(S1[i]))
				Counter++;
		}

		return Counter;
	}

	short  CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static short  CountSmallLetters(std::string S1)
	{
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (islower(S1[i]))
				Counter++;
		}

		return Counter;
	}

	short  CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static short  CountSpecificLetter(std::string S1, char Letter, bool MatchCase = true)
	{
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (MatchCase)
			{
				if (S1[i] == Letter)
					Counter++;
			}
			else
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}
		}

		return Counter;
	}

	short  CountSpecificLetter(char Letter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char Ch1)
	{
		Ch1 = tolower(Ch1);

		return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
	}

	static short  CountVowels(std::string S1)
	{
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (IsVowel(S1[i]))
				Counter++;
		}

		return Counter;
	}

	short  CountVowels()
	{
		return CountVowels(_Value);
	}

	static std::vector<std::string> Split(std::string S1, std::string Delim)
	{
		std::vector<std::string> vString;

		size_t pos = 0;
		std::string sWord; // define a string variable

		// use find() function to get the position of the delimiters
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			// if (sWord != "")
			// {
			vString.push_back(sWord);
			//}

			S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
		}

		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}

		return vString;
	}

	std::vector<std::string> Split(std::string Delim)
	{
		return Split(_Value, Delim);
	}

	static std::string TrimLeft(std::string S1)
	{
		for (size_t i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - i);
			}
		}
		return "";
	}

	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static std::string TrimRight(std::string S1)
	{
		for (size_t i = S1.length() - 1; i >= 0; i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i + 1);
			}
		}
		return "";
	}

	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static std::string Trim(std::string S1)
	{
		return (TrimLeft(TrimRight(S1)));
	}

	void Trim()
	{
		_Value = Trim(_Value);
	}

	static std::string JoinString(std::vector<std::string> vString, std::string Delim)
	{
		std::string S1 = "";

		for (std::string& s : vString)
		{
			S1 = S1 + s + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());
	}

	static std::string JoinString(std::string arrString[], short Length, std::string Delim)
	{
		std::string S1 = "";

		for (short i = 0; i < Length; i++)
		{
			S1 = S1 + arrString[i] + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());
	}

	static std::string ReverseWordsInString(std::string S1)
	{
		std::vector<std::string> vString;
		std::string S2 = "";

		vString = Split(S1, " ");

		// declare iterator
		std::vector<std::string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;

			S2 += *iter + " ";
		}

		S2 = S2.substr(0, S2.length() - 1); //remove last space.

		return S2;
	}

	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}

	static std::string ReplaceWord(std::string S1, std::string StringToReplace, std::string sRepalceTo, bool MatchCase = true)
	{
		std::vector<std::string> vString = Split(S1, " ");

		for (std::string& s : vString)
		{
			if (MatchCase)
			{
				if (s == StringToReplace)
				{
					s = sRepalceTo;
				}
			}
			else
			{
				if (LowerAllString(s) == LowerAllString(StringToReplace))
				{
					s = sRepalceTo;
				}
			}
		}

		return JoinString(vString, " ");
	}

	std::string ReplaceWord(std::string StringToReplace, std::string sRepalceTo)
	{
		return ReplaceWord(_Value, StringToReplace, sRepalceTo);
	}

	static std::string RemovePunctuations(std::string S1)
	{
		std::string S2 = "";

		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}

		return S2;
	}

	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}
};
