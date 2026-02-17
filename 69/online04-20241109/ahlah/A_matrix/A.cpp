#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
#define ff first
#define ss second
#define all(s) s.begin(),s.end()
#define rall(s) s.rbegin(),s.rend()
#define int ll

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int p,n,m;
    cin>>p>>n>>m;
    int a[n+5][m+5];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    int b[n+5][m+5];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            b[i][j]=a[i][j]/p*p;
        }
    }
    vector<int>r(n+1,0),c(m+1,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            r[i]+=a[i][j];
            r[i]-=b[i][j];
            c[j]+=a[i][j];
            c[j]-=b[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        r[i]/=p;
    }
    for(int i=1;i<=m;i++){
        c[i]/=p;
    }
    for(int i=1;i<=n;i++){
        vector<pair<int,int>>v;
        for(int j=1;j<=m;j++){
            if(c[j]>0){
                v.pb({c[j],j});
            }
        }
        sort(rall(v));
        if(v.size()<r[i]){
            cout<<-1;
            return 0;
        }
        for(int j=0;j<r[i];j++){
            b[i][v[j].ss]+=p;
            c[v[j].ss]--;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<b[i][j];
            if(j<m) cout<<' ';
        }
        cout<<"\n";
    }
}
