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
	while(p != NULL)
        {
		printf("\nID >%s", p->node.ID);
		printf("\nSEQ >>%s", p->node.seq);
		p = p->next;
	}
}

void insert(list** root, chr node)
{
	*root = insertnode(*root, node);
}

int main(int argc, char* argv[]){

	FILE *fp = NULL;
	printf("!!");	
	char Buffer[MAX];
	char *pt, *str;
	int  oldlen, newlen, count=0, count2 =0;

	printf("!!");	
	chr chrom;
	list *root = NULL;

	fp = fopen(argv[1], "r");
	
	if(fp==NULL) return;

	printf("!!");	
	memset(Buffer, 0, MAX);
	while(fgets(Buffer, sizeof(Buffer), fp)){
		
		if(Buffer[0] == '>' && count == 0)
		{
			strcpy(chrom.ID, Buffer);
			count =1;
		}
		else if(Buffer[0] == '>' && count == 1)
		{
			insert(&root, chrom);
			memset(chrom.ID,0, MAX);
			memset(chrom.seq,0, MAX);
			strcpy(chrom.ID, Buffer);
			count2=0;
		}
		else if(Buffer[0] != '>' && count2 ==0)
		{
//			memset(chrom.seq,0, MAX);
			strcpy(chrom.seq, Buffer);
			count2=1;
		}
		else
		{
			oldlen = strlen(chrom.seq);
			newlen = strlen(Buffer);
			memcpy(&chrom.seq[oldlen-1],&Buffer,newlen);
			chrom.seq[oldlen+newlen]='\n';
			
		}
		memset(Buffer, 0, MAX);
		
	}
	insert(&root, chrom);
	fclose(fp);

	search(root);

	return 0;
}
