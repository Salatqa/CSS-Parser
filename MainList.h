#pragma once

#include <iostream>

#include "Block.h"
#include "Section.h"

class MainList
{
public:
	List<Block> main_list;

	void AddBlock(Block& block);
	void FillBlock(Section& section);
	bool CheckSectionExisting(unsigned long long index);
	unsigned long long GetFreeBlockNumber();
	Section& GetSectionByNumber(unsigned long long index);
	void ReturnNumberOfSelectorsOfGivenSection(unsigned long long index);
	void ReturnNumberOfAttributesOfGivenSection(unsigned long long index);
	void JSelectorInISection(unsigned long long index, unsigned long long j);
	void NAttributeInISection(unsigned long long index, String name);
	void AttributeN(String name);
	void SelectorZ(String name);
	void AttributeNValueforSelectorZ(String name_of_selector, String name_of_attribute);
	void DeleteISection(unsigned long long i_number, bool print);
	void DeleteNAttribute(unsigned long long i_number, String name);
	unsigned long long CountSections();
};