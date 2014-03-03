//Hillel Weintraub, DSA2 Programming assignment#3

//This program loads a graph from an input file and applies Dijkstra's algorithm
// to it. The resulting shortest paths to each node in the graph are written to an 
// output file.

#include "graph.h"


void loadGraph(graph &g) {
	string filename;
	cout << "Enter name of graph file: ";
	cin >> filename;

	ifstream input(filename.c_str());
	if (!input) {
    	cerr << "Error: could not open " << filename << endl;
    	exit(1);
	}

	string source,dest;
	long cost;
	while(!input.eof()){
		input>>source>>dest>>cost;
		g.addEdge(source,cost,dest);
	}

	input.close();
}

int main(int argc, char const *argv[])
{
	graph g(0);
	string s;
	loadGraph(g);
	bool valid=false;
	while(!valid){
		cout<<"Enter a valid vertex id for the starting vertex: ";
		cin>>s;
		if(g.isNode(s))
			valid=true;
		else
			cout<<"Vertex id was not valid"<<endl;
	}

	clock_t t1 = clock();
  	g.doDijkstra(s);
  	clock_t t2 = clock();
 	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff<< endl;
	g.printpaths(s);
}