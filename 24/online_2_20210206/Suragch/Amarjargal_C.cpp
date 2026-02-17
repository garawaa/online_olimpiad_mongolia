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
vector<int> pocket(2e5, 0), p(2e5), loan(2e5), child(2e5, 0);
vector<bool> vis(2e5, 0);
vector<int> loop;
vector<int> take(2e5, 0);
int dfs(int cur) {
    // debug(cur);
    vis[cur] = 1;
    loop.pb(cur);
    if(vis[p[cur]]) {
        return max(0, loan[cur] - pocket[cur] - take[cur]);
    }
    return max(0, loan[cur] - pocket[cur] - take[cur]) + dfs(p[cur]);
}

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int person, money;
        cin >> person >> money;
        person--;
        loan[i] = money;
        p[i] = person;
        child[person]++;
    }
    int ans = 0;
    queue<int> poor;
    for(int i = 0; i < n; i++) {
        if(child[i] == 0) {
            poor.push(i);
        }
    }
    while(!poor.empty()) {
        int i = poor.front();
        poor.pop();
        ans += max(0, loan[i] - pocket[i]);
        child[p[i]]--;
        pocket[p[i]] += loan[i];
        if(child[p[i]] == 0) 
            poor.push(p[i]);
    }
    // cout << ans << "\n";
    // debug(ans);
    for(int i = 0; i < n; i++) {
        if(child[i] > 0) {
            take[p[i]] = loan[i];
        }
    }
    for(int i = 0; i < n; i++) {
        if(child[i] > 0 && !vis[i]) {
            // debug(i);
            // cout << vis[i] << "\n";
            int sum = dfs(i);
            int temp = INF;
            // cout << "loop: ";
            for(int x : loop) {
                // cout << x << " ";
                temp = min(temp, max(0, loan[x] - pocket[x]) + sum - max(0, loan[x] - pocket[x] - take[x]));
            }
            // cout << "\n";
            ans += temp;
            loop.clear();
        }
    }
    cout << ans << "\n";

    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/