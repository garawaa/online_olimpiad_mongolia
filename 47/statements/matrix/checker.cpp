#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#define Row first
#define Col second

using namespace std;
vector< string > rez;
vector< pair< int, int > > koord;
struct element{
	int value;
	int urjigdsen;
} mat[ 105 ][ 105 ],tmp[ 105 ];

int R, S, niz[ 10005 ];
int recon[ 20005 ], moguce[ 20005 ] = { 1 };
int sumuk[ 20005 ] = { 0 }, negativnih = 0;
int por[ 10005 ], cnt = 0;
char tmpbuff[ 105 ], ozn[ 105 ][ 105 ];

void ac()
{
	printf("1\n");
	fprintf(stderr,"Шаардлага 100 хувь хангасан бодолт мөн."); 
}
void achalf()
{
	printf("0.5\n");
	fprintf(stderr,"Шаардлага 50 хувь хангасан бодолт байна."); 
}
void wa()
{
	printf("0\n");
	fprintf(stderr,"Бодолт буруу"); 
}
void rotaterow( int row, int K ) {
	for( int i = 0; i < S; ++i )
		tmp[ ( i + K ) % S ] = mat[ row ][ i ];
	for( int i = 0; i < S; ++i )
		mat[ row ][ i ] = tmp[ i ];
	for( int i = 0; i < ( int )koord.size(); ++i )
		if( koord[ i ].Row == row )
			koord[ i ].Col = ( koord[ i ].Col + K ) % S;
	sprintf( tmpbuff, "ergBaruun %d %d", row + 1, K );
	rez.push_back( string( tmpbuff ) );
}

void rotatecol( int col, int K ) {
	for( int i = 0; i < R; ++i )
		tmp[ ( i + K ) % R ] = mat[ i ][ col ];
	for( int i = 0; i < R; ++i )
		mat[ i ][ col ] = tmp[ i ];
	for( int i = 0; i < ( int )koord.size(); ++i )
		if( koord[ i ].Col == col )
			koord[ i ].Row = ( koord[ i ].Row + K ) % R;
	sprintf( tmpbuff, "ergDoosh %d %d", col + 1, K );
	rez.push_back(string(tmpbuff));
}

void changerow( int row ) {
	for( int i = 0; i < S; ++i ){
		mat[ row ][ i ].value = -mat[ row ][ i ].value;
		mat[ row ][ i ].urjigdsen += 1;
	}
	sprintf( tmpbuff, "sorogMor %d", row + 1 );
	rez.push_back(string(tmpbuff ));
}

void changecol( int col ) {
	for( int i = 0; i < R; ++i ){
		mat[ i ][ col ].value = -mat[ i ][ col ].value;
		mat[ i ][ col ].urjigdsen+=1;
	}
	sprintf( tmpbuff, "sorogBagana %d", col + 1 );
	rez.push_back( string( tmpbuff ) );
}
/*
int suma( int a, int b ) {
	if( a > b ) return( 0 );
	return( sumuk[ b ] - ( a == 0 ? 0 : sumuk[ a-1 ] ) );
}

int evalpod( int X ) {
	return( suma( X, R * S - 1 ) - suma( 0, X - 1 ) );
}

pair< int, int > pronadji( int X ) {
	for( int i = 0; i < R; ++i )
		for( int j = 0; j < S; ++j )
			if( !ozn[ i ][ j ]  &&  mat[ i ][ j ] == X ) {
				ozn[ i ][ j ] = 1;
				return make_pair( i, j );
			}
	return make_pair( -1, -1 );
}

void sredi_stupac( void ) {
	int len = ( int )koord.size();
	for( int i = 0; i < len; ++i ) {
		int razl = i - koord[ i ].Row;
		if( razl < 0 ) razl += R;
		
		if( koord[ i ].Col == 0 ) rotaterow( koord[ i ].Row, 1 );
		if( koord[ i ].Row != i ) rotatecol( koord[ i ].Col, razl );
		rotaterow( koord[ i ].Row, S - koord[ i ].Col );
	}
}

void sredi_redak( void ) {
	int len = ( int )koord.size();
	for( int i = 0; i < len; ++i ) {
		int razl = i - koord[ i ].Col;
		if( razl < 0 ) razl += S;
		
		if( koord[ i ].Row == 0 ) rotatecol( koord[ i ].Col, 1 );
		if( koord[ i ].Col != i ) rotaterow( koord[ i ].Row, razl );
		rotatecol( koord[ i ].Col, R - koord[ i ].Row );
	}
}
*/
int main(int argc, char **argv) {  
	int zohiogchS,bodoltS,bodoltT,uildelS=0,doubleUrjigdsen = 0;   
  //input
  ifstream input(argv[1]);
  input >> R >> S; 
	for( int i = 0; i < R; ++i )
		for( int j = 0; j < S; ++j ) {
			input >> mat[ i ][ j ].value;
			niz[ S * i + j ] = mat[ i ][ j ].value;
			mat[ i ][ j ].urjigdsen = 0;
		}

  //output author - correct
  ifstream out1(argv[2]);
   out1 >> zohiogchS;
   
   string command;
   int ii,jj,kk;
  //output user  
  ifstream out2(argv[3]);
  out2 >> bodoltS >> bodoltT;
		for( int i = 0; i < bodoltT; ++i ){
			out2 >> command;
			if(command=="ergBaruun"){
					out2 >>ii>>kk;
					rotaterow( ii-1, kk );
			}
			else if(command=="ergDoosh"){
					out2 >>jj>>kk;
					rotatecol( jj-1, kk );
			}			
			else if(command=="sorogMor"){
					out2 >>ii;
					changerow(ii-1);
			}			
			else if(command=="sorogBagana"){
					out2 >>jj;
					changecol(jj-1);
			}
		}
		uildelS = 0;
		for( int i = 0; i < R; ++i ){
			for( int j = 0; j < S; ++j ){
				uildelS+=mat[i][j].value;
				if(mat[i][j].urjigdsen>1) 
					doubleUrjigdsen = 1;
			}
		}

  if(bodoltS != zohiogchS || bodoltT>100000 || doubleUrjigdsen==1)
  {
	  wa();
	  return 0;
  } 
  else if(bodoltS == zohiogchS && bodoltT<=5*R*S && uildelS==zohiogchS)
	  {
		  ac();
		  return 0;
	  } 
	  else if(bodoltS == zohiogchS && bodoltT>5*R*S && bodoltT<=100000 && uildelS==zohiogchS)
	  {
		  achalf();
		  return 0;
	  }  
  wa();
  return 0;
}

