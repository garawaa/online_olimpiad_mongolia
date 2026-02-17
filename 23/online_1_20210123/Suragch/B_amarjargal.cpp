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
    string s;
    int a, b, c, d;
    cin >> s;
    a = (s[0] - '0') * 600 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
    cin >> s;
    b = (s[0] - '0') * 600 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
    cin >> s;
    c = (s[0] - '0') * 600 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
    cin >> s;
    d = (s[0] - '0') * 600 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
    if(b < a) {
        swap(a, b);
        swap(c, d);
    }
    int rem = (b - a) % c, rem1 = d % c, cnt = 0;
    vector<bool> remainders(c, 0);
    while(rem > 0 && !remainders[rem]) {
        remainders[rem] = 1;
        (rem += rem1) %= c;
        cnt ++;
    }
    if(rem > 0) {
        cout << "Never\n";
        return 0;
    }
    int ans = b + d * cnt;
    string day[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    cout << day[(ans / (24 * 60)) % 7] << "\n";
    ans %= 24 * 60;
    int hour = ans / 60, minute = ans % 60;
    if(hour < 10) {
        cout << "0";
    }
    cout << hour << ":";
    if(minute < 10) {
        cout << "0";
    }
    cout << minute << "\n";




    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/