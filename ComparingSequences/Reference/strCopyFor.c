#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX 5000

char* instr(char* p, int all, int t){
	int i;
	char* pt;
	pt = (char*)malloc( sizeof(char)* MAX );

	for(i =0; i<=t; i++){
		pt[i] = p[i];
	}
	for(i = t+1; i<=all; i++){
		pt[i+1] = p[i];
	}
	pt[t+1] = ' ';
	return pt;
	

}

void main(){
	int i,max;
	char* p ="ABEd df g";
	printf("[%s]", p);
	max = strlen(p);
	printf("=>[%s]", instr(p,max,2));

}
