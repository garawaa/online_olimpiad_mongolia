#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
pair<int,int> f(int l,int r)
{
    if(l==0 && r==n+1) {return {-2e18,1};}
    if(l==0)
    {
        return {1-r,1};
    }
    if(r==n+1)
    {
        return {l-n,n};
    }
    if(r==l+1) {return {1,0};}
    return {l-(l+r)/2,(l+r)/2};
}
int32_t main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int k;cin>>n>>k;
    map<int,int> v;
    set<int> u={0,n+1};
    set<pair<int,int> > goodp={f(0,n+1)};
    auto add=[&](int pos)
    {
        set<int>::iterator it=u.upper_bound(pos);int r=(*it);--it;int l=(*it);
        u.insert(pos);
        goodp.erase(f(l,r));goodp.insert(f(l,pos));goodp.insert(f(pos,r));
    };
    auto del=[&](int pos)
    {
        u.erase(pos);
        set<int>::iterator it=u.upper_bound(pos);int r=(*it);--it;int l=(*it);
        goodp.erase(f(l,pos));goodp.erase(f(pos,r));goodp.insert(f(l,r));
    };
    int cyc=1;
    for(int i=1;i<=k;++i)
    {
        string s;cin>>s;
        if(s[0]=='+')
        {
            pair<int,int> h=(*goodp.begin());
            if(h.first==1) assert(false);
            v[cyc]=h.second;++cyc;cout<<h.second<<endl;
            add(h.second);
        }
        else
        {
            s.erase(s.begin());int x=stoll(s);
            del(v[x]);
        }
    }
    return 0;
}