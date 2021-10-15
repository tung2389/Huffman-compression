// CS271 - Project 4
// Profess: Jessen Havill 
// Students: Uyen (Grace) Le, Tung Luu 
// October 22th, 2021

// pq.cpp

// These 3 constructors just call the corresponding MinHeap constructors.  That's all.
template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue() // : MinHeap<KeyType>()
{
	MinHeap<KeyType> pq(0);  
}

template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(int n) : MinHeap<KeyType>(n)
{
	MinHeap<KeyType> pq(n);
}

template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(const MinPriorityQueue<KeyType>& pq) : MinHeap<KeyType>(pq)
{
	MinHeap<KeyType> queue(pq);
}

template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::minimum() const
{
	if (empty())
		throw EmptyError(); 
	return A[0]; 
}

template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::extractMin()
{
	if (empty())
		throw EmptyError(); 
	KeyType* min = A[0]; 
	A[0] = A[heapSize - 1]; 
	heapSize--; 
	heapify(0); 
	return min; 
}

template <class KeyType>
void MinPriorityQueue<KeyType>::decreaseKey(int index, KeyType* key) 
{
	if (*key > *(A[index]))
		throw KeyError();
	A[index] = key; 
	while ((index > 0) && *(A[index]) < *(A[parent(index)]))
	{
		swap(index, parent(index)); 
		index = parent(index);
	}
}

template <class KeyType> 
void MinPriorityQueue<KeyType>::insert(KeyType* key)
{
	if (heapSize == capacity)
		throw FullError(); 
	heapSize++; 
	A[heapSize - 1] = key; 
	decreaseKey(heapSize - 1, key); 
}

template <class KeyType> 
bool MinPriorityQueue<KeyType>::empty() const 
{
	if (heapSize == 0)
		return 1;
	return 0;
}

template <class KeyType> 
int MinPriorityQueue<KeyType>::length() const
{
	return heapSize; 
}

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