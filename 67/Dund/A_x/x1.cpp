#include <cstdio>
#define N 15
typedef long long int ll;

int freq[N];

int same_digits( ll x, ll y ) {
   for( int i = 0; i < N; ++i ) freq[i] = 0;

   while( x > 0 ) { ++freq[x%10]; x /= 10; }
   while( y > 0 ) { --freq[y%10]; y /= 10; }

   for( int i = 0; i < N; ++i )
      if( freq[i] != 0 ) return 0;

   return 1;
}
int allDigitSame(ll x){
	ll c=x%10, d;	
	x=x/10;
	while (x){		
	    //printf("%lld\n", x);
		d=x%10;		
		if (c==d) x=x/10;
		else break;
	}	
	return (x==0)?(1):(0);
}
int main( void ) {
	//freopen("x.in.10","r",stdin);
	//freopen("x.out.10","w",stdout);
	
   ll x, y;
   scanf( "%lld", &x );
   
   if (allDigitSame(x)) printf( "0\n" );
   else{   	
      ///printf( "%lld\n", y ); 
      
	  for( y = x+1; y-x < 1000000000 && !same_digits( x, y ); ++y );

      if( y-x >= 1000000000 ) printf( "0\n" );
        else printf( "%lld\n", y );     
   }
   return 0;
}
