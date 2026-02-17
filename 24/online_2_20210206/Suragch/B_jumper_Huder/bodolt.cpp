#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using cd = complex<ld>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> v(n);
  ll sum = 0;
  for (int &e : v) {
    cin >> e;
    sum += e;
  }
  vector<bool> dp(sum + 1);
  dp[0] = true;
  for (int i : v) {
    for (int j = sum; j >= i; j--) {
      dp[j] = dp[j] | dp[j - i];
    }
  }
  vector<int> a;
  for (int i = 1; i <= sum; i++) {
    if (!dp[i]) {
      a.push_back(i);
    }
  }
  ll res = 0;
  for (int i = 0; i < a.size(); i++) {
    int j = --upper_bound(a.begin(), a.end(), sum - a[i]) - a.begin();
    if (j >= 0) {
      res += j + 1;
    }
  }
  cout << (sum + 1) * (sum + 2) / 2 - res;
  return 0;
}