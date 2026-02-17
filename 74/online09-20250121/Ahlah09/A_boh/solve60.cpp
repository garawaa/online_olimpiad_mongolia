#include <fstream>
#include <vector>
#include <cassert>
#include <cstdio>

using namespace std;

const int maxN = 100000;

int main () {
  ifstream fin ("input.txt");
  int n;
  assert (fin >> n);
  assert (1 <= n && n <= maxN);
  n /= 2;
  vector <vector <int> > to (2 * n);
  for (int i = 0; i < 2 * n; ++i) {
    int a, b;
    assert (fin >> a >> b);
    assert (1 <= a && a <= 2 * n);
    assert (1 <= b && b <= 2 * n);
    --a;
    --b;
    to[a].push_back (b);
    to[b].push_back (a);
  }
  int k;
  assert (fin >> k);
  fin.close ();

  vector <bool> u (2 * n);
  vector <int> d (2 * n, 2);
  vector <int> ans;
  while ((int)ans.size () < k) {
    int v = -1;
    for (int i = 0; i < 2 * n; ++i) {
      if (!u[i]) {
        if (v == -1 || d[v] > d[i]) {
          v = i;
        }
      }
    }
    if (v == -1) {
      break;
    }
    ans.push_back (v);
    u[v] = true;
    for (int i = 0; i < (int)to[v].size (); ++i) {
      int w = to[v][i];
      u[w] = true;
      for (int j = 0; j < (int)to[w].size (); ++j) {
        --d[to[w][j]];
      }
    }
  }

  ofstream fout ("output.txt");
  if ((int)ans.size() == k) {
    for (int i = 0; i < k; ++i) {
      fout << (1 + ans[i]);
      if (i + 1 < k) {
        fout << " ";
      }
    }
    fout << endl;
  } else {
    fout << 0 << endl;
  }
  fout.close ();
  return 0;
}
