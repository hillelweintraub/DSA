//Hillel Weintraub, DSA2 Programming assignment#1

//This program loads a dictionary from an input file into
//a hashtable. It then spellchecks a second input file and outputs the results to a file.


#include "hash.h"
#include <fstream>
#include <ctime>
#include <cctype>




// Load the dictionary from a specified input file into a hashTable
void loadDict(hashTable &HT) {
  string filename;
  cout << "Enter name of dictionary: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  
  string word="";
  char c;
  while(!input.eof()){ 
  	input.get(c);
  	if(c!='\n'){
  		word+=tolower(c);//make all words lowercase
  	}
  	else{
  		if(HT.insert(word)==2){
  			cerr << "Memory allocation fail!" << endl;
  			exit(1);
  		}
  		word="";	
  	}
  	
  }
  input.close();
}

//returns 1 if c is a valid character. 0 otherwise
bool isvalid(char c){
	return isalnum(c)||c=='-'||c=='\'';
}

//spellchecks an input file using the supplied hashtable
// and outputs the results to a file
void spellcheck(hashTable &HT) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  string word="";
  char c;
  int length=0; 
  int line=1;
  bool ignore=false;
  while(!input.eof()){
  	input.get(c);
  	if(isvalid(c)){
  		if(length<20){
  			word+=tolower(c);//make all words lowercase
  		}
  		length++;
  		if(isdigit(c)){
  			ignore=true;
  		}
  	}
  	else{
  		if(!ignore && length>20){
  			output<<"Long word at line "<<line<<", starts: "<<word<<endl;
  		}
  		else if(!ignore && !HT.contains(word) && length>0){
  			output<<"Unknown word at line "<<line<<": "<<word<<endl;
  		}
  		word="";
  		length=0;
  		ignore=false;
  		if(c=='\n')
  			line++;
  	}
  }

  //checking the last word, since last line of file doesn't end with a newline
  if(!ignore && length>20){
  	output<<"Long word at line "<<line<<", starts: "<<word<<endl;
  }
  else if(!ignore && !HT.contains(word) && length>0)
  	output<<"Unknown word at line "<<line<<": "<<word<<endl;
  input.close();
  output.close();
}


  




// The main function calls routines to load the dictionary, 
// spellcheck the file, and output the results. 
// The loading and the spellchecking are timed according to CPU time.
int main(int argc, char const *argv[]){
	hashTable HT(100000);

	clock_t t1 = clock();
  	loadDict(HT);
  	clock_t t2 = clock();
 	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  	cout << "Total time (in seconds) to load dictionary: " << timeDiff<< endl;

  	t1 = clock();
  	spellcheck(HT);
  	t2 = clock();
 	timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  	cout << "Total time (in seconds) to check document: " << timeDiff<< endl;
}


