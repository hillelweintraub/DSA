//Hillel Weintraub, DSA2 Programming assignment#2

//This is the definition of the heap class

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include "hash.h"
using namespace std;


class heap{

private:
	struct node { // An inner class within heap
		string id; // The id of this node
		int key; // The key of this node
		void *pData; // A pointer to the actual data
  };

private:
	int capacity; // The capacity of the heap
	int currSize; // The current size of the heap
	vector<node> data; // The actual binary heap
	hashTable *mapping; // maps ids to node pointers

	//Private member functions of the heap:

	//
	//percolate up- Heapefies the heap by pecolating the node at the
	//given position up to its final resting position
	//
	void percolateUp(int posCur);

	//
	//percolateDown- Heapefies the heap by pecolating the node at the
	//given position down to its final resting position
	//
	void percolateDown(int posCur);

	//
	//getPos- Gets the position of the given node in the heap array
	//
	int getPos(node *pn);



public:

	//
	// heap-The constructor allocates space for the nodes of the heap
	// and the mapping (hash table) based on the specified capacity
	//
	heap(int capacity);

	//
	//insert- Inserts a new node into the binary heap
	//
	//inserts a node with the specified id string, key,
	// and optionally a pointer. The key is used
	// to determine the final position of the new node.
	//
	//Returns:
	//	0 on success
	//	1 if the heap is already filled to capacity
	//	2 if a node with the given id already exists (but the heap
	// 	  is not filled to capacity)
	//
	int insert(const string &id, int key, void *pv = NULL);

	//
	//setKey - set the key of the specified node to the specified value
	//
	// Returns:
	//	0 on success
	//	1 if a node with the given id does not exist
	//
	int setKey(const string &id, int key);

	//
	//deleteMin - return the data associated with the smallest key
	//			  and delete that node from the binary heap
	//
	//if pId is supplied (i.e. it's not NULL), write to that address
	//the id ofthe node being deleted. If pKey is supplied, write to 
	//that address the key of the node being deleted. If ppData
	// is supplied, write to that address the associated void pointer.
	//
	//Returns:
	//	0 on success
	//	1 if the heap is empty
	//
	int deleteMin(string *pId = NULL, int *pKey = NULL, void *ppData = NULL);

	//
	//remove - delete the node with the specified id from the binary heap
	//
	//If pKey is supplied, write to that address the key of the node
	//being deleted. If ppData is supplied, write to that address the
	//associated void pointer.
	//
	//Returns :
	//	0 on success
	//	1 if a node with the given id does not exist
	//
	int remove(const string &id, int *pKey = NULL, void *ppData = NULL);
};

#endif //_HEAP_H