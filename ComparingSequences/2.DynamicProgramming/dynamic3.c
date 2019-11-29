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
	

	int i, oldlen;
	int oldlen_x, oldlen_y;
	char temp[MAX], temp2[MAX];
	oldlen_x = strlen(X);
	oldlen_y = strlen(Y);
	memset(temp,0,oldlen_x);
	memset(temp2,0,oldlen_y);

	if ( m == 0 || n == 0 )
        return;

	if ( 	Table->Data[m][n] > Table->Data[m][n-1]
        	&& Table->Data[m][n] > Table->Data[m-1][n]
		&& Table->Data[m][n] > Table->Data[m-1][n-1] )
	{
		oldlen = strlen(string);
		string[oldlen]=X[m-1];
		string[oldlen+1]='\0';
        	Dy_back( X, Y, m-1, n-1, Table, string );
	}
	else if ( Table->Data[m][n] > Table->Data[m-1][n]
              && Table->Data[m][n] == Table->Data[m][n-1])
    	{
		for(i=0; i <=n; i++){
		  temp[i]=X[i];
		}
		  temp[n+1]=' ';
		for(i=n+1; i< oldlen_x;i++){
		  temp[i+1] = X[i];
		}
		strcpy(X, temp);
		
		oldlen = strlen(string);
		string[oldlen]='|';
		string[oldlen+1]='\0';
        	Dy_back( X, Y, m, n-1, Table, string );
	}
	else
	{
		for(i=0; i <=m; i++){
		  temp2[i]=Y[i];
		}
		  temp2[m+1]=' ';
		for(i=m+1; i< oldlen_y;i++){
		  temp2[i+1] = Y[i];
		}
		strcpy(Y, temp2);
		
		oldlen = strlen(string);
		string[oldlen]='|';
		string[oldlen+1]='\0';
	        Dy_back( X, Y, m-1, n, Table, string );
	}

}

int Dy(char* X, char* Y, int i, int j, DyTable* Table)
{
	int m =0;
	int n =0;
	for ( m=0; m<=i; m++ ){	Table->Data[m][0] = 0;}
	for ( n=0; n<=j; n++ ){	Table->Data[0][n] = 0;}

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

int max(int *i, int *j){

	if (*i>*j) return *i;
	else return *j;

}

int dysearch(Chr* root, Chr* root2)
{
	Chr *p1, *p2;
	p1 = root;
	p2 = root2;
	int i, j, k,l, sum;
	
	DyTable Table;
	int xlen, ylen;
	char X[MAX], Y[MAX];

	memset(X, 0, MAX);
	memset(Y, 0, MAX);
	
	char Result1[MAX];
	int Result2;
	for(p1=root->next; p1; p1 = p1->next)
	{
		for(p2=root2->next; p2; p2 = p2->next)
		{
			
			xlen = strlen(p1->seq);
			ylen = strlen(p2->seq);
			sum = max(&xlen, &ylen);
			strcpy(X, p1->seq);
			strcpy(Y, p2->seq);
			printf("\n\n________________________________\n\n%s",X);
			printf("%s",Y);

			printf("\nA_ID >%s", p1->ID);
			printf("B_ID>>%s", p2->ID);
			
			Table.Data = (int**)malloc( sizeof(int*) * (xlen + 1) );
			for ( i=0; i < xlen+1; i++ ) {
			Table.Data[i] = (int*)malloc( sizeof(int) * (ylen + 1) );
			memset( Table.Data[i], 0, sizeof( int) * (ylen + 1 ) );
			}
			
			Result2 = Dy(X, Y, xlen, ylen, &Table);
			printf("match = %d \n", Result2 );

			memset( Result1, 0,MAX);
			Dy_back(X, Y, xlen, ylen, &Table, Result1);
			
			printf("C :\n %s \n",Result1);
			
		/*	for(k=0; k<sum; k+=80){
				printf("A\n");
				for(j=k; j<80;j++){ 
					printf("%c",X[j] ); 
				}
				printf("\n");
				printf("com");
				for(j=k; j<80;j++){ 
					printf("%c",Result1[j] ); 
				}
				printf("\n");
				printf("B\n");
				for(j=k; j<80;j++){ 
					printf("%c",Y[j] ); 
				}
				printf("\n");
			}
		*/	
			free(Table.Data);
			memset(X,0,MAX);
			memset(Y,0,MAX);
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
