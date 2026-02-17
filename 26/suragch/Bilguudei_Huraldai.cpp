#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define pp push
#define MOD 1000000007
#define INF 1e18
#define N 300005
#define M 5000000
typedef long long ll;
using namespace std;
ll x[N],y[N],ans[N];
bool occ[2505][2505];
ll cnt[2505][2505];
pair<ll,ll>a[2505][2505],b[2505][2505];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
 	ll n;
 	cin >> n;
 	for(ll i=1;i<=n;i++){
 		cin >> x[i] >> y[i];
 		occ[x[i]][y[i]]=1;
 	}
 	for(ll i=1;i<=2500;i++){
 		for(ll j=1;j<=2500;j++){
 			cnt[i][j]=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1];
 			if(occ[i][j]==1){
 				a[i][j]={i,j};
 				if(a[i-1][j].ff!=0){
 					a[i][j].ff=min(a[i][j].ff,a[i-1][j].ff);
 				}
 				if(a[i-1][j].ss!=0){
 					a[i][j].ss=min(a[i][j].ss,a[i-1][j].ss);
 				}
 				if(a[i][j-1].ff!=0){
 					a[i][j].ff=min(a[i][j].ff,a[i][j-1].ff);
 				}
 				if(a[i][j-1].ss!=0){
 					a[i][j].ss=min(a[i][j].ss,a[i][j-1].ss);
 				}
 				cnt[i][j]++;
 			}
 			else{
 				if(a[i-1][j].ff!=0){
 					if(a[i][j-1].ff!=0){
 						a[i][j].ff=min(a[i-1][j].ff,a[i][j-1].ff);
 					}
 					else a[i][j].ff=a[i-1][j].ff;
 				}
 				else{
 					if(a[i][j-1].ff!=0){
 						a[i][j].ff=a[i][j-1].ff;
 					}
 				}
 				if(a[i-1][j].ss!=0){
 					if(a[i][j-1].ss!=0){
 						a[i][j].ss=min(a[i-1][j].ss,a[i][j-1].ss);
 					}
 					else a[i][j].ss=a[i-1][j].ss;
 				}
 				else{
 					if(a[i][j-1].ss!=0){
 						a[i][j].ss=a[i][j-1].ss;
 					}
 				}
 			}
 		}
 	}
 	for(ll i=2500;i>=1;i--){
 		for(ll j=2500;j>=1;j--){
 			if(occ[i][j]==1){
 				b[i][j].ff=max(i,max(b[i][j+1].ff,b[i+1][j].ff));
 				b[i][j].ss=max(j,max(b[i][j+1].ss,b[i+1][j].ss));
 			}
 			else{
 				b[i][j].ff=max(b[i][j+1].ff,b[i+1][j].ff);
 				b[i][j].ss=max(b[i][j+1].ss,b[i+1][j].ss);
 			}
 		}
 	}
 	for(ll i=1;i<=n;i++){
 		ll l1=x[i],r1=y[i],l2=x[i],r2=y[i];
 		ll rem=cnt[2500][r1]-cnt[l1-1][r1]+cnt[l2][2500]-cnt[l2][r2-1]-2;
 		ans[i]=n-1-rem;
 		ll act=1;
 		while(rem){
 			act++;
 			ll l3=b[l2+1][r1+1].ff;
 			ll r3=a[l1-1][r2-1].ss;
 			ll l4=a[l1-1][r2-1].ff;
 			ll r4=b[l2+1][r1+1].ss;
 			if(l3!=0) l1=l3;
 			if(r3!=0) r1=r3;
 			if(l4!=0) l2=l4;
 			if(r4!=0) r2=r4;
 			ll yt=cnt[2500][r1]-cnt[l1-1][r1]+cnt[l2][2500]-cnt[l2][r2-1];
 			ans[i]+=((rem-yt)*act);
 			rem=yt;
 		}
 	}
 	for(ll i=1;i<=n;i++){
 		cout << ans[i] << '\n';
 	}

}