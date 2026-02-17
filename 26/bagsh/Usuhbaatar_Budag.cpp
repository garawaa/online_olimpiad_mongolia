#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	string paper[27], a, b;
	bool m[256] = {false};
	char c;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> paper[i];

	a = paper[0];
	b = paper[1];
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	if (a != b) {
		a = paper[2];
		sort(a.begin(), a.end());
	}

	int y = -1;
	for (int i = 0; i < n; i++) {
		b = paper[i];
		sort(b.begin(), b.end());
		if (a != b) {
			y = i;
			break;
		}
	}

	int x = -1;
	for (int i = 0; i < n; i++) {
		b = "";
		for (int j = 0; j < n; j++)
			b += paper[j][i];
		sort(b.begin(), b.end());
		if (a != b) {
			x = i;
			break;
		}
	}

	b = paper[y];

	for (int i = 0; i < n; i++)
		m[a[i]] = true;

	for (int i = 0; i < n; i++)
		m[b[i]] = false;

	for (int i = 0; i < n; i++)
		if (m[a[i]]) {
			c = a[i];
		}

	cout << y + 1 << " " << x + 1 << " " << c << endl;

	return 0;
}