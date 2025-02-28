#pragma once

#include <iostream>

#include "Selectors.h"
#include "Attributes.h"

class Section
{
	friend class Block;
	friend class MainList;

public:
	Selectors selectors;
	Attributes attributes;
	bool is_empty=false;
};

