#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define pp push
#define MOD 1000000007
#define INF 1e18
#define N 100005
#define M 2000000
typedef long long ll;
using namespace std;
string s[51][1501];
unordered_map<string,ll>dp;
unordered_map<string,bool>lol;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,k;
	cin >> n >> k;
	for(int i=1;i<=k;i++){
		cin >> s[1][i];
		dp[s[1][i]]++;
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<=k;j++){
			cin >> s[i][j];
			string a="",b="";
			for(int p=1;p<i;p++){
				a=a+s[i][j][p];
			}
			for(int p=0;p<i-1;p++){
				b=b+s[i][j][p];
			}
			// cout << a << " " << b << '\n';
			dp[s[i][j]]+=dp[a];
			if(dp[s[i][j]]>=MOD) dp[s[i][j]]%=MOD;
			if(a!=b) dp[s[i][j]]+=dp[b];
			if(dp[s[i][j]]>=MOD) dp[s[i][j]]%=MOD;
		}
	}
	ll ans=0;
	for(int i=1;i<=k;i++){
		if(lol[s[n][i]]==0){
			lol[s[n][i]]=1;
			ans+=dp[s[n][i]];
			if(ans>=MOD) ans%=MOD;
		}
	}
	cout << ans;

	
 
}