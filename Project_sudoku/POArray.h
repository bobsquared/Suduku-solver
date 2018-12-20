//Code by Vincent Yu
//Created on 2018-07-08
//Position Oriented Array data structure

#include "Random.h"
#pragma once
template <class T>
class POArray
{
public:
	POArray();

	void Insert(T n);
	bool Remove(int n);
	T* Search(int n);
	void Traverse(void(*f)(T));
	int ElementCount();
	void Sort();

	T* RandomElement(unsigned int);

	~POArray();
private:

	int elementCount;
	int maxElements;
	void qsort(int first, int last);
	int partition(int first, int last);

	T * arr;

};


//Implementation


//Initialize the array
template <class T>
POArray<T>::POArray()
{
	maxElements = 1;
	const int max = maxElements;

	elementCount = 0;
	arr = new T[max];
}


//Destroy the array
template <class T>
POArray<T>::~POArray()
{
	delete[] arr;
}


//Insert an element
//Pre-condition: Element must be of type T
//Post-condition: Element is inserted into end of array
template <class T>
void POArray<T>::Insert(T n) {

	//If the number of elements reached max of array then extend the array by 2 times.
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

		elementCount++;

	}
	else {

		//Add to end of array and sort the new element.
		arr[elementCount] = n;

		elementCount++;
	}

}

//Remove an element target from an array
//Find the element from index n and remove
//Pre-condition: Element must be of type T
//Post-condition: Returns false if element is not removed, true if it is removed.
template <class T>
bool POArray<T>::Remove(int n) {

	bool ret = true;

	if (n < 0 || n >= elementCount) {
		ret = false;
	}
	else {

		//Else return true, and shift the elements to the left.

		for (int i = n; i < elementCount - 1; i++) {
			arr[i] = arr[i + 1];
		}

		elementCount--;

	}


	return ret;

}

//Searches and returns an element in the array
//Uses linear search to search for the element.
//Pre-condition: Element must be of type T
//Post-condition: Element n must be returned from the list, else if its not found, then throw an exception
template <class T>
T* POArray<T>::Search(int n) {

	if (n < 0 || n >= elementCount) {
		throw "Parameter outside of range";
	}

	//Find element in the array
	return &arr[n];

	//Didn't find the element
	throw "Element cannot be found in VOArray";

}

//Traverse through the whole array and call function on each element of the array.
//Pre-condition: Function passed in must take in one T parameter, and void function.
//Post-condition: Call function on every node on array.
template <class T>
void POArray<T>::Traverse(void(*f)(T)) {

	//Traverse through the array
	for (int i = 0; i < elementCount; i++) {
		(*f)(arr[i]);
	}

}

//Sorts the array
template <class T>
void POArray<T>::Sort() {

	qsort(0, elementCount-1);

}


//Partition of quick sort
template <class T>
int POArray<T>::partition(int first, int last) {

	int start = first;
	T part = arr[first];
	
	while (first+1 <= last) {

		if (arr[first+1] < part) {
			first++;
		}
		else {
			
			T temp = arr[first+1];
			arr[first+1] = arr[last];
			arr[last] = temp;
			last--;
		}

	}

	
	T temp = arr[last];
	arr[last] = part;
	arr[start] = temp;
	
	


	return last;

}

//use quick sort to sort the array
template <class T>
void POArray<T>::qsort(int first, int last) {

	if (first >= last) {

		return;

	}

	int part = partition(first, last);
	qsort(first, part-1);
	qsort(part+1, last);

	return;

}

//Returns a random element from the array
template <class T>
T* POArray<T>::RandomElement(unsigned int t) {

	if (elementCount < 1) {
		return NULL;
	}

	Random r = Random(t);
	return &arr[r.RandInt(0, elementCount - 1)];

}


template <class T>
int POArray<T>::ElementCount() {

	return elementCount;
}