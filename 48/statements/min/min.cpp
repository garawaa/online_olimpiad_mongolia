/**
 *    author:  tourist
 *    created: 05.06.2021 17:07:52       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  //cin >> tt;
  //for (int qq = 1; qq <= tt; qq++) 
  {
    //cout << "Case #" << qq << ": ";
    string s;
    cin >> s;
    int len = (int) s.size();
    if (len % 2 == 1) {
      sort(s.begin(), s.end());
      for (int i = 0; i < (int) s.size(); i++) {
        if (s[i] != '0') {
          swap(s[0], s[i]);
          break;
        }
      }
      int big = (len + 1) / 2;
      long long x = 0;
      for (int i = 0; i < big; i++) {
        x = x * 10 + (int) (s[i] - '0');
      }
      long long y = 0;
      for (int i = 0; i < len - big; i++) {
        y = y * 10 + (int) (s[len - 1 - i] - '0');
      }
      cout << abs(x - y) << '\n';
    } else {
      vector<int> cnt(10);
      for (char c : s) {
        cnt[(int) (c - '0')] += 1;
      }
      long long ans = (long long) 9e18;
      bool all_even = true;
      for (int d = 0; d < 10; d++) {
        all_even &= (cnt[d] % 2 == 0);
      }
      if (all_even) {
        {cout << 0 << '\n'; return 0;}
       // continue;
      }
      for (int d1 = 0; d1 < 10; d1++) {
        if (cnt[d1] > 0) {
          --cnt[d1];
          for (int d2 = 0; d2 < d1; d2++) {
            if (cnt[d2] > 0) {
              --cnt[d2];
              auto backup = cnt;
              vector<int> pairs;
              for (int d = 9; d >= 0; d--) {
                while (cnt[d] >= 2) {
                  cnt[d] -= 2;
                  pairs.push_back(d);
                }
              }
              int sz = (int) pairs.size();
              vector<int> rm;
              for (int t = 0; t < (1 << sz); t++) {
                long long x = 0;
                long long y = 0;
                bool any = false;
                bool err = false;
                rm.clear();
                for (int i = 0; i < sz; i++) {
                  if (t & (1 << i)) {
                    if (pairs[i] == 0 && !any) {
                      err = true;
                      break;
                    }
                    x = x * 10 + pairs[i];
                    y = y * 10 + pairs[i];
                    any = true;
                  } else {
                    rm.push_back(pairs[i]);
                    rm.push_back(pairs[i]);
                  }
                }
                if (err) {
                  continue;
                }
                if (!any && d2 == 0) {
                  continue;
                }
                x = x * 10 + d1;
                y = y * 10 + d2;
                for (int d = 0; d < 10; d++) {
                  for (int i = 0; i < cnt[d]; i++) {
                    rm.push_back(d);
                  }
                }
                sort(rm.begin(), rm.end());
                assert(rm.size() % 2 == 0);
                for (int i = 0; i < (int) rm.size() / 2; i++) {
                  x = x * 10 + rm[i];
                }
                for (int i = 0; i < (int) rm.size() / 2; i++) {
                  y = y * 10 + rm[(int) rm.size() - 1 - i];
                }
                ans = min(ans, abs(x - y));
              }
              cnt = backup;
              ++cnt[d2];
            }
          }
          ++cnt[d1];
        }
      }
      cout << ans << '\n';
      //cout << ans << '\n';
    }
  }
  return 0;
}
