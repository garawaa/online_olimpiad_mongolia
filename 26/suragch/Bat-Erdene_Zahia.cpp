#include <bits/stdc++.h>
#define int long long
using namespace std;
// #define FOR(i, begin, end) for (__typeof(end) i = (begin); i != (end) + 1 - 2 * ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

#define _upgrade ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORB(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a) for (int i = 0; i < a; i++)
#define REP1(i, a) for (int i = 1; i < a; i++)
#define REPB(i, a) for (int i = a - 1; i >= 0; i--)
#define TRAV(a,x) for (auto& a: x)
#define ALL(A) A.begin(), A.end()
#define LLA(A) A.rbegin(), A.rend()
#define II <int, int>
#define Q queue
#define ff first
#define bk back()
#define ss second
#define rs resize
#define ins insert 
#define fr front() 
#define ts to_string
#define pb push_back
#define mp make_pair
#define lb lower_bound 
#define ub upper_bound 
#define PQ priority_queue
#define umap unordered_map
#define sz(x) (int)x.size()

typedef long long ll;
typedef double db;
typedef unsigned uint;
typedef unsigned long long ull;
typedef unordered_map<int, int> umapII;
// PQ going up <int, VI, greater<int> >
typedef vector<int> VI;
typedef vector<char> VC;
typedef vector<string> VS;
typedef vector<VS> VVS;
typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<VVB> VVVB;
typedef vector<umapII> VumapII;
typedef vector<ll> VLL;
typedef vector<VLL> VVLL;
typedef vector<VVLL> VVVLL;
typedef vector<VVVLL> VVVVLL;
typedef vector<db> VD;
typedef set<int> SI;
typedef set<string> SS;
typedef map<int, int> MII;
typedef map<string, int> MSI;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<PII> VPI;
typedef vector<VPI> VVPI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI;
typedef vector<VVVI> VVVVI;
typedef vector<VVVVI> VVVVVI;
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 

int strToInt(string&a) {
    stringstream x(a);
    int b;
    x >> b;
    return b;
}
void readI(int& a) {
    cin >> a;
}
void readI(int& a, int&b) {
    cin >> a >> b;
}
void readI(int& a, int&b, int&c) {
    cin >> a >> b >> c;
}
VI readVI(int n) {
    VI a(n);
    REP(i, n) cin >> a[i];
    return a;
}
VVI readVVI(int n, int m) {
    VVI a(n, VI(m));
    REP(i, n) a[i] = readVI(m);
    return a;
}
VLL readVLL(ll n) {
    VLL a(n);
    REP(i, n) cin >> a[i];
    return a;
}
VVLL readVVLL(ll n, ll m) {
    VVLL a(n, VLL(m));
    REP(i, n) a[i] = readVLL(m);
    return a;
}


int gcd(int a, int b) {
   if (b == 0) return a;
   return gcd(b, a % b);
}

void print(VI& a) {
    for (auto el : a) {
        cout << el << ' ';
    }
    cout << '\n';
}

void print(VI& a, int n) {
    int cnt = 0;
    for (auto el : a) {
        if (cnt++ == n) break;
        cout << el << ' ';
    }
    cout << '\n';
}
const int MOD = 1e9 + 7;
const int INF = INT_MAX;
const ll INFF = INT64_MAX;
const db EPS = 1e-9;
const db PI = acos(-1.0); //M_PI;
const int moveX[] = {-1, 0, 1, 0};
const int moveY[] = {0, 1, 0, -1};
/*
|      ⣠⣶⡾⠏⠉⠙⠳⢦⡀⠀  ⠀⢠⠞⠉⠙⠲⡀
|  ⠀⠀⣴⠿⠏⠀⠀⠀⠀⠀⠀⢳⡀⠀  ⡏⠀⠀ ⠀⠀ ⢷
|⠀⠀⢠⣟⣋⡀⢀⣀⣀⡀⠀⣀⡀⣧⠀  ⢸⠀⠀⠀⠀   ⡇ ⠀
| ⠀⢸⣯⡭⠁⠸⣛⣟⠆⡴⣻⡲⣿   ⣸⠀⠀OK.  ⡇
|⠀⠀⣟⣿⡭⠀⠀⠀⠀⠀⢱⠀⠀⣿   ⢹⠀⠀⠀⠀⠀ ⡇
|⠀⠀⠙⢿⣯⠄⠀⠀⠀⢀⡀⠀⠀⡿⠀  ⡇⠀⠀ ⠀ ⡼
|⠀⠀⠀⠀⠹⣶⠆⠀⠀⠀⠀⠀⡴⠃ ⠀ ⠘⠤⣄⣠⠞⠀ ⠀
|⠀⠀⠀⠀⢸⣷⡦⢤⡤⢤⣞⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀
|⠀⢀⣤⣴⣿⣏⠁⠀⠀⠸⣏⢯⣷⣖⣦⡀⠀⠀⠀⠀⠀⠀
|⢀⣾⣽⣿⣿⣿⣿⠛⢲⣶⣾⢉⡷⣿⣿⠵⣿⠀⠀⠀⠀⠀
|⣼⣿⠍⠉⣿⡭⠉⠙⢺⣇⣼⡏⠀ ⠀⣄⢸⣿
|⣿⣿⣧⣀⣿.........⣀⣰⣏⣘⣆⣀
      
|                                                   _         _   _
|                                                   (_)       | | | |
|_ __  _ __ ___   __ _ _ __ __ _ _ __ ___  _ __ ___  _ ___ ___| |_| |_
| '_ \| '__/ _ \ / _` | '__/ _` | '_ ` _ \| '_ ` _ \| / __/ __| __| __|
| |_) | | | (_) | (_| | | | (_| | | | | | | | | | | | \__ \__ \ |_| |_
| .__/|_|  \___/ \__, |_|  \__,_|_| |_| |_|_| |_| |_|_|___/___/\__|\__|
| |               __/ |
|_|              |___/
 _   _      _ _    __        __         _     _ 
| | | | ___| | | __\ \      / /__  _ __| | __| |
| |_| |/ _ \ | |/ _ \ \ /\ / / _ \| '__| |/ _` |
|  _  |  __/ | | (_) \ V  V / (_) | |  | | (_| |
|_| |_|\___|_|_|\___/ \_/\_/ \___/|_|  |_|\__,_|                                  


 
 
 


*/











int a, b, c, d;
int solve(int x, int y) {
    if (x <= c && y <= d) return 0;
    if (x > c) return 1 + solve((x+1) / 2, y);
    if (y > d) return 1 + solve(x, (y+1) / 2);
    return 0;
}
void go () {
    cin >> a >> b >> c >> d;
    cout << min(solve(a, b), solve(b, a)) << '\n';
}



signed main () {

#ifdef ONLINE_JUDGE
#else
    // freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
    _upgrade
    int T = 1;
    while(T--) go();
    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
*/