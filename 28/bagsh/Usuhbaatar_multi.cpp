#include <cstring>
#include <iostream>

using namespace std;

int t, n, a[101];
int dp[101][101];
bool vis[101][101];

int solve(int l, int r) {
	if (l + 1 >= r) return 0;
	if (vis[l][r]) return dp[l][r];

	int ret = 1e9;

	for (int i = l + 1; i < r; i++) {
		int temp = solve(l, i) + solve(i, r) + a[l] * a[i] * a[r];
		ret = min(ret, temp);
	}
	
	
	vis[l][r] = true;
	return dp[l][r] = ret;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];

		cout << solve(1, n) << endl;
		memset(vis, 0, sizeof vis);
	}

	return 0;
}