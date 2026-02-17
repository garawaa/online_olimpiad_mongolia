#include <iostream>
#include <algorithm>

using namespace std;

int n, m, s, l;
int a[100001];
int b[100001];


int main() {
	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++)
		cin >> a[i];

	sort(a + 1, a + m + 1);
	l = 1; b[0] = 0; b[1] = a[1];
	for (int i = 2; i <= m; i++) {
		if (a[i] != a[i - 1]) {
			l++; b[l] = a[i];
		}
	}

	int ans = 0;
	int need = m - s;
	for (int i = 1, j = need; j <= l; i++, j++) {
		int start = max(b[j] - m + 1, b[i - 1] + 1);
		int end = min(b[i], n - m + 1);
		if (end < start) continue;
		ans += (end - start + 1);
	}
	cout << ans << endl;
	return 0;
}