#include "MainList.h"
#include "Selectors.h"

void MainList::AddBlock(Block& block)
{
	main_list.AddNode(block);
}

void MainList::FillBlock(Section& section)
{
	Node<Block>* node = main_list.GetNode(GetFreeBlockNumber());
	Block &block = node->data;
	block.AddSection(section);
}

unsigned long long MainList::GetFreeBlockNumber()
{
	Node<Block>* node = main_list.GetNode(main_list.GetLenght());
	Block& block = node->data;
	if (block.IsFull() == true)
	{
		Block* new_block = new Block; 
		main_list.AddNode(*new_block);
	}
	return main_list.GetLenght();
}

bool MainList::CheckSectionExisting(unsigned long long index)
{
	if (index < 1 || (index >CountSections()) || (main_list.GetLenght() ==0))
	{
		return false;
	}
	else return true;
}

Section& MainList::GetSectionByNumber(unsigned long long index)
{
	Section sect;
	unsigned long long counter = 0;
	Node<Block>* node = main_list.GetNode(1);
	for (int j = 1; j <= main_list.GetLenght(); j++)
	{
		Block& block = node->data;
			
		for (int i = 1; i <= block.ReturnBlockFullness(); i++)
		{

			counter++;

			if (counter == index)
			{
				Section& temp_section = block.ReturnSection(i);
				return temp_section;
			}
		}
		if(node!=main_list.GetNode(main_list.GetLenght())) node = node->next;
	}
	return sect;
}

void MainList::ReturnNumberOfSelectorsOfGivenSection(unsigned long long index)
{
	if (CheckSectionExisting(index) == false) return;
	Section& section = GetSectionByNumber(index);
	std::cout << index <<","<< "S" << "," << "?" << " == " << section.selectors.list_of_selectors.GetLenght() << endl;
}

void MainList::ReturnNumberOfAttributesOfGivenSection(unsigned long long index)
{
	if (CheckSectionExisting(index) == false) return;
	Section& section = GetSectionByNumber(index);
	std::cout << index << "," << "A" << "," << "?" << " == " << section.attributes.list_of_attributes.GetLenght() << endl;
}

void MainList::JSelectorInISection(unsigned long long index, unsigned long long j)
{	
	if (CheckSectionExisting(index) == false) return;
	Section& section = GetSectionByNumber(index);
	if (j > section.selectors.list_of_selectors.GetLenght()) return;
	Node<String>* node = section.selectors.list_of_selectors.GetNode(j);
	if (node->data == "GLOBAL_SELECTOR") return;
	std::cout << index << "," << "S" << "," << j << " == " << node->data << endl;
}

void MainList::NAttributeInISection(unsigned long long index, String name)
{
	if (CheckSectionExisting(index) == false) return;
	Section& section = GetSectionByNumber(index);
	if (section.attributes.list_of_attributes.GetLenght() == 0) return;
	for (int i = 1; i <= section.attributes.list_of_attributes.GetLenght(); i++)
	{
		if (name == section.attributes.GetName(section.attributes.list_of_attributes.GetNode(i)))
		{
			std::cout << index << "," << "A" << "," << name << " == " << section.attributes.GetValue(section.attributes.list_of_attributes.GetNode(i)) << endl;
			break;
		}
	}
	return;
}

void MainList::AttributeN(String name) 
{
	if (main_list.GetLenght() == 0) std::cout << "0" << endl;
	else
	{
		unsigned long long attributes_counter = 0;
		Node<Block>* node = main_list.GetNode(1);
		for (int k = 1; k <= main_list.GetLenght(); k++)
		{
			unsigned long long counter = 0;
			Block& block = node->data;
			counter = block.ReturnBlockFullness();
			for (int j = 1; j <= counter; j++)
			{
				Section& sect = block.ReturnSection(j);
				unsigned long long lenght = 0;
				lenght = sect.attributes.list_of_attributes.GetLenght();
				for (int i = 1; i <= lenght; i++)
				{
					if (name == sect.attributes.GetName(sect.attributes.list_of_attributes.GetNode(i)))
					{
						attributes_counter++;
						break;
					}
				}
			}
			if (node != main_list.GetNode(main_list.GetLenght())) node = node->next;
		}

		std::cout << name << "," << "A" << "," << "?" << " == " << attributes_counter << endl;
	}
}

