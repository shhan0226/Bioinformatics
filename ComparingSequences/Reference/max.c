#include <stdio.h>
#include <stdlib.h>

int max (int *i, int *j){
	
	if (*i > *j) return *i;
	else return *j;
}

void main(){
	int i = 1;
	int j = 2;
	printf("\n%d``",max(&i, &j) );

}
