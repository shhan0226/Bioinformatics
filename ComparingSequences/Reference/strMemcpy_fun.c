#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

char* Restr(char *p)
{
	char* pt;
	int i;
	
	int max = strlen(p);
	pt = (char*)malloc(sizeof(char)*max);

	for(i=0; i<max; i++)
	{
		memcpy(&pt[i], &p[max-1-i], sizeof(char));
	}
	return pt;	
}

void main(){
	int i,max;
	char* p ="ABEd df g";
	printf("%s\n",p);

	//p = Restr(p);	
	
	printf("=>%s",Restr(p) );

}