void MainList::SelectorZ(String name)
{
	if (main_list.GetLenght() == 0) std::cout << name << "," << "S" << "," << "?" << " == " << "0" << endl;
	else if (name == "GLOBAL_SELECTOR") return;
	else
	{
		unsigned long long selectors_counter = 0;
		Node<Block>* node = main_list.GetNode(1);
		for (int i = 1; i <= main_list.GetLenght(); i++)
		{
			int counter = 0;
			Block& block = node->data;
			counter = block.ReturnBlockFullness();
			for (int j = 1; j <= counter; j++)
			{
				Section& sect = block.ReturnSection(j);
				
				if( sect.selectors.list_of_selectors.Exists(name)==true) selectors_counter++;
			}
			if (node != main_list.GetNode(main_list.GetLenght())) node = node->next;
		}

		std::cout << name << "," << "S" << "," << "?" << " == " << selectors_counter << endl;
	}
}

void MainList::AttributeNValueforSelectorZ(String name_of_selector, String name_of_attribute)
{
	if (main_list.GetLenght() == 0) return;
	else
	{
		for (int i = main_list.GetLenght(); i >= 1; i--)
		{
			unsigned long long counter = 0; 
			Node<Block>* node = main_list.GetNode(i);
			Block& block = node->data; 
			counter = block.ReturnBlockFullness();
			for (int j = counter; j >=1; j--)
			{
				Section& sect = block.ReturnSection(j);

				if (sect.selectors.list_of_selectors.Exists(name_of_selector) == true)
				{
					unsigned long long len;
					len = sect.attributes.list_of_attributes.GetLenght();
					for (int z = 1; z <= len; z++)
					{
						if (name_of_attribute == sect.attributes.GetName(sect.attributes.list_of_attributes.GetNode(z)))
						{
							std::cout << name_of_selector << "," << "E" << "," << name_of_attribute << " == " << sect.attributes.GetValue(sect.attributes.list_of_attributes.GetNode(z)) << endl;
							return;
						}
					}
				}
			}
		}
		return;
	}
}

void MainList::DeleteISection(unsigned long long i_number, bool print)
{
	if (CheckSectionExisting(i_number) == false) return;
	unsigned long long counter = 0;
	Node<Block>* node = main_list.GetNode(1);
	for (int j = 1; j <= main_list.GetLenght(); j++)
	{
		Block& block = node->data;

		for (int i = 1; i <= block.ReturnBlockFullness(); i++)
		{
			counter++;
			
			if (counter == i_number)
			{
				Section& temp_section = block.ReturnSection(i);
				block.DeleteSection(temp_section);
				if (block.RemoveNodeIsNecessary() == true && j!=main_list.GetLenght()) main_list.RemoveNode(j);
				if(print == true) std::cout << i_number << "," << "D" << "," << "*" << " == " << "deleted" << endl;
				return;
			}
		}
		if (node != main_list.GetNode(main_list.GetLenght())) node = node->next;
	}
}

void MainList::DeleteNAttribute(unsigned long long i_number, String name)
{
	if (CheckSectionExisting(i_number) == false) return;
	else
	{
		Section& section = GetSectionByNumber(i_number);
		if (section.attributes.list_of_attributes.GetLenght() == 0) return;
		for (int i = 1; i <= section.attributes.list_of_attributes.GetLenght(); i++)
		{
			if (name == section.attributes.GetName(section.attributes.list_of_attributes.GetNode(i)))
			{
				section.attributes.list_of_attributes.RemoveNode(i);
				if (section.attributes.list_of_attributes.GetLenght() == 0) DeleteISection(i_number, false);
				std::cout << i_number << "," << "D" << "," << name << " == " << "deleted" << endl;
				return;
			}
		}
	}
	return;
}

unsigned long long MainList::CountSections()
{
	unsigned long long counter = 0;
	if (main_list.GetLenght() != 0)
	{
		Node<Block>* node = main_list.GetNode(1);
		for (int i = 1; i <= main_list.GetLenght(); i++)
		{
			Block& block = node->data;
			counter += block.ReturnBlockFullness();
			if (node != main_list.GetNode(main_list.GetLenght())) node = node->next;
		}
	}
	return counter;
}