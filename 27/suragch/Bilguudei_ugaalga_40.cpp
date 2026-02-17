#include <bits/stdc++.h>
#define N 100005
#define pb push_back
#define ss second
#define ff first
#define INF 1000000007
typedef long long ll;
using namespace std;
ll x1[N],y11[N],x2[N],y2[N];
pair<pair<ll,ll>,ll>sp[N],temp;
unordered_map<ll,bool>color[N];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n,m;
	cin >> n >> m;
	for(ll i=1;i<=n;i++){
		cin >> x1[i] >> y11[i] >> x2[i] >> y2[i];
	}
	for(ll i=1;i<=m;i++){
		cin >> sp[i].ff.ff >> sp[i].ff.ss >> sp[i].ss;
	}
	sort(sp+1,sp+m+1);
	for(ll i=1;i<=n;i++){
		temp={{x1[i],0},0};
		ll id1=lower_bound(sp+1,sp+m+1,temp)-(sp+1);
		temp={{x2[i],INF},INF};
		ll id2=upper_bound(sp+1,sp+m+1,temp)-(sp+1);
		ll ans=0;
		for(ll j=id1+1;j<=id2;j++){
			if(sp[j].ff.ss>=y11[i] && y2[i]>=sp[j].ff.ss && color[i][sp[j].ss]==0){
				ans++;
				color[i][sp[j].ss]=1;
			}
		}
		cout << ans << "\n";
	}

		
 
}