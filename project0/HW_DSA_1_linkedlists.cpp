//Hillel Weintraub, DSA Programming assignment#1

//This program manipulates stacks and queues.
//It reads an input file of commands (commands consist of either: create list, push, or pop), processes them, and outputs a corresponding output file.

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <cassert>
using namespace std;



//SimpleList is an abstract base class that provides simple linked list functionality
template <class T>
class SimpleList{
//Node is a private nested class that provides the basic building block for the SimpleList class 
private:
	struct Node{
		T data;
		Node *next;
		Node(const T &d, Node *n=NULL) {data=d; next=n;} //constructor
	};
private:
	Node *head;
	Node *tail;
	string listname;
	int size;
public:
	SimpleList(const string &name = "noname");
	string get_name() const {return listname;} // get the name of the SimpleList
	int get_size() {return size;} // get the size of the SimpleList
	virtual void push(const T &d)=0; //virtual function to be implemented in the derived Stack and Queue classes
	virtual const T pop()=0; //virtual function to be implemented in the derived Stack and Queue classes
protected:
	void push_front(const T &d); 
	void push_back(const T &d); 
	const T pop_front(); 
	
	
};


template <class T> // Stack is a derived class that implements last in first out pushing and popping
class Stack: public SimpleList<T>{
public:
	Stack(const string &name="noname"):SimpleList<T>(name){}
	void push(const T &d);
	const T pop();
};


template <class T> // Queue is a derived class that implements first in first out pushing and popping
class Queue: public SimpleList<T>{
public:
	Queue(const string &name="noname"):SimpleList<T>(name){}
	void push(const T &d);
	const T pop();
};



template <class T> // constructor
SimpleList<T>::SimpleList(const string &name){
	head = NULL;
	tail = NULL;
	size = 0;
	listname = name;
}


template <class T> //Insert element at beginning of list
void SimpleList<T>::push_front(const T &d){
	Node* new_head = new Node(d,head);
	if (size==0){ //for an empty list we adjust the tail pointer as well 
		head = new_head;
		tail=new_head;
	}
	else
		head = new_head;
	size++;
}


template <class T> // Insert element at back of list
void SimpleList<T>::push_back(const T &d){
	Node* new_tail = new Node(d,NULL);
	if (size==0)//for an empty list we adjust the head pointer as well
		head = new_tail;
	else
		tail->next = new_tail;
	tail = new_tail;
	size++;
}


template <class T> //remove and return element from front of list
const T SimpleList<T>::pop_front(){
	assert(head!=NULL);
	Node* old_head = head;
	if (size==1){
		head = NULL;
		tail = NULL;
	}
	else
		head = head->next;
	const T retval = old_head->data;
	delete old_head;
	size--;
	return retval;
}


template <class T> // places an element at the top of the stack
void Stack<T>::push(const T &d){
	return this->push_front(d);
}


template <class T> // remove and return an element from the top of the stack
const T Stack<T>::pop(){
	return this->pop_front();
}


template <class T> // place an element at the bottom of the queue
void Queue<T>::push(const T &d){
	return this->push_back(d);
}
	
	
template <class T> // remove and return an element from the top of the queue
const T Queue<T>::pop(){
	return this->pop_front();
}


template <class T> // a template function used to search through a list of pointers to SimpleList
T find_list(const string &listname, list<T> listSL){
	for(class list<T>::iterator ii = listSL.begin(); ii!=listSL.end(); ii++){
		if( (*ii)->get_name()==listname)
			return *ii;
	}
	return NULL;
}
	
