#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
ll i,j,l,r,w,t;
double n,m,s,a,b,c,bag,mor;
main(){ 
    ios::sync_with_stdio(false);
	cin.tie(0);
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	cin>>t;
	while(t--){
		cin>>n>>m; s=(1+n*m)*n*m/2;
		a=n; b=m*n*(n-1)+n; c=-1*s;  
		l=(-b+sqrt(b*b-4*a*c))/(2*a);
		
		bag=a*l*l+b*l+c;
		if (abs(bag)>abs(a*(l+1)*(l+1)+b*(l+1)+c)) l++;
		bag=a*l*l+b*l+c;
		
		a=m*m; b=m; c=-1*s;
		r=(-b+sqrt(b*b-4*a*c))/(2*a);
		
		mor=a*r*r+b*r+c;
		if (abs(mor)>abs(a*(r+1)*(r+1)+b*(r+1)+c)) r++; 
		mor=a*r*r+b*r+c;
		//cout<<l<<' '<<r<<endl;
		
		//cout<<abs(mor)<<' '<<abs(bag)<<endl;
		if (abs(bag)<=abs(mor)) cout<<"V "<<l+1<<endl;
		else cout<<"H "<<r+1<<endl;
	}
	 }
