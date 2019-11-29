#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX 5000

typedef struct chr{
	char ID[MAX];
	char seq[MAX];
	int cut;
	struct chr *next;
}Chr;


void insert(Chr *root, Chr *node){
	
	Chr *newChr;
	newChr = (Chr*)malloc(sizeof(Chr));
	*newChr = *node;

	newChr->next=root->next;
	root->next=newChr;

}
void search(Chr *root){
	Chr *p;
	p = root;
	for(p=root->next; p; p = p->next)
        {
		printf("\ncut>>%d", p->cut);
		printf("\nID >%s", p->ID);
		printf("SEQ >>%s", p->seq);
	}
}

typedef struct dyTable
{
	int** Data;
}DyTable;



void Dy_back( char* X, char* Y, int m, int n, DyTable* Table, char* string)
{
	
	int max;
	
	if(m>n){
		max = m;
	}else{
		max =n;
	}

	if ( m == 0 || n == 0 )
        return;

    if ( Table->Data[m][n] > Table->Data[m][n-1]
         && Table->Data[m][n] > Table->Data[m-1][n]
         && Table->Data[m][n] > Table->Data[m-1][n-1] )
    {
	char Temp[MAX];

        strcpy(Temp, string );
        sprintf(string, "%c%s", X[m-1], Temp );

        Dy_back( X, Y, m-1, n-1, Table, string );
    }
    else if ( Table->Data[m][n] > Table->Data[m-1][n]
              && Table->Data[m][n] == Table->Data[m][n-1])
    {
        Dy_back( X, Y, m, n-1, Table, string );
    }
    else
    {
        Dy_back( X, Y, m-1, n, Table, string );
    }

}

int Dy(char* X, char* Y, int i, int j, DyTable* Table)
{
	int m =0;
	int n =0;
	for ( m=0; m<=i; m++ )
		Table->Data[m][0] = 0;

	for ( n=0; n<=j; n++ )
	Table->Data[0][n] = 0;

	for ( m=1; m<=i; m++ )
	{
		for ( n=1; n<=j; n++ )
		{
            		if ( X[m-1] == Y[n-1] )
		                Table->Data[m][n] = Table->Data[m-1][n-1] + 1;
			else
            		{
		                if ( Table->Data[m][n-1] >= Table->Data[m-1][n] )
        				Table->Data[m][n] = Table->Data[m][n-1];
	                	else
	        			Table->Data[m][n] = Table->Data[m-1][n];
            		}
        	}
    	}

    return Table->Data[i][j];

}

int dysearch(Chr* root, Chr* root2)
{
	Chr *p1, *p2;
	p1 = root;
	p2 = root2;
	int i, j;
	
	DyTable Table;
	int xlen;
	int ylen;
	char *Result1;
	int Result2;
	for(p1=root->next; p1; p1 = p1->next)
	{
		for(p2=root2->next; p2; p2 = p2->next)
		{
			xlen = strlen(p1->seq);
			ylen = strlen(p2->seq);
			printf("\nA_ID >%s", p1->ID);
			printf("B_ID>>%s", p2->ID);
			
			Table.Data = (int**)malloc( sizeof(int*) * (xlen + 1) );
			for ( i=0; i < xlen+1; i++ ) {
			Table.Data[i] = (int*)malloc( sizeof(int) * (ylen + 1) );
			memset( Table.Data[i], 0, sizeof( int) * (ylen + 1 ) );
			}
			
			Result2 = Dy(p1->seq,p2->seq, xlen, ylen, &Table);
			printf("  rate = %d\n", Result2);

			Result1 = (char*)malloc(MAX);
			memset( Result1, 0,MAX);
			Dy_back(p1->seq, p2->seq, xlen, ylen, &Table, Result1);
			printf("   %s\n", Result1);
			free(Result1);
			free(Table.Data);
		}
	}
}


int main(int argc, char* argv[]){

	FILE *fp = NULL;
	char Buffer[MAX];
	char *pt, *str;
	int  oldlen, newlen, count=0, count2 =0, cut2 =0;

	Chr chrom;
	Chr *root, *root2;
	root = (Chr*)malloc(sizeof(Chr));
	root->next = NULL;
	root2 = (Chr*)malloc(sizeof(Chr));
	root2->next = NULL;

////////////////////////////////////////////////
	fp = fopen(argv[1], "r");
	
	if(fp==NULL) return;

	memset(Buffer, 0, MAX);
	while(fgets(Buffer, sizeof(Buffer), fp)){
		
		if(Buffer[0] == '>' && count == 0)
		{
			strcpy(chrom.ID, Buffer);
			count =1;
		}
		else if(Buffer[0] == '>' && count == 1)
		{
			chrom.cut=cut2;
			cut2++;
			insert(root, &chrom);
			memset(chrom.ID, 0, MAX);
			strcpy(chrom.ID, Buffer);
			count2 = 0;
		}
		else if(Buffer[0] != '>' && count2 ==0)
		{
			memset(chrom.seq,0, MAX);
			strcpy(chrom.seq, Buffer);
			count2 = 1;
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
	chrom.cut=cut2;
	cut2++;
   	insert(root, &chrom);
	fclose(fp);
////////////////////////////////////////////////////////////////
	cut2=0;
	fp = fopen(argv[2], "r");
	
	if(fp==NULL) return;

	memset(Buffer, 0, MAX);
	while(fgets(Buffer, sizeof(Buffer), fp)){
		
		if(Buffer[0] == '>' && count == 0)
		{
			strcpy(chrom.ID, Buffer);
			count =1;
		}
		else if(Buffer[0] == '>' && count == 1)
		{
			chrom.cut=cut2;
			cut2++;
			insert(root2, &chrom);
			memset(chrom.ID, 0, MAX);
			strcpy(chrom.ID, Buffer);
			count2 = 0;
		}
		else if(Buffer[0] != '>' && count2 ==0)
		{
			memset(chrom.seq,0, MAX);
			strcpy(chrom.seq, Buffer);
			count2 = 1;
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
	chrom.cut=cut2;
	cut2++;
   	insert(root2, &chrom);
	fclose(fp);

//	search(root);
//	search(root2);
	dysearch(root,root2);

	

	return 0;
}
