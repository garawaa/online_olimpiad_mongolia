#include <bits/stdc++.h>

using namespace std;
unordered_map<string, int> x;
unordered_map<string, int > y; 
int n;
string s[20005];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int i, j, k;
  cin >> n;
  for(i = 1; i <= n; i++){
    cin >> s[i];
    y.clear();
    for(j = 0; j < s[i].size(); j++){
        string st;
        for(k = j; k < s[i].size(); k++){
          st += s[i][k];
          if(y[st] == 0) { 
            x[st]++;
            y[st] = 1;
          }
        }
    }
  }
  int s1=0;
  for(i = 1; i <= n; i++){
      s1 += x[s[i]] - 1;
  }
  cout<<s1;
  return 0;
}
