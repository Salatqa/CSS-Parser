#pragma once

#include <iostream>

template <typename T>
class Node
{
public:
	T data;
	Node* prev, * next;
};