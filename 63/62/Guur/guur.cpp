#include <cstdio>
#include <cassert>
#include <cstring>

const int maxn = 310;

int x, a, y, b, l;
int f[maxn][maxn];

inline void relax( int &a, int b ) { if (a < b) a = b; }

bool solve( int w )
{
  memset(f, -1, sizeof(f));
  f[x][y] = 0;
  for (int i = x; i >= 0; i--)
    for (int j = y; j >= 0; j--)
      if (f[i][j] != -1)
      {
        int val = f[i][j] + 1;
        int ti = 0;
        while (ti <= i && ti * a < w + a)
        {
          int tj = (w - ti * a + b - 1)/ b;
          if (tj <= j)
            relax(f[i - ti][j - tj], val);
          ti++;
        }
      }
  for (int i = 0; i <= x; i++)
    for (int j = 0; j <= y; j++)
      if (f[i][j] >= l)
        return true;
  return false;
}

int main()
{
 
  assert(scanf("%d%d%d%d%d", &x, &a, &y, &b, &l) == 5);
  assert(1 <= x && x <= 150);
  assert(1 <= a && a <= 150);
  assert(1 <= y && y <= 150);
  assert(1 <= b && b <= 150);
  assert(1 <= l && l <= 150);
  assert(x + y >= l);
  int mi = 1, ma = (x * a + y * b) / l;
  while (mi < ma)
  {
    int av = (mi + ma + 1) / 2;
    if (solve(av))
      mi = av;
    else
      ma = av - 1;
  }
  printf("%d\n", mi);

  return 0;
}
