//Code by Vincent Yu
//Created on 2018-07-08
//Linked list data structure

#include "Random.h"

#pragma once

#include "LLNode.h"
#include <iostream>
using namespace std;

template <class T>
class LinkedList
{
public:
	LinkedList();

	void Insert(T n);
	bool Remove(T n);
	T* Search(T n);
	void Traverse( void(*f)(T) );
	T* RandomElement(unsigned int t);

	~LinkedList();
private:

	int elementCount;
	LLNode<T> *head;
	LLNode<T> *tail;

};




//Implementation


//Initialize empty linked list
//Head and tail is null
template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;

	head = tail;
	elementCount = 0;
}


//Destroy the linked list.
//Traverse through each node and delete it.
template <class T>
LinkedList<T>::~LinkedList()
{

	LLNode<T> *temp;

	//Traverse and delete
	while (head != NULL) {
		temp = head;
		head = head->next;
		delete temp;
	}

}

//Insert element into linked list.
//Inserts a new element:
//Access to elements must be through the head
//tail must be the last element
//Pre-Condition: Element must be of type T
//Post condition: New element must be inserted to end of linked list.
template <class T>
void LinkedList<T>::Insert(T n) {

	//Different cases depending on how many nodes in a linked list.

	if (head == NULL) {
		head = new LLNode<T>(n);
		tail = head;
	}
	else if (tail == head) {
		tail = new LLNode<T>(n);
		head->next = tail;
	}
	else {

		LLNode<T> *newNode = new LLNode<T>(n);
		tail->next = newNode;

		tail = tail->next;

	}

	elementCount++;

}

//Remove an element from the linked list
//Pre-condition: Element must be of type T
//Post-condition: Removes the first element with target data.
template <class T>
bool LinkedList<T>::Remove(T n) {

	bool ret = true;
	LLNode<T> *temp = head;

	//If temp is null, the element cannot be found
	if (temp == NULL) {
		ret = false;
	}
	//If first element is equal to target
	else if (temp != NULL && *(temp->GetData()) == n) {

		//If there are more than one element in the linked list, set the head to next element
		if (head->next != NULL) {
			LLNode<T> *toDelete = head;
			head = head->next;
			delete toDelete;
		}
		//Else this is the only node, delete the head.
		else {
			delete head;
			head = NULL;
			tail = NULL;
		}

		elementCount--;

	}
	//If there are more than one elements in the linked list.
	else {

		//While temp next is not null, and it is not equal to data
		//Set temp to temp next
		while (temp->next != NULL && *(temp->next->GetData()) != n) {
			temp = temp->next;
		}

		//If we reached the end of linked list
		if (temp->next == NULL) {
			ret = false;
		}
		//Else, we found the target
		else {

			//Delete the target
			LLNode<T> *toDelete = temp->next;
			if (temp->next == tail) {
				tail = temp;
				tail->next = NULL;
			}
			else {
				temp->next = temp->next->next;
			}
			delete toDelete;

			elementCount--;
		}
	}

	return ret;

}

//Search for an element
//Pre-condition: Element must be of type T
//Post-condition: Element will be returned
//If it is not found, throw an exception.
template <class T>
T* LinkedList<T>::Search(T n) {

	LLNode<T> *temp = head;
	T* ret = NULL;

	//Traverse through all nodes and find the target
	while (temp != NULL) {

		//If target is found
		if (*(temp->GetData()) == n) {
			ret = temp->GetData();
			break;
		}
		temp = temp->next;
	}

	//If target is not found then throw exception
	if (temp == NULL) {
		throw "Cannot find target in Linked List";
	}

	return ret;

}

//Traverse through the whole linked list
//Takes in a function to call upon each node
//Pre-condition: Function passed in must take in one int parameter, and void function.
//Post-condition: Call function on every node on linked list.
template <class T>
void LinkedList<T>::Traverse( void (*f)(T) ) {

	LLNode<T> *temp = head;

	//Traverse through the whole linked list
	while (temp != NULL) {
		(*f)(*(temp->GetData()));
		temp = temp->next;
	}

}

template <class T>
T* LinkedList<T>::RandomElement(unsigned int t) {

	if (elementCount < 1) {
		return NULL;
	}

	Random r = Random(t);
	int toret = r.RandInt(0, elementCount - 1);

	LLNode<T> *temp = head;
	for (int i = 0; i < toret + 1; i++) {
		temp = temp->next;
	}
	return temp;

}
