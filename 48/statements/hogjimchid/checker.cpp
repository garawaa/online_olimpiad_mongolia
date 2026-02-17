#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#define MAXN 500
#define MAXT 5000

using namespace std;
void ac()
{
	printf("1\n");
	fprintf(stderr,"Бодолт зөв байна."); 
}
void wa()
{
	printf("0\n");
	fprintf(stderr,"Бодолт буруу байна."); 
}
	int T, n;
	int dp[MAXN+1][MAXT+1];
	int pause[MAXN+1];
	int startTime[MAXN+1];

int main(int argc, char **argv) { 
 
  //input
  ifstream input(argv[1]);
  input >> T >> n; 
   for( int i = 1; i <= n; ++i ) {
      input >>pause[i];
   }
   
  //output user  
  ifstream out2(argv[3]);
  for( int i = 1; i <= n; ++i ){ 
      out2 >>startTime[i];
	  if((pause[i]+startTime[i])>T){wa(); return 0;}
	  for(int t=0;t<T;t++)
	  {
		  if(t>=startTime[i] && t<(startTime[i]+pause[i]))
			dp[i][t]=0; //амарч байгаа
		  else 
			dp[i][t]=1; //Тайзан дээр байгаа
	  }
  }
  	  for(int t=0;t<T;t++)
	  {
		int ss=0;
		for( int i = 1; i <= n; ++i ){ 
			ss+=dp[i][t];
		}  
		if(n-ss>2) {wa(); return 0;}
	  }
  ac();
  return 0;
}

