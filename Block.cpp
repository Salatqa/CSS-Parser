#include "Block.h"

void Block::AddSection(Section& new_section)
{
	for (int i = 0; i < L; i++)
	{
		if (taken[i] == false)
		{
			sections[i] = new_section;
			taken[i] = true;
			if (i+1 == L) is_full = true;
			else is_full = false;
			break;
		}
	}
	block_fullness++;
}

void Block::DeleteSection(Section & section) 
{
	section.selectors.list_of_selectors.DeleteList();
	section.attributes.list_of_attributes.DeleteList();
	section.is_empty = true;
	block_fullness--;
}

Section& Block::ReturnSection(int index)
{
	int number = 0;
	int counter = 0;
	for (int i = 0; i < L; i++)
	{
		if (sections[i].is_empty == false)
		{
			counter++;
		}
		if (counter == index)
		{
			number = i;
			break;
		}
	}
	return sections[number]; 
}

int Block::ReturnBlockFullness() const
{
	return block_fullness;
}

bool Block::RemoveNodeIsNecessary() const
{
	if (block_fullness == 0) return true;
	else return false;
}

bool Block::IsFull() const
{
	if (is_full == true) return true;
	else return false;
}