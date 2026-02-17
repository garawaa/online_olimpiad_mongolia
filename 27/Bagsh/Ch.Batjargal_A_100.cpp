#include <bits/stdc++.h>
using namespace std;
long long  xx,yy,zz,a,b,c,x,y,x2,y2,min1,s;
int main(){
	long long t1,t2,t3,d;
	cin>>xx>>yy>>zz>>a>>b>>c>>t1>>t2>>t3>>d>>x>>y>>x2>>y2;
	if (x==x2 && y==y2) {
		cout<<0;
		return 0;
	}
	if (x>x2) {
		swap(x,x2);
		swap(y,y2);
	}
	min1=1e19;
	if (x==1 && x2==2){
		s=0;
		s+=abs(y-a)*t1;
		s+=d;
		s+=abs(b+1-y2)*t2;
		if (min1>s) min1=s;
		
		s=0;
		s+=abs(y-(a+1))*t1;
		s+=d+t3+d;
		s+=abs(b-y2)*t2;
		if (min1>s) min1=s;
		cout<<min1;
	
	}
	else
	if (x==1 && x2==3){
		s=0;
		s+=abs(y-a)*t1;
		s+=d+t2+d;
		s+=abs(c+1-y2)*t3;
		if (min1>s) min1=s;
		
		s=0;
		s+=abs(y-(a+1))*t1;
		s+=d;
		s+=abs(c-y2)*t3;
		if (min1>s) min1=s;
		cout<<min1;
	}
	else
	if (x==2 && x2==3){
		s=0;
		s+=abs(y-(b+1))*t2;
		s+=d+t1+d;
		s+=abs(c-y2)*t3;
		if (min1>s) min1=s;
		
		s=0;
		s+=abs(y-b)*t2;
		s+=d;
		s+=abs(c+1-y2)*t3;
		if (min1>s) min1=s;
		cout<<min1;
	
	}
	else
	if (x==1 && x2==1){
		s=abs(y-y2)*t1;
		if(min1>s) min1=s;
		
		s=abs(y-a)*t1;
		s+=d+t2+d;
		s+=t3+d;
		s+=abs(y2-(a+1))*t1;
		if(min1>s) min1=s;
		
		s=abs(y-(a+1))*t1;
		s+=d+t3+d;
		s+=t2+d;
		s+=abs(y2-a)*t1;
		if(min1>s) min1=s;
		cout<<min1;
	}
	else
	if (x==2 && x2==2){
		s=abs(y-y2)*t2;
		if(min1>s) min1=s;
		
		s=abs(y-b)*t2;
		s+=d+t3+d;
		s+=t1+d;
		s+=abs(y2-(b+1))*t2;
		if(min1>s) min1=s;
		
		s=abs(y-(b+1))*t2;
		s+=d+t1+d;
		s+=t3+d;
		s+=abs(y2-b)*t2;
		if(min1>s) min1=s;
		cout<<min1;
	}
	else
	if (x==3 && x2==3){
		s=abs(y-y2)*t3;
		if(min1>s) min1=s;
		
		s=abs(y-c)*t3;
		s+=d+t1+d;
		s+=t2+d;
		s+=abs(y2-(c+1))*t3;
		if(min1>s) min1=s;
		
		s=abs(y-(c+1))*t3;
		s+=d+t2+d;
		s+=t1+d;
		s+=abs(y2-c)*t3;
		if(min1>s) min1=s;
		cout<<min1;
	}	
}

