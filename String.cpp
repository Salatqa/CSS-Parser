#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <string.h>
#include <cmath>


String::String() : string(nullptr) 
{
	string = new char[1];
	string[0] = '\0';
}

String::String(const char* value)
{
	if (value == nullptr) 
	{
		string = new char[1];
		string[0] = '\0';
	}

	else 
	{
		string = new char[strlen(value) + 1];
		strcpy(string, value);
		string[strlen(value)] = '\0';
	}
}

String::String(const String& source)
{
	string = new char[strlen(source.string) + 1];
	strcpy(string, source.string);
	string[strlen(source.string)] = '\0';
}

std::ostream& operator<<(std::ostream& ostr, const String& String)
{
	ostr << String.string;

	return ostr;
}

String& String::operator=(const String& source)
{
	if (this != &source) 
	{
		delete[] string;
		string = new char[strlen(source.string) + 1];
		strcpy(string, source.string);
		string[strlen(source.string)] = '\0';
	}
	return *this;
}

String& String::operator+=(const char& source)
{
	int new_size = strlen(string) + 1;
	char* temp = new char[new_size + 1] {};
	strcpy(temp, string);

	temp[new_size - 1] = source;
	temp[new_size] = '\0'; 
	string = temp;
	return *this;
}

bool String::operator==(const String& other) const
{
	if (&other == nullptr || &string == nullptr)
	{
		return false;
	}

	if (strlen(string) != strlen(other.string)) 
	{
		return false;
	}

	for (size_t i = 0; i < strlen(string); i++) 
	{
		if (string[i] != other.string[i]) {
			return false;
		}
	}
	return true;
}

bool String::ISNumber()
{
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] < 48 || string[i]>57) return false;
	}
	return true;
}

unsigned long long String::StringToNumber()
{
	unsigned long long number = 0;
	double n = 0;
	for (int i = (strlen(string)-1); i >=0; i--)
	{
		number = number + (string[i] - '0')* pow(10, n);
		n++;
	}
	return number;
}

String::~String() 
{ 
	if(string!=nullptr) delete[] string; 
}


//Czêœæ funkcjonalnoœci klasy String zosta³a zaimplementowana na podstawie artyku³u "How to create a custom String class in C++ with basic functionalities" ze strony geeksforgeeks.org