#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>



void main(){
	int i,max;
	char* p ="ABEd df g";
	printf("%s\n",p);
	char* pt;
	
	max= strlen(p);
	printf("%d\n",max);
	
	pt= (char*)malloc(sizeof(char)*max);

	for(i=0; i<max; i++)
	{
		memcpy(&pt[i], &p[max-1-i], sizeof(char));
	}
	pt[max]='\0';

	printf("=>%s",pt);

}
