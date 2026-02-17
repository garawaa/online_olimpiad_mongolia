#include <bits/stdc++.h>
using namespace std;

#define int long long

#pragma GCC optimize("O3", "Ofast")
#pragma target("avx2")

int main() {
	int n, k;
	cin >> n >> k;

	int m = sqrt(n);
	vector<int> a;

	for(int i = 0; i <= m + 1; i++) {
		int r = i * i;
		int x = n - r;
		if(0 < x)
			a.push_back(x);
	}

	m = a.size();
	vector<int> b(m, 0);
	for(int i = 0; i < k; i++)
		b[i] = 1;
	reverse(b.begin(), b.end());

	if(m < k) {
		cout << "NO\n";
		return 0;
	}

	int mn = 0;
	for(int i = 0; i < k - 1; i++)
		mn += a[m - 1 - i];

	int st = 0;
	for(; st < m - k - 1; st++)
		if(a[st] + mn <= n)
			break;

	do {
		int sum = 0;
		for(int i = st; i < m; i++)
			sum += a[i] * b[i];

		if(sum == n) {
			cout << "YES\n";
			for(int i = 0; i < m; i++)
				if(b[m - 1 - i])
					cout << a[m - 1 - i] << ' ';
			cout << endl;
			return 0;
		}

		// if(sum > n) break;
	} while(next_permutation(b.begin() + st, b.end()));

	cout << "NO\n";
	return 0;
}
