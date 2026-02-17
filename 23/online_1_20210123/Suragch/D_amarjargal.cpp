#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ss second
#define ff first
#define pb push_back
#define pii pair<int, int>
#define INF INT_MAX
#define debug(n) cout << #n << " = " << n << "\n";
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

using namespace std;

const ll MOD = 1e9 + 7;

bool cus(pair<int, string> a, pair<int, string> b) {
    if(a.ff > b.ff) {
        return 1;
    }
    if(a.ff == b.ff) {
        return a.ss < b.ss;
    }
    return 0;
}
int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string s;
    unordered_map<string, unordered_set<string> > m;
    while(getline(in, s)) {
        vector<string> info;
        // int cnt = 0;
        string str = "";
        for(char c : s) {
            if(c == ',') {
                info.pb(str);
                str = "";
            } else {
                str += c;
            }
        }
        m[info[4]].insert(info[2]);
    }
    vector<pair<int, string> > ans;
    for(auto el : m) {
        ans.pb({el.ss.size(), el.ff});
    }
    sort(ans.begin(), ans.end(), cus);
    for(auto el : ans) {
        out << el.ss << " " << el.ff << "\n";
    }


    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/