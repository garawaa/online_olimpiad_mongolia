#include <bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;
string a,b;
vector<string>v;
unordered_map<string,set<string> >m;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int o=0;
	while(cin >> a){
		int coma=0;
		string x="",name="";
		for(int j=0;j<a.size();j++){
			// cout << coma << ' ';
			if(a[j]==','){
				coma++;
				if(coma==5){
					// cout << x << '\n';
					if(m[x].size()==0){
						v.pb(x);
					}
					m[x].insert(name);
				}	
				continue;
			}
			if(coma==4){
				x=x+a[j];
			}
			if(coma==2) name=name+a[j];
		}
		a.clear();
		cin >> b;
	}
	vector<pair<int,string> >ans;
	for(string i:v){
		ans.pb({-m[i].size(),i});
	}
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++){
		cout << ans[i].second << ' ' << -ans[i].first << '\n';
	}
}