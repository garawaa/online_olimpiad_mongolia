#include <bits/stdc++.h>

using namespace std;

struct Ticket {
	int c, p, a, b;
};

struct SegmentTree {
	int n, sz;
	vector<int> mx;
	vector<Ticket> tickets;

	SegmentTree(vector<Ticket> tickets) : tickets(tickets) {
		n = 1;
		sz = (int)tickets.size();
		while (n < sz) {
			n <<= 1;
		}
		mx.assign(2 * n, 0);
		for (int i = 0; i < n; ++i) {
			if (i < sz) {
				mx[i + n] = tickets[i].b;
			} else {
				mx[i + n] = -1;
			}
		}
		for (int i = n - 1; i >= 1; --i) {
			pull(i);
		}
	}

	void pull(int i) {
		mx[i] = max(mx[2 * i], mx[2 * i + 1]);
	}

	void remove(vector<int>& v, int p, int i = 1, int l = 0, int r = -1) {
		if (r == -1) {
			r += n;
		}
		if (l >= sz || tickets[l].a > p || mx[i] < p) {
			return;
		} else if (l == r) {
			mx[i] = -1;
			v.push_back(l);
		} else {
			int m = (l + r) >> 1;
			remove(v, p, 2 * i, l, m);
			remove(v, p, 2 * i + 1, m + 1, r);
			pull(i);
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	const long long INF = 1e18;
	int n, k;
	cin >> n >> k;
	vector<Ticket> tickets(k);
	for (auto& t : tickets) {
		cin >> t.c >> t.p >> t.a >> t.b;
		--t.c, --t.a, --t.b;
	}
	sort(tickets.begin(), tickets.end(), [](const auto& l, const auto& r) {
		return l.a < r.a;
	});
	auto dijkstra = [&](vector<long long> dist) {
		priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
		for (int i = n; i < n + k; ++i) {
			dist[tickets[i - n].c] = min(dist[tickets[i - n].c], dist[i] + tickets[i - n].p);
		}
		for (int i = 0; i < n; ++i) {
			if (dist[i] < INF) {
				pq.push({dist[i], i});
			}
		}
		SegmentTree seg(tickets);
		while (!pq.empty()) {
			auto x = pq.top();
			pq.pop();
			if (x.first > dist[x.second]) {
				continue;
			}
			vector<int> removed;
			seg.remove(removed, x.second);
			for (int r : removed) {
				if (dist[r + n] > x.first) {
					dist[r + n] = x.first;
					if (dist[tickets[r].c] > x.first + tickets[r].p) {
						dist[tickets[r].c] = x.first + tickets[r].p;
						pq.push({dist[tickets[r].c], tickets[r].c});
					}
				}
			}
		}
		return dist;
	};
	vector<long long> start_left(n + k, INF);
	start_left[0] = 0;
	vector<long long> dist_left = dijkstra(start_left);
	vector<long long> start_right(n + k, INF);
	start_right[n - 1] = 0;
	vector<long long> dist_right = dijkstra(start_right);
	vector<long long> dist(n + k);
	for (int i = 0; i < n + k; ++i) {
		dist[i] = dist_left[i] + dist_right[i];
	}
	dist = dijkstra(dist);
	for (int i = 0; i < n; ++i) {
		if (dist[i] < INF) {
			cout << dist[i] << '\n';
		} else {
			cout << -1 << '\n';
		}
	}
}
