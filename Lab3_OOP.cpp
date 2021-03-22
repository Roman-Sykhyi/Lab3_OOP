#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <Windows.h>

using namespace std;

class CharSet
{
public:
	char* str;
	int strLength;

	CharSet()
	{
		str = new char[1];
		strLength = 0;
	}

	CharSet(const CharSet& charset)
	{
		SetString(charset.str);
	}

	CharSet(const char* str)
	{
		SetString(str);
	}
	~CharSet()
	{
		delete[] str;
	}

	void SetString(const char* str)
	{
		strLength = strlen(str);
		this->str = new char[strLength + 1];
		strcpy(this->str, str);
	}

	char* GetString()
	{
		return str;
	}

	void Print()
	{
		cout << str << endl;
	}

	bool IsEqualTo(const char* strToCompare)
	{
		return strcmp(str, strToCompare);
	}

	bool IsGreaterThan(const char* strToCompare)
	{
		return strLength > strlen(strToCompare);
	}

	friend ostream& operator << (ostream& output, const CharSet& charset)
	{
		output << charset.str;
		return output;
	}

	friend istream& operator >> (istream& input, const CharSet& charset)
	{
		input >> charset.str;
		return input;
	}

	bool operator <= (CharSet charset)
	{
		const char* ukr_alphabet = "абвгґдеєжзиіїйклмнопрстуфхцшщьюяАБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦШЩЬЮЯ";
		int alphabet_size = 65;

		char* str1 = str;
		char* str2 = charset.str;

		while (*str1 != '\0' || *str2 != '\0')
		{
			if (*str1 == *str2)
			{
				str1++;
				str2++;
				continue;
			}

			int i, j;
			for (i = 0; i < alphabet_size; i++)
			{
				if (*str1 == ukr_alphabet[i])
					break;
			}
			for (j = 0; j < alphabet_size; j++)
			{
				if (*str2 == ukr_alphabet[j])
					break;
			}

			if (i >= j)
				return true;
			else
				return false;
		}
	}

	void operator - (char ch)
	{
		char* result = str;
		char* sentence = str;

		while (*sentence != '\0')
		{
			if (*sentence == ch)
			{
				sentence++;
				continue;
			}

			*result++ = *sentence++;
		}

		*result = '\0';
	}
};

void Sort(CharSet charSets[], int count);
void PrintAll(CharSet charSets[], int count);
void RemoveCharFromCharSets(CharSet charSets[], int count, char ch);
bool IsInAlphabeticalOrder(CharSet charSets[], int count);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CharSet charSets[] =
	{
		CharSet("Яюєї"),
		CharSet("Аббвгд"),
		CharSet("Іб"),
		CharSet("Іа"),
		CharSet("Абвгд")
	};

	int arrsize = sizeof(charSets) / sizeof(CharSet);

	PrintAll(charSets, arrsize);
	Sort(charSets, arrsize);
	puts("");
	PrintAll(charSets, arrsize);

	RemoveCharFromCharSets(charSets, arrsize, 'І');
	puts("");
	PrintAll(charSets, arrsize);

	if (IsInAlphabeticalOrder(charSets, arrsize))
		cout << "Рядки залишились впорядкованими" << endl;
	else
		cout << "Рядки більше не впорядковані" << endl;

	system("pause");
}

void Sort(CharSet arr[], int count)
{
	CharSet temp;
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (arr[i] <= arr[j])
			{
				temp.SetString(arr[i].str);
				arr[i].SetString(arr[j].str);
				arr[j].SetString(temp.str);
			}
		}
	}
}

void PrintAll(CharSet charSets[], int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << charSets[i] << endl;
	}
}

void RemoveCharFromCharSets(CharSet charSets[], int count, char ch)
{
	for (int i = 0; i < count; i++)
	{
		charSets[i] - ch;
	}
}

bool IsInAlphabeticalOrder(CharSet charSets[], int count)
{
	bool flag = true;
	for (int i = 0; i < count - 1; i++)
	{
		if (charSets[i] <= charSets[i + 1])
			flag = false;
	}
	return flag;
}