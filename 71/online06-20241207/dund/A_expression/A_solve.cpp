#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) cin >> i;
    for (int i = 0; i < n; ++i)
        if (a[i] % 2 != 0) {
            int j = i;
            while (j < n && a[j] % 2 != 0) ++j;
            string ans(n - 1, 'x');
            if (i > 0) ans[i - 1] = '+';
            if (j < n) ans[j - 1] = '+';
            cout << ans;
            return 0;
        }
}
