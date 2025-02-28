#pragma once

#include <iostream>

#define L 8

#include "Section.h"

class Block
{
	friend class Section;
private:
	Section sections[L] = {};
	bool taken[L] = {};
	int block_fullness = 0;
	bool is_full = false;
public:
	void AddSection(Section& new_section);
	void DeleteSection(Section& section);
	Section& ReturnSection(int index);
	int ReturnBlockFullness() const;
	bool RemoveNodeIsNecessary() const;
	bool IsFull() const;
};