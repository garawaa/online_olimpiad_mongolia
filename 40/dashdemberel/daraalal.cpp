#include <iostream>
#include <cstdio>
#include <map>
#include <set>

using namespace std;

int A[100010];

int main() {
  //freopen("lineup.in", "r", stdin);
 // freopen("lineup.out", "w", stdout);

  int N, K; cin >> N >> K;
  for(int i = 0; i < N; i++) {
    cin >> A[i];
  }

  int res = 0;
  int nz_cnt = 0;
  map<int, int> cnt;
  for(int i = 0, j = 0; i < N; i++) {
    int& ci = cnt[A[i]];
    if(ci == 0) nz_cnt++;
    ci++;

    for(; nz_cnt > K + 1; j++) {
      int& cj = cnt[A[j]];
      --cj;
      if(cj == 0) nz_cnt--;
    }

    res = max(res, ci);
  }
  cout << res << endl;

  return 0;
}