// main takes an input file, parses and processes it, and returns a corresponding output file
main() 
{
	list<SimpleList<int> *> listSLi; //all integer stacks and queues
	list<SimpleList<double> *> listSLd; // all double stacks and queues
	list<SimpleList<string> *> listSLs; // all string stacks and queues
	SimpleList<int> *pSLi;
	SimpleList<double> *pSLd;
	SimpleList<string> *pSLs;

	
	string FilenameInput, FilenameOutput; //variables to get input and output file names
	string action, listname, listtype,val; //variables to store input from the input file
	int ival; //variable used to convert strings to ints
	double dval; //variable used to convert strings to doubles
	cout<<"Enter name of input file: ";
	cin>>FilenameInput;
	cout<<"Enter name of output file: ";
	cin>>FilenameOutput;
	ofstream output;
	ifstream input;
	input.open(FilenameInput.c_str());
	output.open(FilenameOutput.c_str());
	
	
	while (input>>action){ //input>>action returns 0 when EOF is reached
	   if (action=="create"){ //process create commands
			input>>listname>>listtype;
			output<<"PROCESSING COMMAND: "<<action<<" "<<listname<<" "<<listtype<<endl;
			if(listname[0]=='i'){ //list of ints
				if (find_list<SimpleList<int> *>(listname,listSLi)!=NULL)
					output<<"ERROR: This name already exists!"<<endl;
				else{
						if (listtype=="queue"){
							pSLi = new Queue<int>(listname);
							listSLi.push_front(pSLi);
						}
						else{ //listtype==stack
							pSLi = new Stack<int>(listname);
							listSLi.push_front(pSLi);
						}
					}
			}
			else if(listname[0]=='d'){ //list of doubles
				if (find_list<SimpleList<double> *>(listname,listSLd)!=NULL)
						output<<"ERROR: This name already exists!"<<endl;
				else{
					if (listtype=="queue"){
						pSLd = new Queue<double>(listname);
						listSLd.push_front(pSLd);
					}
					else{ //listtype==stack
					pSLd = new Stack<double>(listname);
					listSLd.push_front(pSLd);
					}
				}
			}
			else{ //list of strings
				if (find_list<SimpleList<string> *>(listname,listSLs)!=NULL)
					output<<"ERROR: This name already exists!"<<endl;
				else{
					if (listtype=="queue"){
						pSLs = new Queue<string>(listname);
						listSLs.push_front(pSLs);
					}
					else{ //listtype==stack
						pSLs = new Stack<string>(listname);
						listSLs.push_front(pSLs);
					}
				}
			}
		}
		if (action=="push"){ //process push commands
			input>>listname>>val;
			output<<"PROCESSING COMMAND: "<<action<<" "<<listname<<" "<<val<<endl;
			if(listname[0]=='i'){ //list of ints
				if ( (pSLi=find_list<SimpleList<int> *>(listname,listSLi)) == NULL){
						output<<"ERROR: This name does not exist!"<<endl;
				}
				else{
					stringstream(val)>>ival; //convert string stored in val to int stored in ival
					pSLi->push(ival);
				}
			}
			else if(listname[0]=='d'){ //list of doubles
				if ( (pSLd=find_list<SimpleList<double> *>(listname,listSLd)) == NULL){
						output<<"ERROR: This name does not exist!"<<endl;
				}
				else{
					stringstream(val)>>dval; //convert string stored in val to double stored in dval
					pSLd->push(dval);
				}
			}
			else{ //list of strings
				if ( (pSLs=find_list<SimpleList<string> *>(listname,listSLs)) == NULL){
						output<<"ERROR: This name does not exist!"<<endl;
				}
				else
					pSLs->push(val);
			}
		}
		if (action=="pop"){ //process pop commands
			input>>listname;
			output<<"PROCESSING COMMAND: "<<action<<" "<<listname<<endl;
			if(listname[0]=='i'){ //list of ints
				if ( (pSLi=find_list<SimpleList<int> *>(listname,listSLi)) == NULL){
						output<<"ERROR: This name does not exist!"<<endl;
				}
				else if(pSLi->get_size()==0)
					output<<"ERROR: This list is empty!"<<endl;
				else
					output<<"Value popped: "<<pSLi->pop()<<endl;
			}
			else if(listname[0]=='d'){ //list of doubles
				if ( (pSLd=find_list<SimpleList<double> *>(listname,listSLd)) == NULL){
						output<<"ERROR: This name does not exist!"<<endl;
				}
				else if(pSLd->get_size()==0)
					output<<"ERROR: This list is empty!"<<endl;
				else
					output<<"Value popped: "<<pSLd->pop()<<endl;
			}
			else{ //list of strings
				if ( (pSLs=find_list<SimpleList<string> *>(listname,listSLs)) == NULL){
						output<<"ERROR: This name does not exist!"<<endl;
				}
				else if(pSLs->get_size()==0)
					output<<"ERROR: This list is empty!"<<endl;
				else
					output<<"Value popped: "<<pSLs->pop()<<endl;
			}
		}
	}
	input.close();
	output.close();	
}


