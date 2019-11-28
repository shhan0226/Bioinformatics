#include <iostream>
#include <stdio.h>
#include <string.h>

#define MAX 512
using namespace std;

int main(int argc, char* argv[]){


	char X[MAX];
	char Y[MAX];

	cout<<"input string no.1\n";
	cin>>X;
	cout<<"input string no.1\n";
	cin>>Y;

	int x;
	int y;

	x = strlen(X);
	y = strlen(Y);
	

	cout<<X<<" "<<x<<endl;
	cout<<Y<<" "<<y<<endl;

	return 0;

}
