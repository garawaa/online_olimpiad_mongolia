#include <iostream>
#include <algorithm>

typedef long long ll;

using namespace std;

int n;
bool flag = false;
ll L, x[600001], half;

int search(long long z) {
	int l = 0, r = 2 * n;
	while (r - l > 1) {
		int m = ((l + r) >> 1);
		if (x[m] > z) r = m;
		else l = m;
	}
	return l;
}

int main() {
	cin >> n >> L;
	if (L % 2 == 1) {
		half = L;
		L = (L << 1);
		flag = true;
	} else {
		half = (L >> 1);
	}

	for (int i = 0; i < n; i++) {
		cin >> x[i];
		if (flag) x[i] *= 2;
		x[i + n] = x[i] + L;
	}
	sort(x, x + 2 * n);
	
	ll ans = 1LL * n * (n - 1) * (n - 2) / 6;
	
	int k, k1, k2;
	for (int i = 0; i < n; i++) {
		k1 = search(x[i]);
		k2 = search(x[i] + half);
		if (x[k2] != x[i] + half) k2++;
		k = k2 - k1 - 1;
		ans -= 1LL * k * (k - 1) / 2;
	}

	cout << ans << endl;

	return 0;
}