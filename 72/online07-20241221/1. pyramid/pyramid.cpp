#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <functional>
#include <ctime>
#include <unordered_map>
#include <unordered_set>
#include <memory.h>
#include <map>
#include <queue>
#include <set>
#include <limits.h>
#include <stack>

#define x1 fkdslfk
#define x2 fkdslfkd
#define y1 fkdplfk
#define y2 fkdplfkd
#define long long long
//#define MULTITEST

using namespace std;

void precalc() {

}

int n;
unordered_map<int, int> mp;

int solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		mp[a] = max(mp[a], b);
	}
	long ans = 0;
	for (auto it = mp.begin(); it != mp.end(); ++it) {
		ans += it->second;
	}
	printf("%I64d\n", ans);

	return 0;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	freopen("debug.txt", "wt", stderr);
#endif

	precalc();

	int t;
#ifdef MULTITEST
	scanf("%d", &t);
#else
	t = 1;
#endif

	for (int i = 1; i <= t; ++i) {
		solve();
	}

	return 0;
}
