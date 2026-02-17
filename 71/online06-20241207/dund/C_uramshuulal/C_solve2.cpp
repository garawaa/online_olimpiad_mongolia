#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    scanf("%d%d", &n, &k);
    vector <int> a(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    sort(a.begin(), a.end(), greater<int>());
    int res = 0;
    for (int i = 0; i < n; ++i)
        if (i % k != k - 1)
            res += a[i];
    printf("%d\n", res);

    return 0;
}