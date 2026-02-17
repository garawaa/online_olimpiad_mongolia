#include<bits/stdc++.h>

using namespace std;
using ll = long long ;
ll Unite(ll& lo, ll& hi, ll x, ll y) {
	if ( x > hi || lo > y) return -1;
	lo = max(lo, x);
	hi = min(hi, y);
	return 1;
}
void Solve() {
	ll n, i, ans, lo, j, hi, x, y;
	cin >> n;
	
	ll a[n + 2], b[n + 2];
	lo = 0;
	hi = 1e9;
	for (i = 1; i <= n; i ++) cin >> a[i];
	for (i = 1; i <= n; i ++) cin >> b[i];
	
	for (i = 1; i <= n; i ++) {
		if ( Unite(lo, hi, a[i], b[i]) == -1) break;
	}
	if (i == n + 1) {
		cout << 0 << endl;
		for (i = 1; i <= n; i ++) {
			cout << lo << " ";
		}
		cout << endl;
		return ;
	}
	if ( a[i] < lo && b[i] < lo) {
		x = lo;	
	}
	else x= hi;
	vector < ll > v;
	for (j = 1; j < i; j ++) {
		v.push_back(x);
	}
	ans = 0;
	for (j = i; j <= n; j ++) {
		if ( x >= a[j] && x <= b[j]) {
			v.push_back(x);
			continue;
		}
		if ( abs(a[j] - x) <= abs(b[j] - x)) ans = ans + abs(a[j] - x), x= a[j];
		else ans = ans + abs(b[j] - x), x = b[j];
		v.push_back(x);
	}
	cout << ans << endl;
	for (j = 0; j < v.size(); j ++) cout << v[j] << " ";
	cout << endl;
}

int main() {
//	freopen("moocast.in", "r", stdin);
//	freopen("moocast.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll t;

	cin >> t;
	
	while (t --) {
		Solve();
	}
}

