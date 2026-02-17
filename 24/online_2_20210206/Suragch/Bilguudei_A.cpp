#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define N 100005
typedef long long ll;
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int test;
	cin >> test;
	while(test--){
		ll l,r;
		cin >> l >> r;
		ll k=(r-l+1)/9;
		ll d=(r-l+1)%9;
		ll u=0,ih=l%9-1;
		for(ll i=1;i<=d;i++){
			ll y=(i+ih)%9;
			if(y==0) y=9;
			u+=y;
		}
		cout << u+45*k << '\n';
	}
}