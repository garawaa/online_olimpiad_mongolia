#include <bits/stdc++.h>

using namespace std;
#define inf 1000000000

int n;
int a[100];
int calced[100][100];

int f(int st, int ed)
{
	int i;
	int ret = inf;

	if (ed == st + 1)
	{
		return 0;
	}
	if (calced[st][ed] != -1)
	{
		return calced[st][ed];
	}
	int tmp;
	for (i = st + 1; i < ed; i++)
	{
		tmp = f(st, i) + f(i, ed) + a[i] * a[st] * a[ed];
		if (tmp < ret)
		{
			ret = tmp;
		}
	}
	return calced[st][ed] = ret;
}

int main()
{
	int i;
  int test;
  cin >> test;
  while(test--)
  {
	scanf("%d", &n);
	memset(calced, -1, sizeof(calced));
	for (i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	printf("%d\n", f(0, n - 1));
  }
	return 0;
}
