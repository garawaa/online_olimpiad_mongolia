#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define ff first
#define ss second
ll a,b,a1,b1,c,d=0,e=0,i,f=0,g=0,j,k=0,l=0,r,z,m,h[1000001],p[1000001],mod=1000000007,mod1=998244353;
string x,q;
ll df[101];
//double ;
vector<ll>v[4];
vector<ll>u,w;
vector<ll>dv[101];
//vector<string>;
set<string>y;
void dfs(ll x){
	for(ll i=0;i<dv[x].size();i++){
		if(df[dv[x][i]]==0){
			df[dv[x][i]]=df[x]+1;
			dfs(dv[x][i]);
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
    for(i=0;i<=1000000;i++){
    	p[i]=0;
    	h[i]=0;
	}
    char s,t;
    for(i=1;i<=a;i++){
    	cin>>b>>c>>d>>e>>f>>g;
    	v[0].pb(min(b,min(d,f))+1);
    	v[1].pb(max(b,max(d,f)));
    	v[2].pb(min(c,min(e,g))+1);
    	v[3].pb(max(c,max(e,g)));
	}
	sort(v[0].begin(),v[0].end());
	d=0;
	p[0]=0;
	for(i=1;i<=1000000;i++){
		while(d<a&&v[0][d]==i){
			d++;
		}
		p[i]=d;
	}
	sort(v[1].begin(),v[1].end());
	d=0;
	for(i=1;i<=1000000;i++){
		while(d<a&&v[1][d]==i){
			d++;
		}
		p[i]-=d;
	}
	sort(v[2].begin(),v[2].end());
	d=0;
	p[0]=0;
	for(i=1;i<=1000000;i++){
		while(d<a&&v[2][d]==i){
			d++;
		}
		h[i]=d;
	}
	sort(v[3].begin(),v[3].end());
	d=0;
	for(i=1;i<=1000000;i++){
		while(d<a&&v[3][d]==i){
			d++;
		}
		h[i]-=d;
	}
	cin>>b;
	while(b--){
		cin>>s>>t>>c;
		if(s=='x'){
			cout<<p[c]<<endl;
		}
		else{
			cout<<h[c]<<endl;
		}
	}
}
