#include <bits/stdc++.h>
using namespace std;

long long INF = (long long)2e18;
int main()
{
	freopen("input.txt", "r", stdin);
    int x, y, z;
    cin >> x >> y >> z;
    int a, b, c;
    cin >> a >> b >> c;
    int t1, t2, t3, d;
    cin >> t1 >> t2 >> t3 >> d;
    int k, i, l, j;
    cin >> k >> i >> l >> j;
    
    int len[3] = {x, y, z};
    long long t[3] = {t1, t2, t3};
    pair<int, int> croses[3][3] = {{{-1, -1}, {a, b + 1}, {a + 1, c}}, 
                                   {{b + 1, a}, {-1, -1}, {b, c + 1}},
                                   {{c, a + 1}, {c + 1, b}, {-1, -1}}};
    
    long long ans = INF;
    if (k == l)
    {
        //zero cross case
        ans = abs(i - j) * t[k - 1];
        //three cross case
        pair<int, int> others[3] = {{2, 3}, {1, 3}, {1, 2}};
        int next1 = others[k - 1].first;
        int next2 = others[k - 1].second;
        
        int from1 = croses[k - 1][next1 - 1].first;
        int to3 = croses[next2 - 1][l - 1].second;
        
        long long ans1 = 3ll * d + t[next1 - 1] + t[next2 - 1] + abs(i - from1) * t[k - 1] + abs(j - to3) * t[l - 1];
        
        swap(next1, next2);

        from1 = croses[k - 1][next1 - 1].first;
        to3 = croses[next2 - 1][l - 1].second;
        
        long long ans2 = 3ll * d + t[next1 - 1] + t[next2 - 1] + abs(i - from1) * t[k - 1] + abs(j - to3) * t[l - 1];

        //cout << ans << endl << ans1 << endl << ans2 << endl;

        ans = min(ans, min(ans1, ans2));
    }
    else
    {
        // one cross case
        int from = croses[k - 1][l - 1].first;
        int to = croses[k - 1][l - 1].second;
        long long ans1 = abs(i - from) * t[k - 1] + abs(j - to) * t[l - 1] + d;
        
        //two cross case
        int other = 1 ^ 2 ^ 3 ^ k ^ l;
        //cerr << k << ' ' << l << ' ' << other << endl;  
        int from1 = croses[k - 1][other - 1].first;
        int to1 = croses[k - 1][other - 1].second;
        int from2 = croses[other - 1][l - 1].first;
        int to2 = croses[other - 1][l - 1].second;
        
        long long ans2 = abs(i - from1) * t[k - 1] + abs(j - to2) * t[l - 1] + 2ll * d + t[other - 1];
        ans = min(ans1, ans2);
    }    
    cout << ans << endl;
    return 0;
}