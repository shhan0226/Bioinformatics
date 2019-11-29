#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX 5000

typedef struct Chr{
	char ID[MAX];
	char seq[MAX];
}chr;

typedef struct List{
	chr node;
	struct List *next; 
}list;

list* insertnode(list *p, chr node){
	
	list *newList;
	if(p == NULL)
	{
		newList = (list*)malloc(sizeof(list));
		newList->node = node;
		newList->next = NULL;
		return newList;
	}
	else
	{
		if(strcmp(node.ID, p->node.ID)==0)
		{
			printf("already chr");
		}
		else
		{
			p->next = insertnode(p->next, node);
		}
	return p;
	}
}

void search(list* root)
{
	list *p;
	p = root;
	while(p == NULL)
        {
		printf("ID \n%s ", p->node.ID);
		printf("SEQ\n%s ", p->node.seq);
		p = p->next;
	}
}

void insert(list** root, chr node)
{
	*root = insertnode(*root, node);
}

int main(int argc, char* argv[]){

	FILE *fp = NULL;
		
	char Buffer[MAX];
	char string[MAX];
	char *pt, *str;
	int  count=0;

	chr chrom;
	list *root = NULL, *temp = NULL;

	fp = fopen(argv[1], "r");
	
	if(fp==NULL) return;
	pt = Buffer;

	while(fgets(Buffer, sizeof(Buffer), fp)){
		
		printf("%s",Buffer);		

	}

	fclose(fp);

	return 0;
}
