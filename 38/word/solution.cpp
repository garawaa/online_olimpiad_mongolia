#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

int main() {
  string a, b;
  getline(cin, a);
  getline(cin, b);

  vector<int> count[2];
  count[0].resize(26);
  count[1].resize(26);

  for (int i = 1; i < a.size(); i++) {
    count[0][a[i]-'a']++;
  }
  for (int i = 0; i < b.size() - 1; i++) {
    count[1][b[i]-'a']++;
  }

  long long ans = a.size() * 1LL * b.size();
  for (int i = 0; i < 26; i++)
    ans -= count[0][i] * 1LL * count[1][i];
  cout << ans << endl;
  return 0;
}
