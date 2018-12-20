//Code by Vincent Yu
//Created on 2018-07-08
//Value Oriented Array data structure

#include "Random.h"	
#include <exception>
#pragma once

template <class T>
class VOArray
{
public:
	VOArray();

	void Insert(T n);
	bool Remove(T n);
	T Search(T n);
	void Traverse(void(*f)(T));
	T* RandomElement(unsigned int);
	int ElementCount();

	~VOArray();
private:

	int elementCount;
	int maxElements;

	T * arr;

};


//Implementation

//Initialize the array
template <class T>
VOArray<T>::VOArray()
{
	maxElements = 1;
	const int max = maxElements;

	elementCount = 0;
	arr = new T[max];

}

//Destroy the array
template <class T>
VOArray<T>::~VOArray()
{
	delete[] arr;
}

//Insert an element
//Pre-condition: Element must be of type T
//Post-condition: Element is inserted in sorted order
template <class T>
void VOArray<T>::Insert(T n) {

	//If the number of elements reached max of array then extend the array by 2.
	if (elementCount == maxElements) {

		maxElements *= 2;
		const int max = maxElements;
		
		//Create new type T and add to end of list
		T *temp = new T[max];
		for (int i = 0; i < elementCount; i++) {
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;

		//Sort the new element
		arr[elementCount] = n;
		for (int i = elementCount; i > 0; i--) {
			if (arr[i] < arr[i - 1]) {
				T temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
			}
			else {
				break;
			}
		}

		elementCount++;

	}
	else {

		//Add to end of array and sort the new element.
		arr[elementCount] = n;
		for (int i = elementCount; i > 0; i--) {
			if (arr[i] < arr[i - 1]) {
				T temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
			}
			else {
				break;
			}
		}

		elementCount++;
	}

}

//Remove an element target from an array
//Find the element and remove
//Pre-condition: Element must be of type T
//Post-condition: Returns false if element is not removed, true if it is removed.
template <class T>
bool VOArray<T>::Remove(T n) {

	bool ret = true;

	//Find the element
	int k = -1;
	for (int i = 0; i < elementCount; i++) {
		if (arr[i] == n) {
			k = i;
			break;
		}
		
	}

	//If it is not found, then return false
	if (k == -1) {
		ret = false;
	}
	//Else return true, and shift the elements to the left.
	else {
		
		for (int i = k; i < elementCount - 1; i++) {
			arr[i] = arr[i + 1];
		}

		elementCount--;
		
	}

	return ret;

}

//Searches and returns an element in the array
//Uses binary search to search for the element.
//Pre-condition: Element must be of type T
//Post-condition: Element n must be returned from the list, else if its not found, then throw an exception
template <class T>
T VOArray<T>::Search(T n) {

	int a = 0;
	int b = elementCount;
	int i = (a + b) / 2;

	//Binary search
	while (arr[i] != n && i != a && i != b) {

		if (arr[i] > n) {
			b = i;
			i = (a + b) / 2;
		}
		else if (arr[i] < n) {
			a = i;
			i = (a + b) / 2;
		}

	}

	//Found the element
	if (arr[i] == n) {
		return arr[i];
	}
	//Didn't find the element

	throw "Element cannot be found in VOArray";
	

}

//Traverse through the whole array and call function on each element of the array.
//Pre-condition: Function passed in must take in one T parameter, and void function.
//Post-condition: Call function on every node on array.
template <class T>
void VOArray<T>::Traverse(void (*f)(T)) {

	//Traverse through the array
	for (int i = 0; i < elementCount; i++) {
		(*f)(arr[i]);
	}

}

//Returns a random element from the array
template <class T>
T* VOArray<T>::RandomElement(unsigned int t) {

	if (elementCount < 1) {
		return NULL;
	}

	Random r = Random(t);
	return &arr[r.RandInt(0, elementCount - 1)];

}

template <class T>
int VOArray<T>::ElementCount() {
	return elementCount;
}