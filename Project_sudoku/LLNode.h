//Code by Vincent Yu
//Created on 2018-07-08
//Linked list node

#pragma once

#include <iostream>

template <class T>
class LLNode
{
public:
	LLNode(T n);

	T* GetData();

	~LLNode();

	LLNode<T> *next;


private:

	T *data;

};


//Implementation


//Node constructor
//Set data to n, and next to NULL;
template <class T>
LLNode<T>::LLNode(T n)
{
	data = new T;
	*data = n;
	next = NULL;

}

//Destroy the node
template <class T>
LLNode<T>::~LLNode()
{
	delete data;
}

//Return the node data.
template <class T>
T* LLNode<T>::GetData() {
	return data;
}

