#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
#define ff first
#define ss second
#define all(s) s.begin(),s.end()
#define rall(s) s.rbegin(),s.rend()

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n;
	cin>>n;
	ll r[n+5],c[n+5];
	for(ll i=1;i<=n;i++){
		cin>>r[i];
	}
	for(ll i=1;i<=n;i++){
		cin>>c[i];
	}
	sort(r+1,r+n+1);
	sort(c+1,c+n+1);
	if(r[n]!=c[n]){
		cout<<-1;
		return 0;
	}
	ll pre[n+5];
	pre[0]=0;
	for(ll i=1;i<=n;i++){
		pre[i]=pre[i-1]+c[i];
	}
	ll ans=0;
	for(ll i=n;i>=1;i--){
		ll p=lower_bound(c+1,c+n+1,r[i])-c;
		if(p<n+1){
			ans+=(n+1-p)*r[i];
		}
		ans+=pre[p-1];
	}
	cout<<ans<<"\n";
}