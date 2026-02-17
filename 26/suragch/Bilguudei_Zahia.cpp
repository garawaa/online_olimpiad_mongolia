#include <bits/stdc++.h>
typedef long long ll;
#define N 2005
using namespace std;
int main() {
	unsigned long long a,b,c,d;
	cin >> a >> b >> c >> d;
	unsigned long long x=c,y=d;
	int cnt1=0,cnt2=0;
	while(a>x){
		x*=2;
		cnt1++;
	}
	while(b>y){
		y*=2;
		cnt1++;
	}
	x=d,y=c;
	while(a>x){
		x*=2;
		cnt2++;
	}
	while(b>y){
		y*=2;
		cnt2++;
	}
	cout << min(cnt1,cnt2);
}