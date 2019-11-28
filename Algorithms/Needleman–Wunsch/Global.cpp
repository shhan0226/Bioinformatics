#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <iostream>
#include <map>

#define MAX 512;
using namespace std;


void main()
{
	map<int, int> table;
	map<int, int>::iterator pos;

	char *X;
	X = malloc(MAX*sizeof(char));
	char *Y;
	Y = (char*)malloc(sizeof(char)*MAX);

	cout <<"input string no.1 \n";
	cin >> X;
	cout <<"input string no.2 \n";
	cin >> Y;
/*
	for(que_pos = que.begin(); que_pos !=que.end(); ++que_pos)
	{
		cluster = v.find(que_pos->vertex);
		if(cluster != v.end())	cout<<cluster_num[v[que_pos->vertex]]+1<<endl;
	}
	
*/
	

	
}
