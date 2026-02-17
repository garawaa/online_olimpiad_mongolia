#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
ll i,j,k,l,n,m;
string a[200050],s;
unordered_map<string, ll> c,d;
unordered_map<string, ll> ::iterator ti;

main(){ 
    ios::sync_with_stdio(false);
	cin.tie(0);
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	cin>>n;
	for(i=1; i<=n; i++)
	cin>>a[i];
	for(i=1; i<=n; i++)
	{   c.clear();
		for(j=0; a[i][j]; j++)
		for(l=j; a[i][l]; l++)
		{ s.clear();
		   for(k=j; k<=l; k++)
		   s+=a[i][k];
		   c[s]=1;
		}
		for(ti=c.begin(); ti!=c.end(); ti++)
		d[ti->first]++;
	}
	k=0;
	for(i=1; i<=n; i++)
	{ 	  
	  k+=d[a[i]]-1;	
	}
	cout<<k;
	 }
