#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <cmath>
#include <set>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <stdint.h>
#include <cstdio>
#include <bitset>
#include <random>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int_fast32_t, int_fast32_t, int_fast32_t> tiii;
typedef vector<vector<int>> vvi;
typedef vector<set<int>> vsi;
typedef unsigned int uint;
const int INF = 1e9 + 10;
const int N = 2e5 + 1000, C = 16;
int MOD = 998244353;




int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	vector<int64_t> a(3, 0); cin >> a[0] >> a[1] >> a[2];
	
	if ((a[0] + a[1] + a[2]) % 3 != 0) {
		cout << "No";
	}
	else {
		cout << "Yes\n";
		int mid = (a[0] + a[1] + a[2]) / 3;
		int cnt = (abs(a[0] - mid) + abs(a[1] - mid) + abs(a[2] - mid)) / 2;
		cout << cnt << '\n';
		if (t == 1) {
			sort(a.begin(), a.end());
			while (a[0] < a[2]) {
				cout << a[0]++ << ' ' << a[2]-- << '\n';
				sort(a.begin(), a.end());
			}
		}
	}
}
