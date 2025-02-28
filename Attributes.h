#pragma once

#include <iostream>

#include "List.h"

class Attributes
{
	friend class Section;
	friend class Block;
	friend class MainList;

public:
	struct attribute_struct
	{
		String Name;
		String Value;
	};
	List<attribute_struct> list_of_attributes;

	void AddAttribute(String name, String value);
	String static GetName(Node<attribute_struct>* node);
	String static GetValue(Node<attribute_struct>* node);
	void AddOrChangeAttribute(String name, String change);
};

