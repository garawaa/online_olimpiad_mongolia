#include <cassert>
#include <cstdio>
#include <cstring>

#include <iostream>

void it_set( int *it, int maxit, long long *d, int i ) {
  i += maxit;
  for (i >>= 1; i >= 1; i >>= 1)
    it[i] = it[i + i + (d[it[i + i]] > d[it[i + i + 1]])];
}

const long long inf = (long long)1e18;

int main() {
  //assert(freopen("bank.in", "r", stdin));
  //assert(freopen("bank.out", "w", stdout));

  int n, m;
  assert(scanf("%d%d", &n, &m) == 2);
  int t0[n], a[n], b[n];
  for (int i = 0; i < n; i++)
    assert(scanf("%d%d%d", &t0[i], &a[i], &b[i]) == 3);

  long long t[n + 1], ans[n], manager_free = 0;
  int state[n], q[n], use[n], ql = 0, qr = 0;
  for (int i = 0; i < n; i++) {
    t[i] = t0[i];
    ans[i] = -1;
    state[i] = 0;
  }
  t[n] = inf;
  int next[m], free = m - 1;
  for (int i = 0; i < m; i++)
    next[i] = i - 1;
  int it[3 * n], maxit = 1;
  while (maxit < n)
    maxit *= 2;
  for (int i = 0; i < 3 * n; i++)
    it[i] = n;
  for (int i = 0; i < n; i++) {
    it[maxit + i] = i;
    it_set(it, maxit, t, i);
  }
  while (1) {
    int u = it[1];
    if (t[u] == inf)
      break;
    switch (state[u]) {
      case 0: {
        if (free == -1 && a[u]) {
          q[qr++] = u;
          t[u] = inf;
          it_set(it, maxit, t, u);
        } else {
          state[u] = 1;
          t[u] = t[u] + a[u];
          it_set(it, maxit, t, u);
          use[u] = -1;
          if (a[u])
            use[u] = free, free = next[free];
        }
        break;
      }
      case 1: {
        if (use[u] + 1) {
          next[use[u]] = free;
          free = use[u];
          if (ql < qr) {
            t[q[ql]] = t[u];
            it_set(it, maxit, t, q[ql++]);
          }
        }
        state[u] = 2;
        if (b[u]) {
          if (manager_free < t[u])
            manager_free = t[u];
          manager_free += b[u];
          ans[u] = manager_free;
          t[u] = inf;
        } else {
          ans[u] = t[u];
          t[u] = inf;
        }
        it_set(it, maxit, t, u);
        break;
      }
      default:
        assert(0);
    }
  }

  for (int i = 0; i < n; i++)
    std::cout << ans[i] << std::endl;

  return 0;
}

