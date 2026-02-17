#include <fstream>
#include <vector>
#include <cassert>
#include <iostream>


using namespace std;

const int maxN = 100000;

int main () {
  ifstream fin ("input.txt");
  int n;
  assert (fin >> n);
  assert (2 <= n && n <= maxN);
  assert(n % 2 == 0);

  vector <vector <int> > to (n);
  for (int i = 0; i < n; ++i) {
    int a, b;
    assert (fin >> a >> b);
    assert (1 <= a && a <= n);
    assert (1 <= b && b <= n);
    --a;
    --b;
    to[a].push_back (b);
    to[b].push_back (a);
  }
  int k;
  assert (fin >> k);
  fin.close ();
  cerr << ":)";
  vector <bool> u (n);
  vector <int> ans;
  for (int i = 0; i < n; ++i) {
    if (u[i]) {
      continue;
    }
    int j = i;
    while (!u[j]) {
      ans.push_back (j);
      u[j] = true;
      if (u[to[j][0]]) {
        j = to[j][1];
      } else {
        j = to[j][0];
      }
    }
  }
  cerr << ans[0] << " " << ans[1];
  ofstream fout ("output.txt");
  if (k <= n / 2) {
    for (int i = 0; i < k; ++i) {
      fout << (1 + ans[2 * i]);
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
