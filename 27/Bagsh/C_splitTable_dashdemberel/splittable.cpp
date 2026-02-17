#include <iostream>
#include <cmath>
using namespace std;

long long n, m, t;
int main() {
    ios_base::sync_with_stdio(0);
    cin >> t;
    for (int k = 0; k < t; k++) {
        cin >> n >> m;
        long long nm = n * m;
        long long split = (sqrt(2 * nm * nm + 2 * nm + 1) - 1) / 2 / m;
        long long best = 1e18;
        char x = 'V';
        int y = split;
        long long sumAll = nm * (nm + 1) / 2;
        split =(sqrt(nm * nm + m * m + 2 * nm + 1) - nm + m - 1) / 2;
        for (long long i = split; i <= min(m, split + 1ll); i++) {
            long long now_sum = i * n * (i + 1 + nm - m) / 2;
            if (best > abs(now_sum - (sumAll - now_sum))) {
                best = abs(now_sum - (sumAll - now_sum));
                x = 'V';
                y = i;
            }
        }
        split = (sqrt(2 * nm * nm + 2 * nm + 1) - 1) / 2 / m;
        for (long long i = split; i <= min(n, split + 1ll); i++) {
            long long now_sum = (m * m * i * i + m * i) / 2;
            if (best > abs(now_sum - (sumAll - now_sum))) {
                best = abs(now_sum - (sumAll - now_sum));
                x = 'H';
                y = i;
            }
        }

        cout << x << " " << y + 1 << "\n";
    }
}