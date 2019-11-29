#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX 10000
#define MAT 1
#define MIS 0
#define IND -1

typedef struct chr{
	char ID[MAX];
	char seq[MAX];
	int cut;
	struct chr *next;
}Chr;
	

int max(int *i, int *j){
	if(*i>*j) return *i;
	else return *j;
}


char* Restr(char *p)
{
        int i, len;
        char temp;
        len = strlen(p);
//        printf("%d\n",len);

        for(i=0; i<len/2; i++)
        {
                temp = p[i];
                p[i] = p[len-1-i];
                p[len-1-i] = temp;
	}
	return p;
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


void PrintTable( DyTable* Table, char* X, char* Y, int LEN_X, int LEN_Y ){
    int i = 0;
    int j = 0;

    printf("%4s\t", "");

    for ( i=0; i<LEN_Y+1; i++ )
       printf("%c\t", Y[i]);
    printf("\n");

    for ( i=0; i<LEN_X+1; i++ )
    {

        if ( i == 0 )
            printf( "%2s", "");
        else
            printf("%-2c", X[i-1]);

        for ( j=0; j<LEN_Y+1; j++ )
        {
            printf("%d\t", Table->Data[i][j]);
        }

        printf("\n");
    }
}


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
	
	oldlen_x = strlen(X1);
	X1[oldlen_x] =X[m-1];

	oldlen_y = strlen(Y1);
	Y1[oldlen_y] =Y[n-1];

        Dy_back( X, Y, m-1, n-1, Table, string, X1, Y1 );
    }
    else if ( Table->Data[m][n] > Table->Data[m-1][n]
              && Table->Data[m][n] < Table->Data[m][n-1])
    {
	oldlen = strlen(string);
	string[oldlen]=' ';
	memset( &string[oldlen+1] ,0 ,MAX - oldlen -1);
	
	oldlen_x = strlen(X1);
	X1[oldlen_x] =' ';

	oldlen_y = strlen(Y1);
	Y1[oldlen_y] =Y[n-1];

        Dy_back( X, Y, m, n-1, Table, string, X1, Y1 );
    }
    else
    {
	oldlen = strlen(string);
	string[oldlen]=' ';
	memset( &string[oldlen+1] ,0 ,MAX - oldlen -1);
        
	oldlen_x = strlen(X1);
	X1[oldlen_x] =X[m-1];

	oldlen_y = strlen(Y1);
	Y1[oldlen_y] =' ';
	
	Dy_back( X, Y, m-1, n, Table, string, X1, Y1 );
    }

}

