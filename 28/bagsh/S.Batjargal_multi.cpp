#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
ll i,j,k,l,n,t,x,y,a[200],b[200][200]; 
main(){  
    ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>t;
	while(t--){ cin>>n;
 		for(i=1; i<=n; i++)
		for(j=1; j<=n; j++) b[i][j]=100000000000000000;
		
		
		for(i=1; i<=n; i++) cin>>a[i];
		
		for(i=1; i<=n-2; i++)
		b[i][i+2]=a[i]*a[i+1]*a[i+2];
		
		for(i=4; i<=n; i++)
		{
			for(j=i-3; j>=1; j--)
			{  
			   for(l=j+1; l<i; l++)
			   { k=0;
			     if (j+1==l) { x=a[j]*a[l]*a[i]; k=1;}
			   	 else x=b[j][l];
			   	 if (l+1==i) {k=1; y=a[j]*a[l]*a[i];}
			   	 else y=b[l][i];
			     if (k==0) b[j][i]=min(x+y+a[j]*a[l]*a[i],b[j][i]);
			     else b[j][i]=min(x+y,b[j][i]);
			   }
			} 
		}
		cout<<b[1][n]<<endl;
	}
	} 

