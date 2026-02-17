#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
using namespace std;

struct Range {
	int l, r;
	Range(int x, int y) {
		l = x;
		r = y;
	}
	Range(int x) { l = r = x; }
	Range() {
		l = INT_MAX;
		r = INT_MIN;
	}
	Range operator|(Range a) { return Range(min(l, a.l), max(r, a.r)); }
	void operator|=(Range a) {
		l = min(l, a.l);
		r = max(r, a.r);
	}
};

struct Segtree {
	vector<Range> v;
	int c;
	void update(int x, Range y) {
		x += 1 << c;
		while (x) {
			v[x] |= y;
			x /= 2;
		}
	}
	Range calc(int x) { return v[x + (1 << c)]; }
	Range calc(int l, int r) {
		l += 1 << c;
		r += 1 << c;
		Range x;
		while (l <= r) {
			x |= v[l];
			x |= v[r];
			l = (l + 1) / 2;
			r = (r - 1) / 2;
		}
		return x;
	}
	Range calc(Range x) { return calc(x.l, x.r); }
	Segtree() {}
	Segtree(int n) {
		c = 0;
		while ((1 << c) < n) c++;
		v.resize(1 << c + 1);
	}
};

int N, K, M, Q, A[200000], B[200000], S[50000], T[50000];
Range R[100000];
Segtree Seg[18];

int query(int s, int t) {
	int cnt = 0;
	Range p;
	p = Range(s);
	for (int i = 17; i >= 0; i--) {
		Range q = Seg[i].calc(p);
		if (!(q.l <= t && t <= q.r)) {
			p = q;
			cnt += 1 << i;
		}
	}
	if (cnt == (1 << 18) - 1)
		return -1;
	else
		return cnt + 1;
}

int main() {
	cin >> N >> K >> M;
	for (int i = 0; i < M; i++) {
		cin >> A[i] >> B[i];
		A[i]--;
		B[i]--;
	}
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> S[i] >> T[i];
		S[i]--;
		T[i]--;
	}
	for (int i = 0; i < 18; i++) {
		Seg[i] = Segtree(N);
	}
	for (int i = 0; i < N; i++) {
		R[i] = Range(i);
	}
	for (int i = 0; i < M; i++) {
		R[A[i]] |= Range(B[i]);
	}
	deque<pair<int, int>> q;
	for (int i = 0; i < N; i++) {
		while (!q.empty() && q.back().first < R[i].r) q.pop_back();
		q.push_back({R[i].r, i + K - 1});
		Seg[0].update(i, Range(q.front().first));
		while (!q.empty() && q.front().second <= i) q.pop_front();
	}
	q.clear();
	for (int i = N - 1; i >= 0; i--) {
		while (!q.empty() && q.back().first > R[i].l) q.pop_back();
		q.push_back({R[i].l, i - K + 1});
		Seg[0].update(i, Range(q.front().first));
		while (!q.empty() && q.front().second >= i) q.pop_front();
	}
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < N; j++) {
			Seg[i + 1].update(j, Seg[i].calc(Seg[i].calc(j)));
		}
	}
	for (int i = 0; i < Q; i++) {
		cout << query(S[i], T[i]) << endl;
	}
}