#include <cassert>
#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main(void)
{
  map<char, int> letterid {{'A', 0}, {'C', 1}, {'B', 2}, {'D', 3}};
  string dna1, dna2;
  while (cin >> dna1 >> dna2)
  { 
    int len = dna1.length();
    vector<vector<int>> ecnt(4, vector<int>(4));
    for (int i = 0; i < len; ++i) {
      int l1 = letterid[dna1[i]];
      int l2 = letterid[dna2[i]];
      ++ecnt[l1][l2];
    }
    int result = 0;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        if(i != j && ecnt[i][j] >= ecnt[j][i]) {
          result += ecnt[j][i];
          ecnt[i][j] -= ecnt[j][i];
          ecnt[j][i] = 0;
        }
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        for (int k = 0; k < 4; ++k) {
          if(i == j || i == k || j == k)
            continue;
          int min = std::min(std::min(ecnt[i][j], ecnt[j][k]), ecnt[k][i]);
          result += 2 * min;
          ecnt[i][j] -= min;
          ecnt[j][k] -= min;
          ecnt[k][i] -= min;
        }
    int rest = 0;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        if(i != j)
          rest += ecnt[i][j];
    result += 3 * rest / 4;
    cout << result << endl;
  }
  return 0;
}
