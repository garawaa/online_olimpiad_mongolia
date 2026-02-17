#include <vector>
#include <iostream>

using namespace std;

bool d[2000001];

int main() {
	int n, sum = 0, p[201];
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}

	d[0] = true;
	for (int i = 0; i < n; i++) {
		for (int j = sum; j >= 0; j--) {
			if (d[j]) {
				d[j + p[i]] = true;
			}
		}
		sum += p[i];
	}

	long long ans = 0, cnt = 0;
	for (int i = 0; i <= sum; i++) {
		if (d[i]) {
			ans += (i + 1);
			cnt++;
		}
	}
	cout << 2 * ans - cnt * (cnt + 1) / 2 << endl;
	return 0;
}