void Dy(char* X, char* Y, int i, int j, DyTable* Table)
{
	int m =0;
	int n =0;
	int match, indell, indell2, max_num, zero=0;
	for ( m=0; m<=i; m++ )
		Table->Data[m][0] = 0;

	for ( n=0; n<=j; n++ )
	Table->Data[0][n] = 0;

	for ( m=1; m<=i; m++ )
	{
		for ( n=1; n<=j; n++ )
		{
            		if ( X[m-1] == Y[n-1] ){
		                match = Table->Data[m-1][n-1] + MAT;
			}
			else{
		                match = Table->Data[m-1][n-1] + MIS;
		        }        
        		indell = Table->Data[m][n-1] + IND;
	                indell2 = Table->Data[m-1][n] + IND;

			indell = max(&indell,&indell2);
			max_num = max(&indell,&match);
			max_num = max(&zero,&max_num);
			
            		
	                Table->Data[m][n] = max_num;
        	}
    	}


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

	char *A1, *B1, *C1;
	
	Result1 = (char*)malloc(sizeof(char)*MAX);
	X = (char*)malloc(sizeof(char)*MAX);
	Y = (char*)malloc(sizeof(char)*MAX);
	A1 = (char*)malloc(sizeof(char)*MAX);
	B1 = (char*)malloc(sizeof(char)*MAX);
	C1 = (char*)malloc(sizeof(char)*MAX);
			

	for(p1=root->next; p1; p1 = p1->next)
	{
		
		xlen = strlen(p1->seq);

		for(p2=root2->next; p2; p2 = p2->next)
		{
			memset( Result1, 0, sizeof(char)*MAX);
			memset( X, 0, sizeof(char)*MAX);
			memset( Y, 0, sizeof(char)*MAX);
			memset( A1, 0, MAX);
			memset( B1, 0, MAX);
			memset( C1, 0, MAX);
			
			ylen = strlen(p2->seq);
			clen = max(&xlen, &ylen);
			printf("\n\n======================================================================================================================");

			printf("\nQuery  >%s", p1->ID);
			printf("%s", p1->seq);
		

			printf("\n\nSbjct  >%s", p2->ID);
			printf("%s", p2->seq);
			
			Table.Data = (int**)malloc( sizeof(int*) * (xlen + 1) );
			for ( i=0; i < xlen+1; i++ ) {
				Table.Data[i] = (int*)malloc( sizeof(int) * (ylen + 1) );
				memset( Table.Data[i], 0, sizeof( int) * (ylen + 1 ) );
			}
			
			Dy(p1->seq,p2->seq, xlen-1, ylen-1, &Table);
//			printf("---->%s.\0.", p1->seq);
//			printf("?%d",strlen(p1->seq));
			Dy_back(p1->seq, p2->seq, xlen-1, ylen-1, &Table, Result1, X, Y);
			clen = strlen(Result1);
			Result2=0;
			for(i=0; i<clen; i++)
			{	
				if( Result1[i] =='|'){ Result2++;
				}	
			}			
			rate = (float)Result2 / (float)clen * 100;
			printf("\n[Length : %d ,rate = %f ,match = %d]\n\n",clen, rate, Result2-1);


			X =  Restr(X);
			Y = Restr(Y);
			Result1 = Restr(Result1);
//			printf("%s/\n", X);
//			printf("%s/\n", Y);
//			printf("%s/\n", Result1);
	

			printf("======================================================================================================================\n\n");
			PrintTable( &Table, p1->seq, p2->seq, xlen-1, ylen-1 );
			printf("\n\n");

			for(i=0, j=0; i<clen+1; i++){
				if(i%80==0)
				{
					A1[j]='\0';
					B1[j]='\0';
					C1[j]='\0';
					printf("Query: %s+\n", &A1[0]);
					printf("     : %s+\n", &C1[0]);
					printf("Sbjct: %s+\n", &B1[0]);
					printf("-\n");
					memset(A1, 0, sizeof(char)*MAX);
					memset(B1, 0, sizeof(char)*MAX);
					memset(C1, 0, sizeof(char)*MAX);
					j=0;
					A1[j]=X[i];
					B1[j]=Y[i];
					C1[j]=Result1[i];
					j++;
			
				}
				else{
				A1[j]=X[i];
				B1[j]=Y[i];
				C1[j]=Result1[i];
				j++;
				}
			}

			A1[j]='\0';
			B1[j]='\0';
			C1[j]='\0';
			printf("Query: %s\n", &A1[0]);
			printf("     : %s\n", &C1[0]);
			printf("Sbjct: %s\n", &B1[0]);
			printf("end.\n");

			memset(A1, 0, sizeof(char)*MAX);
			memset(B1, 0, sizeof(char)*MAX);
			memset(C1, 0, sizeof(char)*MAX);



			for ( i=0; i < xlen+1; i++ ) {
				free(Table.Data[i]);
			}
			free(Table.Data);
		}
	}
	free(X);
	free(Y);
	free(Result1);
	free(A1);
	free(B1);
	free(C1);

}

void create_root(Chr *root, FILE *fp)
{
	Chr chrom;
	char Buffer[MAX];
	int  oldlen, newlen, count=0, count2 =0, cut2 =0;
	if(fp==NULL) return;

	memset(Buffer, 0, sizeof(char)*MAX);
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
			memset(chrom.ID, 0, sizeof(char)*MAX);
			strcpy(chrom.ID, Buffer);
			count2 = 0;
		}
		else if(Buffer[0] != '>' && count2 ==0)
		{
			memset(chrom.seq,0, sizeof(char)*MAX);
			strcpy(chrom.seq, Buffer);
			count2 = 1;
		}
		else
		{
			oldlen = strlen(chrom.seq);
                        newlen = strlen(Buffer);
                        memcpy(&chrom.seq[oldlen-1],&Buffer,sizeof(char)*newlen);
                        chrom.seq[oldlen+newlen]='\n';
		}
		memset(Buffer, 0, MAX);
		
	}
	chrom.cut=cut2;
   	insert(root, &chrom);
}


int main(int argc, char* argv[]){

	FILE *fp = NULL;
	char *pt;

	Chr *root, *root2;

	root = (Chr*)malloc(sizeof(Chr));
	root->next = NULL;

	fp = fopen(argv[1], "r");
	create_root(root, fp);
	fclose(fp);
	
	root2 = (Chr*)malloc(sizeof(Chr));
	root2->next = NULL;

	fp = fopen(argv[2], "r");
	create_root(root2, fp);
	fclose(fp);

//	search(root);
//	search(root2);
	dysearch(root,root2);
	

	return 0;
}
