// CS271 - Project 4
// Profess: Jessen Havill 
// Students: Uyen (Grace) Le, Tung Luu 
// October 22th, 2021

// pq.cpp

// These 3 constructors just call the corresponding MinHeap constructors.  That's all.
/*==========================================================
MinPriorityQueue();                     // default constructor
Precondition: None
Postcondition: An empty min priority queue of capacity 0
============================================================*/
template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue() // : MinHeap<KeyType>()
{
	MinHeap<KeyType> pq(0);  	// call MinHeap constructors for a new heap of capacity 0
}

/*==========================================================
MinPriorityQueue(int n);            	// construct an empty MPQ with capacity n
Precondition: Given capacity n 
Postcondition: An empty min priority queue of capacity n
============================================================*/
template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(int n) : MinHeap<KeyType>(n)
{
	MinHeap<KeyType> pq(n); // call MinHeap constructors for a new heap of capacity n
}

/*==========================================================
MinPriorityQueue(const MinPriorityQueue<KeyType>& pq);      // copy constructor
Precondition: Given a min priority queue to copy
Postcondition: A min priority queue copied from the MPQ given
============================================================*/
template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(const MinPriorityQueue<KeyType>& pq) : MinHeap<KeyType>(pq)
{
	MinHeap<KeyType> queue(pq); 	// call MinHeap copy constructor
}

/*==========================================================
minimum()				// return the minimum element
Precondition: Given a min priority queue 
Postcondition: The minimum element is returned
============================================================*/
template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::minimum() const
{
	if (empty()) 			// check if the MPQ is empty 
		throw EmptyError(); 	// throw exception 
	return A[0]; 
}

/*==========================================================
extractMin()				// delete the minimum element and return it
Precondition: Given a min priority queue 
Postcondition: The minimum element is deleted from the MPQ and returned
============================================================*/
template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::extractMin()
{
	if (empty()) 			// check if the MPQ is empty 
		throw EmptyError(); 	// throw exception 
	KeyType* min = A[0]; 		// store the minimum element
	A[0] = A[heapSize - 1]; 	// delete the minimum element and replace it with the last element currently in MPQ
	heapSize--; 			// decrement heapSize
	heapify(0); 			// call heapify since the subtrees are valid heaps
	return min; 
}

/*==========================================================
decreaseKey(int index, KeyType* key)	// decrease the value of an element
Precondition: Given the index of the element and the key to decrease 
Postcondition: The element at index is decreased by key 
============================================================*/
template <class KeyType>
void MinPriorityQueue<KeyType>::decreaseKey(int index, KeyType* key) 
{
	if (*key > *(A[index]))		// check if key is greater than the current element 
		throw KeyError();	// throw exception 
	A[index] = key; 		// set value of A[index] to key
	while ((index > 0) && *(A[index]) < *(A[parent(index)])) 
					// while not reaching root and current element is smaller than its parent
	{
		swap(index, parent(index)); 	// swap current element with its parent
		index = parent(index);
	}
}

/*==========================================================
insert(KeyType* key)			// insert a new element
Precondition: Given an element to insert
Postcondition: The element is inserted
============================================================*/
template <class KeyType> 
void MinPriorityQueue<KeyType>::insert(KeyType* key)
{
	if (heapSize == capacity)	// check if the MPQ is full
		throw FullError(); 	// throw full exception 
	heapSize++; 			// increment heapSize
	A[heapSize - 1] = key; 		// insert key to last element
	decreaseKey(heapSize - 1, key); // swap key with its parent until find the correct positon
}

/*==========================================================
empty()				// return whether the MPQ is empty
Precondition: Given a min priority queue 
Postcondition: True if the MPQ is empty, Else otherwise
============================================================*/
template <class KeyType> 
bool MinPriorityQueue<KeyType>::empty() const 
{
	if (heapSize == 0)	// if the MPQ is empty
		return 1;
	return 0;		// if the MPQ is not empty 
}

/*==========================================================
length()			// return the number of keys
Precondition: Given a min priority queue 
Postcondition: The size of the MPQ is returned
============================================================*/
template <class KeyType> 
int MinPriorityQueue<KeyType>::length() const
{
	return heapSize; 				
}

/*==========================================================
toString()									// return a string representation of the MPQ
Precondition: Given a min priority queue 
Postcondition: The string representation of the MPQ is returned
============================================================*/
template <class KeyType>
std::string MinPriorityQueue<KeyType>::toString() const
{
	std::stringstream ss;
	
	if (heapSize == 0)
	{
		ss << "[ ]";
	}
	else
	{
		ss << "[";
		for (int index = 0; index < heapSize - 1; index++)
			ss << *(A[index]) << ", ";
		ss << *(A[heapSize - 1]) << "]";
	}
	return ss.str();
}

template <class KeyType>
std::ostream& operator<<(std::ostream& stream, const MinPriorityQueue<KeyType>& pq)
{
	stream << pq.toString();
	
	return stream;
}
