#include <cassert>
#include <cstdio>

#include <algorithm>
#include <unordered_map>

using namespace std;

const int modulo = (int)1e9 + 7;
int half = (modulo + 1) / 2; // we can divide in modular arithmetic
int mul ( int a, int b ) {
  return ((long long)a * (long long)b) % modulo;
}
int add ( int a, int b ) {
  int r = a + b;
  return r < modulo ? r : r - modulo;
}

int main () {
  int n;
  assert (scanf ("%d", &n) == 1);
  int a[n];
  for (int i = 0; i < n; i++)
    assert (scanf ("%d", &a[i]));

  /*
   * jump: next equal (or -1)
   * next: next greater (or n)
   * prev: previous greater (or -1)
   */
  int next[n], prev[n], jump[n];
  int stack[n], k = 0;
  for (int i = 0; i < n; i++) {
    while (k && a[stack[k - 1]] <= a[i])
      k--;
    prev[i] = k == 0 ? -1 : stack[k - 1];
    stack[k++] = i;
  }
  k = 0;
  for (int i = n - 1; i >= 0; i--) {
    while (k && a[stack[k - 1]] <= a[i])
      k--;
    next[i] = k == 0 ? n : stack[k - 1];
    stack[k++] = i;
  }
  unordered_map <int, int> pos;
  for (int i = n - 1; i >= 0; i--) {
    if (pos.count (a[i]))
      jump[i] = pos[a[i]];
    else
      jump[i] = -1;
    pos[a[i]] = i;
  }

  int ans = 0;

  for (auto it: pos) {
    // max (..) = max (..) = T = it.first
    int sum = 0;
    for (int i = it.second; jump[i] != -1; i = jump[i]) {
      int j = jump[i];
      if (next[i] >= j) { // case #1: prev_i..[..T..(a[i]=T)..]..[..(a[j]=T)..T..]..next_j
        int t = i - prev[i];
        t = mul (t, j - i + 1);
        t = mul (t, j - i);
        t = mul (t, half);
        t = mul (t, next[j] - j);
        ans = add (ans, t);
      } else { // case #2: prev_i..[..T..(a[i]=T)..].X.[..(a[j]=T)..T..]..next_j
        int t = i - prev[i];
        t = mul (t, next[i] - i);
        t = mul (t, j - prev[j]);
        t = mul (t, next[j] - j);
        ans = add (ans, t);
      }
      // case #3: ..[..T..T..]..T..(a[i]=T)... ..[..(a[j]=T)..T..]..
      int r = sum;
      r = mul (r, j - max (i, prev[j]));
      r = mul (r, next[j] - j);
      ans = add (ans, r);
      int t = i - prev[i];
      t = mul (t, min (next[i], j) - i);
      sum = add (sum, t);
    }
  }

  printf ("%d\n", ans);
  return 0;
}

