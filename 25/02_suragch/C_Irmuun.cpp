#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define ff first
#define ss second
ll a,b,a1,b1,c,d=0,e=0,i,f=0,g=0,j,k=0,l=0,r,z,m,h,p[1001],mod=1000000007,mod1=998244353;
string t,x,q,s1,t1;
ll df[1001],bf[1001];
//double ;
vector<ll>v;
vector<ll>u,w;
vector<ll>dv[1001];
//vector<string>;
set<string>y;
void dfs(ll x){
	if(bf[x]%2==0){
		df[x]=-1;
		if(dv[x].size()==0){
			df[x]=p[x];
			return;
		}
		for(ll i=0;i<dv[x].size();i++){
	        dfs(dv[x][i]);
	        df[x]=max(df[x],df[dv[x][i]]);
	    }
	}
	else{
		df[x]=1;
		if(dv[x].size()==0){
			df[x]=p[x];
			return;
		}
		for(ll i=0;i<dv[x].size();i++){
	        dfs(dv[x][i]);
	        df[x]=min(df[x],df[dv[x][i]]);
	    }
	}
}
void bfs(ll x){
	for(ll i=0;i<dv[x].size();i++){
		if(bf[dv[x][i]]==0){
			bf[dv[x][i]]=bf[x]+1;
			bfs(dv[x][i]);
		}
	}
}
ll fastPow(ll a,ll b){
    ll d=1;
    while(b>0){
        if(b%2==1){
            d=d*a%mod;
        }
        b/=2;
        a=a*a%mod;
    }
    return d;
}
int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    cin>>a;
    char s;
    p[1]=0;
    for(i=2;i<=a;i++){
    	cin>>s>>b;
    	dv[b].pb(i);
    	if(s=='L'){
    		cin>>p[i];
		}
	}
	bf[1]=0;
	bfs(1);
	dfs(1);
	if(df[1]==1){
		cout<<"+1";
	}
	else{
		cout<<df[1];
	}
}
