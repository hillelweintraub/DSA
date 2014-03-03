//Hillel Weintraub, DSA2 Programming assignment#3

//This is the definition of the graph class

#ifndef _GRAPH_H
#define _GRAPH_H
#include "heap.h"
#include <list>
#include <vector>
#include <string>
#include <climits>
#include <fstream>
#include <iostream>
using namespace std;

class graph{
private:
	struct node { // An inner class within graph
		string id; // The id of this node
		long dist; // distance from the specified start node
		node * prev; // previous node in the path
		
		struct edge { // An inner class within node
			long cost; // cost to get to the adjacent node
			node *dest; // the adjacent node
		};

		list<edge> adjlist;

		node(const string &nid,node * nprev = NULL){ id=nid;prev=nprev;} //constructor
	};

	list<node *> nodeList; //list of nodes in the graph
	hashTable *nodeTable;  //hashtable for quick access to the nodes

	//private member functions:

	//creates a node with the given string id and
	//adds it to the nodeList and nodeTable
	node *addNode(const string &id); 

	//checks if a node with the given id is 
	//already in the graph, and if so, returns true
	bool containsNode(const string &id);

	//returns a string listing the path from the start node
	//to the specified node
	string printpath(node * np);
public:

	//public member functions:

	//constructor- sets the size of nodeTable 
	graph(int size);

	//adds the source and destination nodes to the graph if not already 
	//in it, and updates the adjacency list of the source node 
	void addEdge(const string &sourceid, long cost, const string &destid);

	//applies Dijkstra's algorithm to the graph  to find the shortest path from every 
	//node in the graph to the specified node
	void doDijkstra(const string &s);

	//prompts the user to enter the name of an output file and 
	//writes the paths computed by Dijkstra's algorithm to the file
	void printpaths(const string &s);

	//returns true if a node with the given id is contained in the graph
	bool isNode(const string &s);
	
};

#endif //_GRAPH_H