#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ss second
#define ff first
#define pb push_back
#define pii pair<int, int>
#define INF INT_MAX
#define debug(n) cout << #n << " = " << n << "\n";
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

using namespace std;

const ll MOD = 1e9 + 7;

int main() {
    ll a, b, c, d;
    cin >> a >> b;
    if(a > b) 
        swap(a, b);
    if(b % a == 0) {
        cout << b - a << "\n";
        return 0;
    }
    ll gcd = __gcd(a, b);
    ll n = a / gcd, m = b / gcd;
    ll lcm = n * m / __gcd(n, m);
    cout << (lcm / n - 1) * a - b << "\n";




    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/