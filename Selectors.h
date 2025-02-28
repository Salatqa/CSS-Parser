#pragma once

#include <iostream>

#include "List.h"

class Selectors
{
	friend class Section;
	friend class Block;
	friend class MainList;
public:
	List<String> list_of_selectors;

	void AddSelector(String name);
};

