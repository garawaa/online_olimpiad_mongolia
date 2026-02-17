#include <iostream>
  #include <cstdio>
  #include <vector>
  #include <algorithm>
  #include <cmath>
  using namespace std;
   
  typedef pair<int, int> point;
  #define X first
  #define Y second
   
  const double pi = 2*acos(0.0);
  int n, R;
  vector<point> points;
   
  void input() {
      cin>>n>>R;
      points.resize(n);
      int x,y;
      for (int i=0;i<n;i++) {
          cin>>x>>y;
          points[i] = point(x,y);
      }   
  }
  bool cw(const point &a, const point &b, const point &c) {
      return a.X * (b.Y - c.Y) + b.X * (c.Y - a.Y) + c.X * (a.Y - b.Y) < 0;
  }
  vector<point> convexHull(vector<point> &p) {
   
      int k = 0;
      sort(p.begin(), p.end());
      vector<point> q(n*2); // ?
      for (int i=0; i<n; q[k++] = p[i++])
          for ( ; k>=2 && !cw(q[k-2],q[k-1],p[i]); --k)
              ;
      for (int i=n-2, t=k; i>=0; q[k++] = p[i--])
          for ( ; k > t && !cw(q[k-2],q[k-1],p[i]); --k)
              ;
      q.resize(k-1 - (q[0] == q[1]));
      return q;
  }
  double dist(point &a, point &b) {
      return sqrt(0.0 + (a.X - b.X)*(a.X - b.X) + (a.Y - b.Y)*(a.Y - b.Y));
  }
  void solve() {
      vector<point> hull = convexHull(points);
      double res = 2*pi*R;
      for (int i=0; i<hull.size();++i) {
          res += dist(hull[i], hull[(i+1)%hull.size()]);
      }
      printf("%0.0f",res);
  }
  int main() {
      //freopen("input.txt","r",stdin);
     // freopen("output.txt","w",stdout);
      input();
      solve();
  }