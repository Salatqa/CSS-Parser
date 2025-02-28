#pragma once
#include "String.h"
#include "MainList.h"

class CommandsHandling
{
public:
	void static HandleCommands(String commands[], MainList &list);
};

