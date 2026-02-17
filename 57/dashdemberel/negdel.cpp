#include <bits/stdc++.h>

using namespace std;

vector<vector<long long> > v;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    long long mx = (long long)-1e18;
    for (int i = 0; i < n; i++)
    {
        vector<long long> a;
        int m;
        cin >> m;
        int q = 0;
        for (int j = 0; j < m; j++)
        {
            long long x;
            cin >> x;
            a.push_back(x);
            if (x > a[q])
                q = j;
        }
        swap(a[q], a[0]);
        mx = max(mx, a[0]);
        v.push_back(a);
    }
    long long ans = 0;
    for (int i = 0; i < n; i++)
        ans += v[i].size() * (mx - v[i][0]);
    cout << ans << endl;
    return 0;
}
