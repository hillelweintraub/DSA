//Hillel Weintraub, DSA2 Programming assignment#2

//The implementation of the heap class

#include "heap.h"
#include <climits>

	heap::heap(int capacity){
		data.resize(capacity+1);
		mapping = new hashTable(capacity*2);
		this->capacity = capacity;
		currSize=0;

	}

	int heap::insert(const string &id, int key, void *pv){

		if (currSize==capacity)
			return 1;
		else if(mapping->contains(id))
			return 2;
		else{
			currSize++;
			data[currSize].key=key;
			data[currSize].id=id;
			data[currSize].pData=pv;
			mapping->insert(data[currSize].id,&data[currSize]);
			percolateUp(currSize);
			return 0;
		}
	}

	int heap::setKey(const string &id, int key){
		bool b;
		node *pn = static_cast<node *> (mapping->getPointer(id, &b));
		if(!b)
			return 1;
		int pos=getPos(pn);
		int tKey=data[pos].key;
		data[pos].key=key;
		if(data[pos].key>tKey)
			percolateDown(pos);
		if(data[pos].key<tKey)
			percolateUp(pos);
		return 0;
	}
	int heap::deleteMin(string *pId, int *pKey, void *ppData){
		if(currSize==0)
			return 1;
		if(pId)
			*pId=data[1].id;
		if(pKey)
			*pKey=data[1].key;
		if(ppData)
			*(static_cast<void **> (ppData)) = data[1].pData;
		mapping->remove(data[1].id);
		data[1]=data[currSize];
		mapping->setPointer(data[1].id,&data[1]);
		currSize--;
		percolateDown(1);
		return 0;
	}
	int heap::remove(const string &id, int *pKey, void *ppData){
		bool b;
		node *pn = static_cast<node *> (mapping->getPointer(id, &b));
		if(!b)
			return 1;
		int pos=getPos(pn);
		if(pKey)
			*pKey=data[pos].key;
		if(ppData)
			*(static_cast<void **> (ppData)) = data[pos].pData;
		int tKey=data[pos].key;
		mapping->remove(data[pos].id);
		data[pos]=data[currSize];
		mapping->setPointer(data[pos].id,&data[pos]);
		currSize--;
		if(data[pos].key>tKey)
			percolateDown(pos);
		if(data[pos].key<tKey)
			percolateUp(pos);
		return 0;		
	}

	void heap::percolateUp(int posCur){

		int tKey=data[posCur].key;
		string tId=data[posCur].id;
		void *tPv=data[posCur].pData;
		int hole;
		for (hole = posCur; hole > 1 && tKey < data[hole/2].key; hole/=2){
			data[hole]=data[hole/2];
			mapping->setPointer(data[hole].id,&data[hole]);
		}
		data[hole].key=tKey;
		data[hole].id=tId;
		data[hole].pData=tPv;
		mapping->setPointer(data[hole].id,&data[hole]);
	}

	void heap::percolateDown(int hole){

		int tKey=data[hole].key;
		string tId=data[hole].id;
		void *tPv=data[hole].pData;
		int child;

		for (;hole*2<=currSize; hole=child){
			child=hole*2;
			if (child!=currSize && data[child+1].key < data[child].key)
				child++;
			if(data[child].key<tKey){
				data[hole]=data[child];
				mapping->setPointer(data[hole].id,&data[hole]);
			}
			else
				break;
		}
		data[hole].key=tKey;
		data[hole].id=tId;
		data[hole].pData=tPv;
		mapping->setPointer(data[hole].id,&data[hole]);
	}
	int heap::getPos(node *pn){
		int pos = pn - &data[0];
		return pos;
	}
