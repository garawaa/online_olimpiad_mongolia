#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define M 1000001
typedef long long ll;
// const int p=53;
const long long MOD=1000000007;
using namespace std;
int p[1001];
bool k[2][1000001];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> p[i];
	}
	k[0][0]=1;
	ll mx=0;
	for(int i=1;i<=n;++i){
		vector<ll>v;
		for(int j=p[i];j<=1000000;++j){
			if(k[0][j-p[i]]==1){
				 k[1][j]=1;
				 v.pb(j);
			}
		}
		for(int j=0;j<v.size();j++){
			k[0][v[j]]=1;
			mx=max(mx,v[j]);	
		} 
	}
	ll ans=mx,bef=mx,l=0;
	for(ll i=mx-1;i>=0;i--){
		if(k[0][i]==1){
			ans+=(mx-i);
			ans+=(l*(bef-i-1));
			l++;
			bef=i;
		}
	}
	cout << ans+1;
}