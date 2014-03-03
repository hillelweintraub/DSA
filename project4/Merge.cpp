//Hillel Weintraub, DSA2 Programming assignment#4

//This program takes a list of word triplets and determines
// if the third word in the triplet is a valid merge of the 
// first two words in the triplet.

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;


bool M[1001][1001]; 

int main(int argc, char const *argv[])
{

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

	string s1,s2,merge;
	while(!input.eof()){
		s1="";
		input>>s1>>s2>>merge;
		if(s1=="")
			break;
		int m,n;
		m=s1.length(); n=s2.length();
		if (merge.length()!=m+n)
			output<<"*** NOT A MERGE ***"<<endl;
		else{
			M[0][0]=true;
		
			int i;
			for (i = 1; i <= m; ++i){
				if(merge[i-1]==s1[i-1])
				M[i][0]=true;
				else
					break;
			}
			for (; i <=m; ++i){
				M[i][0]=false;
			}

			for (i = 1; i <= n; ++i){
				if(merge[i-1]==s2[i-1])
					M[0][i]=true;
				else
					break;
			}
			for (; i <= n; ++i){
				M[0][i]=false;
			}

			int j;
			for (i = 1; i <=m; ++i){
				for (j= 1; j <=n; ++j){
					if( (M[i-1][j]==true && merge[i+j-1]==s1[i-1])|| (M[i][j-1]==true && merge[i+j-1]==s2[j-1]) )
						M[i][j]=true;
					else
						M[i][j]=false;
				}
			}

			i--; j--;
			string s="";
			char c;
			if(M[i][j]==true){
				while(i>0 && j>0){
					if(M[i][j-1]==true){
						s=s2[j-1]+s;
						j--;
					}
					else{
						c=toupper(s1[i-1]);
						s= c+s;
						i--;
					}
				}
				if(i==0){
					for(;j>0;--j){
						s=s2[j-1]+s;
					}
				}
				else{
					for(;i>0;--i){
						c=toupper(s1[i-1]);
						s=c+s;
					}
				}
				output<<s<<endl;
			}
			else
				output<<"*** NOT A MERGE ***"<<endl;
		}
	}
	return 0;
}