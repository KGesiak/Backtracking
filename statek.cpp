#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum { UP = 1, RIGHT, DOWN, LEFT } Directions;

int move( int** pDepthTab, int nRow, int nCol, int nDepth, 
     	  int nextMove, int x, int y, int* px, int* py, int** pRoot )
{
	*px = x;
	*py = y;

	switch( nextMove )
	{
	case UP: *px = x - 1; break;
	case RIGHT:	*py = y + 1; break;
	case DOWN: *px = x + 1; break;
	case LEFT: *py = y - 1; break;
	default: printf( "ERROR: Wrong movement command!" ); return 0;
	}
	if( !( ( *px<0 || *px>nRow - 1 ) || ( *py<0 || *py>nCol - 1 ) ) )
		if( !( pDepthTab[*px][*py]<nDepth ) )
			if( !( pRoot[*px][*py]!=0 ) )
				return 1;
	return 0;
}

int root( int** pDepthTab, int nRow, int nCol, int nDepth,  
		  int x, int y, int** pRoot, int x_dest, int y_dest  )
{  
	static int step = 1;
	pRoot[x][y] = step++;
	if( ( x == x_dest )&&( y==y_dest ) ) return 1;
	int x1 = 0;
	int y1 = 0;
	for( int i = UP; i <= LEFT; i++ )
		if( move( pDepthTab, nRow, nCol, nDepth, i, x, y,&x1,&y1,pRoot ) )
			if( root( pDepthTab,nRow,nCol,nDepth,x1,y1,pRoot,x_dest,y_dest ) )	return 1;

	step--;
	pRoot[x][y] = 0;
	return 0;

 }   
int readDepthTab( char* sFile, int** pTab, int nRow, int nCol )
{
	FILE* fin;
	fin = fopen( sFile, "r" );
	if( !fin ) 
	{
		printf( "ERROR: File %s could not be read!", sFile );
		return 0;
	}
	for( int i = 0; i < nRow; i++ )
	{
		int* p = *pTab++;
		for( int j = 0; j < nCol; j++ )
		{
			fscanf( fin, "%d",p++ );
		}
	}
	fclose( fin );
	return 1;
}
int** createTab( int nRow, int nCol )
{
	int** pr = ( int** )malloc( sizeof( int* )*nRow );
	int* pc = ( int* )malloc( sizeof( int )*nRow*nCol );
	if( !pr || !pc ) return 0;
	memset( pr,0,sizeof( int* )*nRow );
	memset( pc,0,sizeof( int )*nRow*nCol );
	int** p = pr;
	for( int i = 0; i < nRow; i++ )
	{
		*p++ = pc;
		pc+=nCol;
	}
	return pr;
}
void printTab( int** pTab, int nRow, int nCol )
{
	for( int i = 0; i < nRow; i++ )
	{
		int* p = *pTab++;
		for( int j = 0; j < nCol; j++ )
			printf( "%3d ", *p++ );
		printf( "\n" );
	}
}
void freeTab( int*** pTab )
{
	free( **pTab );
	free( *pTab );
	*pTab = NULL;
}