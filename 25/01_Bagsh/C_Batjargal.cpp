#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
vector<ll> v[1005];
ll a[1005]; 
bool b[1005];
ll rec(ll k,ll l){ b[k]=1;  
		if (v[k].size()==1 && b[v[k][0]]==1) { return a[k];}
		ll m,m1,m2,g=0; m=0; m1=0; m2=0;
		for(ll i=0; i<v[k].size(); i++) 
		if (b[v[k][i]]==0){ g=rec(v[k][i],l*(-1));
							if (g==1)   m=1;
							if (g==0)   m1=1;
							if (g==-1)  m2=1;
						  }
						  
		if (l==1){ //if (k==2) cout<<'f';
		
					if ( m==1)   { a[k]=1; return 1;}
					if ( m1==1)  { a[k]=0; return  0;}
		   						 { a[k]=-1; return  -1;}
		
		}
		if (l==-1){ 
					if (m2==1)  { a[k]=-1; return  -1;}
					if (m1==1)  { a[k]=0; return  0;}
		  					    { a[k]=1; return  1;}	
	}
		
		}
main(){ ll n,k,l;
		char ch;
    ios::sync_with_stdio(false);
	cin.tie(0);  
	cin>>n;
	for(ll i=1; i<n; i++)	
	{ cin>>ch; cin>>k;
	  if (ch=='N') { v[i+1].pb(k); v[k].pb(i+1); }	
	  else { cin>>l;  v[i+1].pb(k); v[k].pb(i+1); a[i+1]=l;}	 
	}
	if (n==2){ if (a[2]==1) { cout<<'+'<<1; }
			   else cout<<a[2];
			   exit(0);
			 }		 
		
	k=rec(1,1);
	if (k>=1) cout<<'+'<<k;
	else cout<<k; 
//	cout<<endl; 
//	for(ll i=1; i<=n; i++)
//	cout<<a[i]<<' ';
	}
