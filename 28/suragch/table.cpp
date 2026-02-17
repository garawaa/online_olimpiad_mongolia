#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
typedef long long ll;
ll val[1000010], grid[310][310];
int valtoind[1000010], c;
ll indtoval[3200], n, m, k;
ll dp[2][310][3200], ans;
int main()
{
	scanf("%lld%lld%lld", &n, &m, &k);
	val[0] = k+1;
	for (ll i = 1; i <= k; i++)
	{
		val[i] = val[i-1];
		while (val[i]*i >= k) val[i]--;
		val[i]++;
		if (val[i] != val[i-1]) c++;
		indtoval[c] = i;
		valtoind[i] = c;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) scanf("%lld", &grid[i][j]);
	}
	dp[0][0][valtoind[1]] = 1;
	for (int f = 0; f < n; f++)
	{
		int i = f%2;
		for (int j = 0; j < m; j++)
		{
			for (int ind = 1; ind <= c; ind++)
			{
				dp[i][j][ind] %= mod;
				ll newval = min(k, indtoval[ind]*grid[f][j]);
				if (newval == k && f == n-1 && j == m-1 && dp[i][j][ind]) ans += dp[i][j][ind];
				// consider going to left and down
				dp[i][j+1][valtoind[newval]] += dp[i][j][ind];
				dp[!i][j][valtoind[newval]] += dp[i][j][ind];
				dp[i][j][ind] = 0;
			}
		}
	}
	ans %= mod;
	printf("%lld\n", ans);
}
