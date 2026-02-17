#include <iostream>

using namespace std;

int g[4][4];

int main() {
	string a, b;
	cin >> a >> b;
	int n = a.size();

	for (int i = 0; i < n; i++) {
		if (a[i] != b[i]) {
			g[a[i] - 'A'][b[i] - 'A']++;
		}
	}

	long long ans = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i != j) {
				int mn = min(g[i][j], g[j][i]);
				ans += 1 * mn;
				g[i][j] -= mn;
				g[j][i] -= mn;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (i != j && i != k && j != k) {
					int mn = min(g[i][j], min(g[j][k], g[k][i]));
					ans += 2 * mn;
					g[i][j] -= mn;
					g[j][k] -= mn;
					g[k][i] -= mn;
				}
			}
		}
	}
	int mn = g[0][1] + g[0][2] + g[0][3];
	ans += 3 * mn;
	cout << ans << endl;
	return 0;
}