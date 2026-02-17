#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory.h>
#include <cassert>

using namespace std;

const int md = 1000000007;

inline void add(int &a, int b) {
  a += b;
  if (a >= md) a -= md;
}

const int N = 100010;

int a[N];
int f[N][4];

int main() {
  //freopen("tiling.in", "r", stdin);
 // freopen("tiling.out", "w", stdout);
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++) {
    a[i] = 0;
  }
  for (int i = 0; i < k; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    x--; y--;
    a[x] |= (1 << y);
  }
  memset(f, 0, sizeof(f));
  f[0][0] = 1;
  for (int i = 0; i <= n; i++) {
    add(f[i][3], f[i][0]);
    for (int j = 0; j < 4; j++) {
      if (j & a[i]) {
        continue;
      }
      for (int k = 0; k < 4; k++) {
        if (((3 - j - a[i]) & k) == k) {
          add(f[i + 1][k], f[i][j]);
        }
      }
    }
  }
  printf("%d\n", f[n][0]);
  return 0;
}
