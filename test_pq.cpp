#include <iostream>
#include <string>
#include <assert.h>
#include "pq.h"
using namespace std;

int main() 
{
	int myNum[10] = {1, 5, 9, 7, 3, 6, 4, 8, 2, 1};
	
  MinPriorityQueue<int> pq(10); // Default constructor 

  /*=======================================================
  Test case: Empty MinPriorityQueue
  Input: an empty pq
  Expected output:  pq.empty() should return True. 
                    pq.length() should return 0. 
                    Calling minimum() and extractMin() should result in empty exception. 
  =======================================================*/
  assert(pq.empty() == 1); 
  assert(pq.length() == 0); 

  try 
  { 
    int *min = pq.minimum(); 
  }
  catch(...)
  {
    cout << "Minimum Method: Empty Error Caught." << endl;
  }

  try 
  {
    int *min = pq.extractMin();
  }
  catch(...)
  {
    cout << "Extract Min Method: Empty Error Caught." << endl; 
  }
  
  /*=======================================================
  Test case: Insert new elements to an empty pq. 
  Input: insert the first 5 elements in {1, 5, 9, 7, 3, 6, 4, 8, 2, 1} to pq. 
  Expected output: [1, 3, 9, 7, 5]
  =======================================================*/
  for (int i = 0; i<5; i++)
  {
    pq.insert(&myNum[i]); 
  }
  assert(pq.toString() == "[1, 3, 9, 7, 5]");
  assert(pq.empty() == 0); 
  assert(pq.length() == 5); 

  /*=======================================================
  Test case: Insert new elements to an existing pq. 
  Input: insert the last 5 elements in {1, 5, 9, 7, 3, 6, 4, 8, 2, 1 to pq. 
  Expected output: [1, 1, 4, 3, 2, 9, 6, 8, 7, 5]
  =======================================================*/
  for (int i = 5; i<10; i++)
  {
    pq.insert(&myNum[i]); 
  }
  assert(pq.toString() == "[1, 1, 4, 3, 2, 9, 6, 8, 7, 5]");
  assert(pq.empty() == 0); 
  assert(pq.length() == 10); 

  /*=======================================================
  Test case: Copy constructor. 
  Input: copy pq to a new MinPriorityQueue. 
  Expected output: [1, 1, 4, 3, 2, 9, 6, 8, 7, 5]
  =======================================================*/
  MinPriorityQueue<int> copyPQ(pq); 
  assert(copyPQ.toString() == "[1, 1, 4, 3, 2, 9, 6, 8, 7, 5]");
  assert(copyPQ.empty() == 0); 
  assert(copyPQ.length() == 10); 

  /*=======================================================
  Test case: Insert new elements to a full pq. 
  Input: a new element and a full pq. 
  Expected output: throw Full Error exception.
  =======================================================*/
  int extra = 10; 
  try 
  {
    pq.insert(&extra); 
  }
  catch(...)
  {
    cout << "Insert Method: Full Error Caught." << endl;
  }

  /*=======================================================
  Test case: Decrease a element by a larger amount. 
  Input: a populated pq, an index for the element, and a key larger than the element. 
  Expected output: throw Key Error exception.
  =======================================================*/
  int decrease = 5;
  try
  {
    pq.decreaseKey(4, &decrease); 
  }
  catch(...)
  {
    cout << "Decrease Key Method: Key Error Caught." << endl;
  }

  /*=======================================================
  Test case: Decrease a element by a smaller amount. 
  Input: a populated pq, an index for the element (5), and a key (3) smaller than the element. 
  Expected output: .
  =======================================================*/
  int decrease2 = 2; 
  pq.decreaseKey(8, &decrease2); 
  assert(pq.toString() == "[1, 1, 4, 2, 2, 9, 6, 8, 3, 5]"); 

  return 0; 
}