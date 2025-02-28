#include "Attributes.h"


void Attributes::AddAttribute(String name, String value)
{
	attribute_struct attr;
	attr.Name = name;
	attr.Value = value;

	list_of_attributes.AddNode(attr);
}

String Attributes::GetName(Node<attribute_struct>* node)
{
	attribute_struct str = node->data;
	return str.Name;
}

String Attributes::GetValue(Node<attribute_struct>* node)
{
	attribute_struct str = node->data;
	return str.Value;
}

void Attributes::AddOrChangeAttribute(String name, String change)
{
	for (int i = 1; i <= list_of_attributes.GetLenght(); i++)
	{
		Node<attribute_struct>* node = list_of_attributes.GetNode(i);
		attribute_struct & str = node->data;
		if (name == str.Name)
		{
			str.Value = change;
			return;
		}
	}
	AddAttribute(name, change);
}
