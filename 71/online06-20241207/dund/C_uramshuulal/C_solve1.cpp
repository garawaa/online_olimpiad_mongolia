#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(a) (int)a.size()
#define zero(a) memset (a, 0, sizeof(a))
#define mp make_pair

#define taskname "shop"

int n, k, A[110000];

int main (void)
{
  int i, res=0;
  assert(freopen ("input.txt", "r", stdin));
  freopen ("output.txt", "w", stdout);
  assert(scanf("%d%d", &n, &k)==2);
  assert(n>=1 && n<=100000 && k>=2 && k<=100);
  for (i=0; i<n; i++)
  {
    assert(scanf("%d", &A[i])==1);
    assert(A[i]>=1 && A[i]<=10000);
  }
  sort(A,A+n,greater<int>());
  for (i=k-1; i<n; i+=k)
    A[i]=0;
  for (i=0; i<n; i++)
    res+=A[i];
  printf("%d\n", res);
  return 0;
}

