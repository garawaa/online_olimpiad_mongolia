#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

#define PI 3.1415926535897932384626

int main() {
 // freopen("input.0", "r", stdin);
  //freopen("sight.out", "w", stdout);
  int N, R;
  scanf("%d%d", &N, &R);
  vector<pair<double, double> > A;
  for(int i = 0; i < N; i++) {
    int x, y; scanf("%d%d", &x, &y);
    double alpha = acos(R / sqrt(1.0 * x * x + 1.0 * y * y));
    double a0 = atan2(y, x) - alpha;
    if(a0 < 0) a0 += 2 * PI;
    A.push_back(make_pair(a0, a0 + 2 * alpha));
  }
  sort(A.begin(), A.end());

  int result = 0;
  priority_queue<double, vector<double>, greater<double> > q;
  for(int iters = 0; iters < 2; iters++) {
    for(int i = 0; i < N; i++) { 
      while(!q.empty() && q.top() < A[i].first) {
        q.pop();
      }

      if(iters == 1) {
        result += q.size();
      }

      q.push(A[i].second);
      A[i].first += 2 * PI;
      A[i].second += 2 * PI;
    }
  }
  printf("%d\n", result);
  return 0;
}

//http://www.usaco.org/index.php?page=viewproblem2&cpid=347