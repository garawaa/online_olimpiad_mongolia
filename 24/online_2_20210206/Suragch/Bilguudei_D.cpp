#include <bits/stdc++.h>
#define pb push_back
#define ll long long
#define ff first
#define ss second
#define N 200001
using namespace std;
int x[4][4];
int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);
	string a,b;
	cin >> a >> b;
	for(int i=0;i<a.size();i++){
		x[a[i]-'A'][b[i]-'A']++;
	}
	int ans=0;
	int k=min(x[0][1],x[1][0]);
	ans+=k;
	x[0][1]-=k;
	x[1][0]-=k;
	k=min(x[0][2],x[2][0]);
	ans+=k;
	x[0][2]-=k;
	x[2][0]-=k;
	k=min(x[0][3],x[3][0]);
	ans+=k;
	x[0][3]-=k;
	x[3][0]-=k;
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			k=min(x[0][i],x[j][0]);
			ans+=k;
			x[j][i]+=k;
		}
	}
	k=min(x[1][2],x[2][1]);
	ans+=k;
	x[1][2]-=k;
	x[2][1]-=k;
	k=min(x[1][3],x[3][1]);
	ans+=k;
	x[1][3]-=k;
	x[3][1]-=k;
	for(int i=2;i<=3;i++){
		for(int j=2;j<=3;j++){
			k=min(x[1][i],x[j][1]);
			ans+=k;
			x[j][i]+=k;
		}
	}
	ans+=x[2][3];
	cout << ans;
}