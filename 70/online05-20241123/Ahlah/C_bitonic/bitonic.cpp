#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    int n;
    cin >> n;

    vector<ll> v(n);
    vector<ll> up(n);
    vector<ll> down(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
        up[i] = 1;
        down[i] = 1;
    }

    for (int i = n - 2; i >= 0; i--) {
        if (v[i] < v[i + 1]) {
            up[i] += up[i + 1];
        }

        if (v[i] > v[i + 1]) {
            down[i] += down[i + 1];
        }
    }

    ll cnt = 0;

    for (int i = 0; i < n; i++) {
        cnt += up[i] + down[i + up[i] - 1] - 1;
    }

    cout << cnt << endl;

    return 0;
}
