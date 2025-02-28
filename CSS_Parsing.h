#pragma once

#include <iostream>
#include "String.h"
#include "MainList.h"
#include "CommandsHandling.h"

class CSS_Parsing
{
public:
	MainList parsing_list;
	Block parsing_block;
	Section parsing_section;
	Selectors parsing_selectors;
	Attributes parsing_attributes;

	bool commands = false;
	bool will_be_attributes=false;
	bool selectors_reading = false;
	bool attributes_reading = false;
	bool attribute_name = false;
	bool atribute_value = false;
	bool commands_reading = false;

	int commands_block = 0;
	String commands_tab[3] = { NULL, NULL, NULL };

	char c;
	char buff[1024] = {};
	char buff2[1024] = {};
	String temp=nullptr;
	String temp2=nullptr;
	
	void Parse();
};

