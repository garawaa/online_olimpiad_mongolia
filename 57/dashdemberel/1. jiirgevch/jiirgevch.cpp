#include <cstdio>

typedef long long int ll;

ll n;
ll a[1020406];
ll q;
ll b[1020406];

ll cnt[1020406];
ll acc[1020406];

int main (void) {
	ll i, j;

	scanf("%lld", &n);
	for (i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
	}
	scanf("%lld", &q);
	for (i = 0; i < q; i++) {
		scanf("%lld", &b[i]);
	}

	acc[0] = 0;
	for (i = 0; i < n; i++) {
		ll num = 1;
		while (!(a[i] & num)) num *= 2;

		cnt[i] = num;
		acc[i + 1] = acc[i] + cnt[i];
	}

	ll result;

	for (i = 0; i < q; i++) {
		ll ok = n, ng = 0;
		while (ng + 1 < ok) {
			ll med = (ok + ng) / 2;
			if (acc[med] >= b[i]) {
				ok = med;
			} else {
				ng = med;
			}
		}

		result = a[ok - 1] / cnt[ok - 1];
		printf("%lld\n", result);
	}

	return 0;
}
