#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define pp push
#define MOD 1000000007
#define INF 1e18
#define N 200001
#define M 5000000
typedef long long ll;
using namespace std;
ll a[N],b[N],sta[N][20],stb[N][20],val[30],id[N];
ll mn(bool f,ll i,ll j){
	ll l=log2(j-i+1);
	if(f==0){
		return min(sta[i][l],sta[j-val[l]+1][l]);
	}
	else{
		return min(stb[i][l],stb[j-val[l]+1][l]);
	}
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	val[0]=1;
	for(int i=1;i<=29;i++){
		val[i]=val[i-1]*2;
	}
	ll n;
	cin >> n;
	for(ll i=1;i<=n;i++){
		cin >> a[i] >> b[i];
		id[i]=i;
	}
	for(ll i=1;i<=n;i++){
		sta[i][0]=a[i];
		stb[i][0]=b[i];
	}
	shuffle(id+1,id+n+1,rng);
	ll l=log2(n);
	for(ll i=1;i<=l;i++){
		for(ll j=1;j<=(n-val[i]+1);j++){
			sta[j][i]=min(sta[j][i-1],sta[j+val[i-1]][i-1]);
			stb[j][i]=min(stb[j][i-1],stb[j+val[i-1]][i-1]);
		}
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
		int j=id[i];
		while(j>0){
			ll aa=mn(0,j,id[i]);
			ll bb=mn(1,j,id[i]);
			if(aa*bb*(id[i]-j+1)>ans){
				ans=aa*bb*(id[i]-j+1);
				j--;
			}
			else{
				ll k=ans/(aa*bb);
				k++;
				j=id[i]-k+1;
			}
		}
	}
	cout << ans;
}