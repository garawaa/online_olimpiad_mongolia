#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__);fflush(stderr);
#else
	#define eprintf(...) 42
#endif

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
	return (ull)rng() % B;
}

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

const int N = 200200;
int n, m, s;
int sz;
pii ev[N];
set<int> setik;

int main()
{
	startTime = clock();

	scanf("%d%d%d", &n, &m, &s);
	/*
	if (n < m) {
		printf("0\n");
		return 0;
	}
	*/
	for (int i = 0; i < m; i++) {
		int x;
		scanf("%d", &x);
		if (setik.count(x)) continue;
		setik.insert(x);
		int l = max(0, x - m);
		int r = min(n - m + 1, x);
		ev[sz++] = mp(l, -1);
		ev[sz++] = mp(r, 1);
	}
	sort(ev, ev + sz);
	int ans = 0;
	for (int i = 0; i < sz - 1; i++) {
		m += ev[i].second;
		if (m <= s) ans += ev[i + 1].first - ev[i].first;
	}
	printf("%d\n", ans);

	return 0;
}
