#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX 10000

typedef struct chr{
	char ID[MAX];
	char seq[MAX];
	int cut;
	struct chr *next;
}Chr;
	
char* Restr(char* p)
{
	char* pt;
        int i;

        int max = strlen(p);
        pt = (char*)malloc(sizeof(char)*max);
	memset(pt, 0, max+1);

        for(i=0; i<max; i++)
        {
                memcpy(&pt[i], &p[max-1-i], sizeof(char));
        }
        return pt;
}

int max(int *i, int *j){
	if(*i>*j) return *i;
	else return *j;
}


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



void Dy_back( char* X, char* Y, int m, int n, DyTable* Table, 
		char* string, char* X1, char* Y1)
{
	

	int oldlen, i;
	int oldlen_x; 
	int oldlen_y;

	if ( m == 0 || n == 0 )
        return;

    if ( Table->Data[m][n] > Table->Data[m][n-1]
         && Table->Data[m][n] > Table->Data[m-1][n]
         && Table->Data[m][n] > Table->Data[m-1][n-1] )
    {

	oldlen = strlen(string);
	string[oldlen]='|';
	memset( &string[oldlen+1] ,0 ,MAX - oldlen -1);
//	string[oldlen+1]='\0';
	
	oldlen_x = strlen(X1);
	X1[oldlen_x] =X[m-1];
//	X1[oldlen_x+1]='\0';

	oldlen_y = strlen(Y1);
	Y1[oldlen_y] =Y[n-1];
//	Y1[oldlen_y+1]='\0';

        Dy_back( X, Y, m-1, n-1, Table, string, X1, Y1 );
    }
    else if ( Table->Data[m][n] > Table->Data[m-1][n]
              && Table->Data[m][n] == Table->Data[m][n-1])
    {
	oldlen = strlen(string);
	string[oldlen]=' ';
	memset( &string[oldlen+1] ,0 ,MAX - oldlen -1);
//	string[oldlen+1]='\0';
	
	oldlen_x = strlen(X1);
	X1[oldlen_x] =' ';
//	X1[oldlen_x+1]='\0';

	oldlen_y = strlen(Y1);
	Y1[oldlen_y] =Y[n-1];
//	Y1[oldlen_y+1]='\0';

        Dy_back( X, Y, m, n-1, Table, string, X1, Y1 );
    }
    else
    {
	oldlen = strlen(string);
	string[oldlen]=' ';
	memset( &string[oldlen+1] ,0 ,MAX - oldlen -1);
//	string[oldlen+1]='\0';
        
	oldlen_x = strlen(X1);
	X1[oldlen_x] =X[m-1];
//	X1[oldlen_x+1]='\0';

	oldlen_y = strlen(Y1);
	Y1[oldlen_y] =' ';
	//Y1[oldlen_y+1]='\0';
	
	Dy_back( X, Y, m-1, n, Table, string, X1, Y1 );
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
	int i, j=0;
	
	DyTable Table;
	int xlen, ylen, clen;
	float rate;
	char *Result1;
	int Result2;
	char *X, *Y;

	char *A, *B, *C, *A1, *B1, *C1;
	
			
	Result1 = (char*)malloc(sizeof(char)*MAX);
	X = (char*)malloc(sizeof(char)*MAX);
	Y = (char*)malloc(sizeof(char)*MAX);
	A = (char*)malloc(sizeof(char)*MAX);
	B = (char*)malloc(sizeof(char)*MAX);
	C = (char*)malloc(sizeof(char)*MAX);
	A1 = (char*)malloc(sizeof(char)*MAX);
	B1 = (char*)malloc(sizeof(char)*MAX);
	C1 = (char*)malloc(sizeof(char)*MAX);
	memset(A, 0, MAX);
	memset(B, 0, MAX);
	memset(C, 0, MAX);
	memset(A1, 0, MAX);
	memset(B1, 0, MAX);
	memset(C1, 0, MAX);

	for(p1=root->next; p1; p1 = p1->next)
	{
		for(p2=root2->next; p2; p2 = p2->next)
		{
			
			xlen = strlen(p1->seq);
			ylen = strlen(p2->seq);
			clen = max(&xlen, &ylen);
			if(clen < 4000){
			printf("======================================================================================================================");

			printf("\nA_ID  >%s", p1->ID);
			printf("B_ID  >%s", p2->ID);
		
			printf("======================================================================================================================\n");
			printf("A_seq ||%s", p1->seq);
			printf("B_seq ||%s", p2->seq);
			
			Table.Data = (int**)malloc( sizeof(int*) * (xlen + 1) );
			for ( i=0; i < xlen+1; i++ ) {
				Table.Data[i] = (int*)malloc( sizeof(int) * (ylen + 1) );
				memset( Table.Data[i], 0, sizeof( int) * (ylen + 1 ) );
			}
			
			Result2 = Dy(p1->seq,p2->seq, xlen, ylen, &Table);
			rate = (float)Result2 / (float)clen * 100;
			printf("\n[Length : %d ,rate = %f ,match = %d]\n",clen, rate, Result2);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

			memset( Result1, '\0', sizeof(char)* MAX);
			memset( X, '\0', sizeof(char)*MAX);
			memset( Y, '\0', sizeof(char)*MAX);

			Dy_back(p1->seq, p2->seq, xlen, ylen, &Table, Result1, X, Y);
	
			strcpy(A, Restr(X));
			strcpy(B, Restr(Y));
			strcpy(C, Restr(Result1));
			
			clen = strlen(C);
			printf("A %s", A);
			printf("C %s\n", C);
			printf("B %s+\n\n", B);

			for(i=0, j=0; i<clen+1; i++){
				if(i !=0 && i%80 ==0){
					A1[j]='\0';
					B1[j]='\0';
					C1[j]='\0';
					printf("A: %s\n", &A1[0]);
					printf("C: %s\n", &C1[0]);
					printf("B: %s\n", &B1[0]);
					printf("-\n");
					memset(A1, 0, MAX);
					memset(B1, 0, MAX);
					memset(C1, 0, MAX);
					j=0;
			
				}
				else{
				A1[j]=A[i];
				B1[j]=B[i];
				C1[j]=C[i];
				j++;
				}
			}

			A1[j]='\0';
			B1[j]='\0';
			C1[j]='\0';
			printf("A: %s", &A1[0]);
			printf("C: %s\n", &C1[0]);
			printf("B: %s\n", &B1[0]);
			printf("-\n");
			memset(A1, 0, MAX);
			memset(B1, 0, MAX);
			memset(C1, 0, MAX);
			j=0;

			free(Table.Data);
			}
			printf("end.\n");
		}
	}
	free(Result1);
	free(X);
	free(Y);
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
