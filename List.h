#pragma once

#include <iostream>
#include "Node.h"
#include "String.h"


template <typename T>
class List
{
private:
	Node<T>* first, * last;
	unsigned long long counter=0;

public:
	List();

	unsigned long long GetLenght() const;

	void DecreaseLenght();

	Node<T>* GetNode(unsigned long long index);

	void AddNode(T content);

	void RemoveNode(unsigned long long index);

	Node<T>* Find(String name);

	bool Exists(String name) const;

	bool EmptyListCheck() const;

	unsigned long long Count(String name) const;

	void DeleteList();

	~List();
};


template <typename T> //konstruktor
List<T>::List() 
{ 
	first = last = nullptr;
	counter = 0;
}

template <typename T> //zwraca nam ilosc elementow
unsigned long long List<T>::GetLenght() const
{
	return counter;
}

template <typename T> //zmniejsza liczbê elementów (gdy dodawany jest selektor globalny)
void List<T>::DecreaseLenght()
{
	 counter--;
}

template <typename T> //zwraca element listy o podanym indeksie
Node<T>* List<T>::GetNode(unsigned long long index)
{
	if (index < 1 || index > counter || counter ==0) return nullptr;  
	else if (index == 1) return first;
	else if (index == counter) return last;
	else
	{
		Node<T>* node = first;
		for (int i = 1; i < index; i++)
		{
			node = node->next;
		}
		return node;
	}
}

template <typename T> //dodaje element na koncu listy
void List<T>::AddNode(T content)
{
	Node<T>* node = new Node<T>;

	node->data = content;

	if (last == nullptr)
	{
		first = last = node;
	}
	
	else 
	{
		node->prev = last;
		last->next = node;
		node->next = nullptr;
		last=node;
	}
	
	counter++;
}

template <typename T> //usuwa element o wybranej pozycji
void List<T>::RemoveNode(unsigned long long index)
{
	if (index < 1 || counter == 0 || index > counter) return;

	Node<T>* node = GetNode(index);

	if (node == nullptr) return;

	if (counter == 1)
	{
		first = last = nullptr;
		counter = 0;
		return;
	}

	if (node == first)
	{
		first = first->next;
		first->prev = nullptr;
	}

	else if (node == last)
	{
		last = last->prev;
		last->next = nullptr;
	}

	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	counter--;
	delete node;
}

template <typename T> // znajduje element o danej nazwie i zwraca go
Node<T>* List<T>::Find(String name)
{
	Node<T>* node = first;

	for (int i = 0; i < counter; i++)
	{
		if (node->data == name)
		{
			return node;
		}

		if (i != counter - 1) node = node->next;
	}

	return nullptr;
}

template <typename T> //sprawdza czy istenieje element o danej nazwie 
bool List<T>::Exists(String name) const
{
	Node<T>* node = first;

	for (int i = 1; i <= counter; i++)
	{
		if (node->data == name)
		{
			return true;
		}
		if(i!=counter) node = node->next;
	}

	return false;
}

template <typename T> //liczy elementy o danej nazwie
unsigned long long List<T>::Count(String name) const
{
	unsigned long long count = 0;

	Node<T>* node = first;

	for (int i = 0; i < counter; i++)
	{
		if (node->data == name)
		{
			count++;
		}
		
		if(node!=last) node = node->next;
	}

	return count;
}

template <typename T> //sprawdzanie czy lista nie jest pusta
bool List<T>::EmptyListCheck() const
{
	if (counter == 0) return true;
	else return false;
}

template <typename T> //usuwanie listy
void List<T>::DeleteList()
{
	unsigned long long n = counter;
	for (int i = 1; i <= n; i++)
	{
		RemoveNode(1);
	}
}

template <typename T> //usuwanie listy
List<T>::~List()
{
	DeleteList();
}


//Podczas implementowania klasy List inspirowa³am siê slajdami z wyk³adu z przedmiotu "Algorytmy i Struktury Danych" oraz artyku³em "A linear doubly linked list. An example of a template class" ze strony bestprog.net