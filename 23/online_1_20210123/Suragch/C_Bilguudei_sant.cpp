#include <bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll a,b;
	cin >> a >> b;
	if(a==b){
		cout << 0;
		return 0;
	}
	else{
		if(a<b) swap(a,b);
		ll x=a-b;
		ll u=__gcd(x,a);
		ll y=a*x/u;
		ll z=y/x;
		ll o=(z-1)*b-a;
		ll t=a*b/(__gcd(a,b));
		cout << (o%t+t)%t;
	}
}