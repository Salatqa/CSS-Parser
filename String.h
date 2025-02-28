#pragma once
#include <iostream>

using namespace std;

class String
{
public:
	char* string;

	String();
	String(const char* value);
	String(const String& source);

	friend std::ostream& operator<<(std::ostream&, const String&);
	String& operator=(const String& source);	
	String& operator+=(const char& source);
	bool operator==(const String& other)const;

	bool ISNumber();
	unsigned long long int StringToNumber();

	~String();
};