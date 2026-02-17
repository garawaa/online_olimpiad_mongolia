#include <bits/stdc++.h>
#define pb push_back
using namespace std;
vector<int>adj[500001];
int ans=0;
void dfs(int node,int par=-1){
	int res=0;
	for(int i:adj[node]){
		if(i!=par){
			res++;
			dfs(i,node);
		}
	}
	if(par!=-1)ans=ans+max(res-1,0);
	else ans+=(max(res-2,0));
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for(int i=1;i<n;i++){
		int a,b;
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(1);
	cout << ans;
}