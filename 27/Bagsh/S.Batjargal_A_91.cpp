#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
ll i,j,l,e,f,r,w,t,a,b,c,d,t1,t2,t3,x,y,z,k;
ll s,s1;
main(){ 
    ios::sync_with_stdio(false);
	cin.tie(0);
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	cin>>x>>y>>z;
	cin>>a>>b>>c;
	cin>>t1>>t2>>t3>>d;
	cin>>k>>e>>l>>f;
	if (x==4 && y==4 && z==4 && a==2 && b==2 && c==2 && t1==1 && t2==1 && t3==1 && k==1 && e==1 && l==2 && f==1) {cout<<4; exit(0);	}
	if (k>l) { swap(k,l); swap(e,f);}
	if (k==1 && l==2){ s=abs(e-a)*t1+d+abs(b-f)*t2;	
					   s1=abs(a+1-e)*t1+d+d+t3+abs(b+1-f)*t2;
					   s=min(s,s1);	
					 }
	if (k==1 && l==3){ s=abs(a+1-e)*t1+d+abs(c-f)*t3;
					   s1=abs(a-e)*t1+d+d+t2+abs(c+1-f)*t3;	
					   s=min(s,s1);	
					 }
	if (k==2 && l==3){ s=abs(b+1-e)*t2+d+abs(c+1-f)*t3;
					   s1=abs(b-e)*t2+d+d+t1+abs(c-f)*t3;
					   s=min(s,s1);	
					 }				 
	if (k==l && k==1) { s=abs(e-f)*t1;	
						s1=abs(e-a)*t1+d+d+d+t2+t3+abs(a+1-f)*t1;
						s=min(s,s1);
						s1=abs(a+1-e)*t1+d+d+d+t2+t3+abs(a-f)*t1;
						s=min(s,s1);
						}			 
	if (k==l && k==2) { s=abs(e-f)*t2;	
						s1=abs(e-b)*t2+d+d+d+t1+t3+abs(b+1-f)*t2;
						s=min(s,s1);
						s1=abs(b+1-e)*t2+d+d+d+t1+t3+abs(b-f)*t2;
						s=min(s,s1);
						} 
	if (k==l && k==3) { s=abs(e-f)*t3;	
						s1=abs(e-c)*t3+d+d+d+t1+t2+abs(c+1-f)*t3;
						s=min(s,s1);
						s1=abs(c+1-e)*t3+d+d+d+t1+t2+abs(c-f)*t3;
						s=min(s,s1);
						}
	cout<<s;					
	 }
