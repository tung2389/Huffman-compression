// CS271 - Project 4
// Profess: Jessen Havill 
// Students: Uyen (Grace) Le, Tung Luu 
// October 22th, 2021

// heap.cpp

#include <sstream>
#include "heap.h"

// Implement heap methods here.

/*==========================================================
MinHeap(int n = DEFAULT_SIZE)      //default constructor
Precondition: Must be given a capacity size (n)
Postcondition: An empty heap with capacity of n (1000 (default))
============================================================*/
template <class KeyType>
MinHeap<KeyType>::MinHeap(int n)
{
	A = new KeyType*[n];
	this->heapSize = 0;
	this->capacity = n;
}


/*==========================================================
MinHeap(KeyType initA[], int n)      //construct heap from array
Precondition: Must be given an array and a capacity
Postcondition: A min heap constructed from the array
============================================================*/
template <class KeyType>
MinHeap<KeyType>::MinHeap(KeyType* initA[], int n)
{
  A = new KeyType*[n];
  this->capacity = n;
  this->heapSize = n;
  for (int i=0; i<n; i++)
  {
    this->A[i] = initA[i]; //traverse through initA and copy each element to current heap
  }
  buildHeap();
}


/*==========================================================
MinHeap(const MinHeap<KeyType>& heap);  // copy constructor
Precondition: Must be given a heap
Postcondition: A min heap copied from the given heap
============================================================*/
template <class KeyType>
MinHeap<KeyType>::MinHeap(const MinHeap<KeyType>& heap)
{
  copy(heap); //call copy method which copies each element of heap parameter to current heap
}


/*==========================================================
~MinHeap();                             // destructor
Precondition: Given a heap
Postcondition: The heap is deallocated
============================================================*/
template <class KeyType>
MinHeap<KeyType>::~MinHeap()
{
	this->destroy(); //call destroy method that deallocates current object
}


/*==========================================================
heapSort(KeyType sorted[]);  // heapsort, return result in sorted
Precondition: Must be given a heap to be sorted
Postcondition: The heap is sorted in ascending order and the result is stored in sorted
============================================================*/
template <class KeyType>
void MinHeap<KeyType>::heapSort(KeyType* sorted[])
{
  // One by one extract an element from heap
	int n = this->heapSize;
  for (int i = n-1; i > 0; i--)
  {
    // Swap current root and end
    swap(0, i);
	  this->heapSize -= 1;
    // call max heapify on the reduced heap
    heapify(0);
  }
	this->heapSize = n;
	for (int i = 0; i < this->heapSize; i++){
		sorted[n-i-1] = this->A[i]; //reverse max heap to get min heap
	}
}


/*==========================================================
operator = (const MinHeap<KeyType>& heap);  // assignment operator
Precondition: Must be given a heap to be copied
Postcondition: Assign the heap to a new heap
============================================================*/
template <class KeyType>
MinHeap<KeyType>& MinHeap<KeyType>::operator=(const MinHeap<KeyType>& heap)
{
  this->copy(); //call copy method that copies each element of the heap parameter to current heap
  return *this;
}


/*==========================================================
heapify(int index);          // heapify subheap rooted at index
Precondition: The subtrees are valid heaps. 
Postcondition: The min heap property is maintained by calling the heapifyR
============================================================*/
template <class KeyType>
void MinHeap<KeyType>::heapify(int index)
{
  heapifyR(index); //calls recursive heapify
}


/*==========================================================
heapifyR(int index);          // heapify subheap rooted at index
Precondition: The subtrees are valid heaps. 
Postcondition: The min heap property is maintained by recursively calling heapifyR
============================================================*/
template <class KeyType>
void MinHeap<KeyType>::heapifyR(int index)
{
  int smallest = index;
  int left = leftChild(index);
  int right = rightChild(index);

  if (left < heapSize  && *(A[left]) < *(A[smallest]))
  {
    smallest = left;
  }
  if (right < heapSize && *(A[right]) < *(A[smallest]))
  {
    smallest = right; //switch smallest to right if A[right] is the smaller of the two children
  }

  if (smallest != index)
  {
    swap(smallest, index); //swap current index with the index of the smaller child
    heapify(smallest); //recursively call heapify on lower children
  }
}


/*==========================================================
heapify(int index);          // heapify subheap rooted at index
Precondition: The subtrees are valid heaps. 
Postcondition: The min heap property is maintained by iteratively heapifying
============================================================*/
template <class KeyType>
void MinHeap<KeyType>::heapifyI(int index)
{
	int smallest = index;
  int left = leftChild(index);
  int right = rightChild(index);

  if (left < heapSize  && *(A[left]) < *(A[smallest]))
  {
    smallest = left; //intitialize smallest
  }
  if (right < heapSize && *(A[right]) < *(A[smallest]))
  {
    smallest = right; //switch smallest to right if A[right] is the smaller of the two children
  }

  while(smallest != index) //iterative call
  {
    swap(smallest, index);
    index = smallest;
    left = leftChild(index);
    right = rightChild(index);

    if (left < heapSize  && *(A[left]) < *(A[smallest]))
    {
      smallest = left;
    }
    if (right < heapSize && *(A[right]) < *(A[smallest]))
    {
      smallest = right;
    }
  }
}


/*==========================================================
buildHeap();                 // build heap
Precondition: Used on an array
Postcondition: Build a new heap from the array
============================================================*/
template <class KeyType>
void MinHeap<KeyType>::buildHeap()
{
  for (int i = heapSize/2; i>=0; i--)
  {
    heapify(i); //call heapify on the first half of the array
  }
}


/*==========================================================
swap(int index1, int index2);        // swap elements in A
Precondition: Must be given two indices of the array
Postcondition: The values of the two indices are exchanged
============================================================*/
template <class KeyType>
void MinHeap<KeyType>::swap(int index1, int index2)
{
	KeyType* temp = this->A[index1]; //temporary variable to store A[index1]
	this->A[index1] = this->A[index2];
	this->A[index2] = temp;
}


/*==========================================================
copy(const MinHeap<KeyType>& heap);  // copy heap to this heap
Precondition: Must be given a heap to copy
Postcondition: Copy the heap to this heap
============================================================*/
template <class KeyType>
void MinHeap<KeyType>::copy(const MinHeap<KeyType>& heap)
{
	this->heapSize = heap.heapSize;
	this->capacity = heap.capacity;
	A = new KeyType*[this->capacity];
	for (int i = 0; i < heap.heapSize; i++){
		this->A[i] = heap.A[i]; //traverses through the heap parameter and copies each of the element to the current heap
	}
}


/*==========================================================
destroy();                           // deallocate heap
Precondition: Given a heap
Postcondition: The heap is deallocated
============================================================*/
template <class KeyType>
void MinHeap<KeyType>::destroy()
{
	delete []A; //deallocate object
}


// Use the following toString() for testing purposes.

template <class KeyType>
std::string MinHeap<KeyType>::toString() const
{
	std::stringstream ss;

	if (capacity == 0)
		ss << "[ ]";
	else
	{
		ss << "[";
		if (heapSize > 0)
		{
			for (int index = 0; index < heapSize - 1; index++)
				ss << *(A[index]) << ", ";
			ss << *(A[heapSize - 1]);
		}
		ss << " | ";
		if (capacity > heapSize)
		{
			for (int index = heapSize; index < capacity - 1; index++)
				ss << *(A[index]) << ", ";
			ss << *(A[capacity - 1]);
		}
		ss << "]";
	}
	return ss.str();
}

template <class KeyType>
std::ostream& operator<<(std::ostream& stream, const MinHeap<KeyType>& heap)
{
	return stream << heap.toString();
}
