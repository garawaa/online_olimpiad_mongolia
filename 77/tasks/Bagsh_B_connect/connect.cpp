#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void dfs(const vector<vector<int>>& edges, vector<int>& component, const int currv, const int id) {
  for(int child: edges[currv]) {
    if(component[child] != id) {
      component[child] = id;
      dfs(edges, component, child, id);
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> edges(n);
  for(int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  vector<int> component(n);
  iota(component.begin(), component.end(), 0);
  for(int i = 0; i < n; i++) {
    if(component[i] == i) {
      dfs(edges, component, i, i);
    }
  }
  if(component[0] == component[n-1]) {
    cout << "0\n";
    return;
  }
  vector<vector<int>> componentToVertices(n);
  for(int i = 0; i < n; i++) {
    componentToVertices[component[i]].push_back(i);
  }
  long long ans = 1e18;
  vector<long long> srccost(n, 1e9);
  vector<long long> dstcost(n, 1e9);
  int srcidx = 0;
  int dstidx = 0;
  for(int i = 0; i < n; i++) {
    while(srcidx < componentToVertices[component[0]].size()) {
      srccost[component[i]] = min(srccost[component[i]], (long long)abs(i - componentToVertices[component[0]][srcidx]));
      if(componentToVertices[component[0]][srcidx] < i) srcidx++;
      else break;
    }
    if(srcidx) srcidx--;
    while(dstidx < componentToVertices[component[n-1]].size()) {
      dstcost[component[i]] = min(dstcost[component[i]], (long long)abs(i - componentToVertices[component[n-1]][dstidx]));
      if(componentToVertices[component[n-1]][dstidx] < i) dstidx++;
      else break;
    }
    if(dstidx) dstidx--;
  }
  for(int i = 0; i < n; i++) ans = min(ans, srccost[i]*srccost[i] + dstcost[i]*dstcost[i]);
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  for(int i = 0; i < t; i++) {
    solve();
  }
  return 0;
}
