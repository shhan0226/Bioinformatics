#include <iostream>
#include <stdio.h>
#include <string.h> // strlen
#include <stdlib.h> //malloc
#include <map>
#include <string>


#define MAX 512
#define MAT 10
#define MIS -5
#define IND -5
using namespace std;
int table[MAX][MAX];
char *R_X, *R_Y, *RE;


int max(int *i, int *j)
{
	if(*i>*j) return *i;
	else	return *j;
}


int dynamic(string X, string Y, int x, int y)
{
	int i, j, init, match_max, mis_max;

	init =0;
	for(i =0; i<x+1; i++)
	{
		table[i][0] = init-i;
	}

	init =0;
	for(j =0; j<y+1; j++)
	{
		table[0][j] = init-j;
	}


	for(i = 1; i<x+1; i++)
	{
		for(j= 1; j<y+1; j++)
		{
			match_max = 0;
			if(X[i-1] == Y[j-1])
			{
				match_max = table[i-1][j-1]+MAT;
			}
			else
			{
				mis_max = max( table[i-1][j]+IND, table[i][j-1]+IND );
				mis_max = max( table[i-1][j-1]+MIS, mis_max);
				match_max = max( match_max, mis_max);
			}

			table[i][j] = match_max;
		}
	}

	return 0;	
}

void print_dy( string X, string Y, int x, int y)
{
	int i,j;
	i=j=0;

	printf(" \t\t");

	for( i=0; i<y+1; i++)
	{
		printf("%c\t", Y[i]);
	}	
	printf("\n");

	for( i=0; i<x+1; i++)
	{
		if(i == 0)
		{	
			printf(" \t");
		}
		else
		{
			printf("%c\t", X[i-1]);
		}
		for(j=0; j<y+1; j++)
		{
			printf("%d\t", table[i][j]);
		}
	
		printf("\n");
		
	}
}

void Back_Tra( string X, string Y, int x, int y, string Res_x, string Res_y, string Result)
{
	if(x==0 || y==0)
	{
		R_X = (char*)(Res_x.c_str());	
		R_Y = (char*)(Res_y.c_str());	
		RE = (char*)(Result.c_str());	
		return;
	}

	if( table[x][y] > table[x][y-1] && table[x][y] > table[x-1][y] && table[x][y] > table[x-1][y-1] )
	{
		Res_x+=X[x-1];
		Res_y+=Y[y-1];
		Result+="|";
		Back_Tra(X, Y, x-1, y-1, Res_x, Res_y, Result);
	}
	else if( table[x][y] > table[x-1][y] && table[x][y] == table[x][y-1] )
	{
		Result+="-";
		Res_x+="-";
		Res_y+=Y[y-1];
		Back_Tra(X, Y, x, y-1, Res_x, Res_y, Result);
	}
	else
	{
		Result+="-";
		Res_x+=X[x-1];
		Res_y+="-";
		Back_Tra(X, Y, x-1, y, Res_x, Res_y, Result);
	}
}

void conver_sort()
{
	int i, j, k, l;
	i = strlen(R_X);
	j = strlen(RE);
	k = strlen(R_Y);

	cout<<endl<<"??"<<endl<<R_X<<endl<<RE<<endl<<R_Y<<endl;
	cout<<"tis "+i<<endl<<"tis "+j<<endl<<"tis "+k<<endl;
/*
	cout<<endl;
	for(l=i-1; l>-1;l--)
	{	
		cout<<R_X[l];
	}
	cout<<endl;
	for(l=j-1; l>-1;j--)
	{	
		cout<<RE[l];
	}
	cout<<endl;
	for(l=k-1; l>-1;l--)
	{	
		cout<<R_Y[l];
	}
	cout<<endl;
*/	
}
int main(int argc, char* argv[]){

	
	char X[MAX];
	char Y[MAX];
	
	string str_X, str_Y, Res_x, Res_y, Result;
	Res_x=Res_y=Result="";


	cout<<"input string no.1\n";
	cin>>X;
	str_X = X;

	cout<<"input string no.1\n";
	cin>>Y;
	str_Y = Y;

	int x;
	int y;

	x = strlen(X);
	y = strlen(Y);

	cout<<X<<" "<<x<<endl;
	cout<<Y<<" "<<y<<endl;


	dynamic( str_X, str_Y, x, y);
	print_dy( str_X, str_Y, x,y);
	Back_Tra( str_X, str_Y, x, y, Res_x, Res_y, Result);
	conver_sort();
		



	return 0;

}
