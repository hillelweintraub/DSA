//Hillel Weintraub, DSA2 Programming assignment#3

//The implementation of the graph class

#include "graph.h"


graph::graph(int size){
	nodeTable=new hashTable(size);
}

bool graph::containsNode(const string &id){
	return nodeTable->contains(id);
}

graph::node * graph::addNode(const string &id){
		node *vertex = new node(id);
		nodeList.push_back(vertex);
		//cout<<nodeList.size()<<endl;
		nodeTable->insert(id,vertex);
		return vertex;
}

void graph::addEdge(const string &sourceid, long cost, const string &destid){
	node *dest, *source;
	node::edge e;
	//cout<<nodeList.size()<<endl;
	if(!containsNode(sourceid)){
		source=addNode(sourceid);
	}
	else{
		source= static_cast<node *> (nodeTable->getPointer(sourceid));
	}
	
	if(!containsNode(destid)){
		dest=addNode(destid);
	}
	else
		dest= static_cast<node *> (nodeTable->getPointer(destid));

	e.cost=cost;
	e.dest=dest;
	(source->adjlist).push_front(e);
}

void graph::doDijkstra(const string &s){
	heap nodeHeap(nodeList.size());
	list<node *>::iterator np;
	for( np = nodeList.begin(); np!=nodeList.end(); np++){
		(*np)->dist=LONG_MAX;
		nodeHeap.insert((*np)->id,(*np)->dist,*np);
	}

	node * start = static_cast<node *> (nodeTable->getPointer(s));
	nodeHeap.setKey(start->id,start->dist=0);

	node *v;
	while(!nodeHeap.deleteMin(NULL,NULL,&v)){
		for( list<node::edge>::iterator ep = (v->adjlist).begin(); ep!=(v->adjlist).end(); ep++){
			long d;
			if( (d=v->dist+(*ep).cost) <((*ep).dest)->dist && v->dist!=LONG_MAX){
				nodeHeap.setKey(((*ep).dest)->id,((*ep).dest)->dist=d);
				((*ep).dest)->prev=v;
			}
		}
	}
}

string graph::printpath(node * np){//fix this
	string s="";
	if(np->prev !=NULL){
		s=printpath(np->prev)+", ";
	}
	s+=np->id;
	return s;
}

void graph::printpaths(const string &s){
	string filename;
	cout << "Enter name of output file: ";
	cin >> filename;

	ofstream output(filename.c_str());
	if (!output) {
		cerr << "Error: could not open " << filename << endl;
		exit(1);
	}
	
	for( list<node *>::iterator np = nodeList.begin(); np!=nodeList.end(); np++){
		output<<(*np)->id<<": ";
		if((*np)->prev == NULL && (*np)->id!=s){
			output<<"NO PATH"<<endl;
		}
		else{
			output<<(*np)->dist<<" "<<"["<<printpath(*np)<<"]"<<endl;
		}
	}
	output.close();
}

bool graph::isNode(const string &s){
	return containsNode(s);
}

