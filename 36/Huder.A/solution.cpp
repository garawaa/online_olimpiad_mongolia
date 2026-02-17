#define _ijps 01
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:667772160")
#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <map>
#include <set>
#include <deque>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <bitset>
#include <algorithm>
#include <string>
#include <fstream>
#include <assert.h>
#include <list>
#include <cstring>
using namespace std;

#define name ""
typedef unsigned long long ull;
typedef long long ll;
#define mk make_pair
#define forn(i, n) for(ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for(ll i = (ll)q; i < (ll)n; i++)

const ll Log = 60;

const ll mod = 1e9 + 7;

ll A[Log];

int main(){
	ll n;
	cin >> n;
	forn(i, Log){
		A[i] += (n >> (i + 1)) << i;
		if(n % (1ll << (i + 1)) >= (1ll << i)){
			A[i] += n % (1ll << (i + 1)) - (1ll << i) + 1;
		}
		A[i] %= mod;
	}
	ll res = 0;
	forn(i, Log){
		ll a = (1ll << i) % mod;
		ll b = A[i] % mod;
		ll c = (n - A[i]) % mod;
		res += a * b % mod * c % mod;
		res %= mod;
	}
	cout << res % mod;
}