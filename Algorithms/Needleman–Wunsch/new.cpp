#include <iostream>
#include <stdio.h>
#include <string.h>

#define MAX 512
using namespace std;

int main(int argc, char* argv[]){


	string X = "as df asdf dd";
	cout<< "word :"+ X<<endl;
 	cout<< "count:" <<X.length()<<endl; 
	cout<< "empty: " <<X.find(" ")<< endl << X.length() - X.find(" ") <<endl;
	return 0;

}
