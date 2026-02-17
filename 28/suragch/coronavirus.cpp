#ifdef LOCAL
#  define _GLIBCXX_DEBUG
#  define _GLIBCXX_DEBUG_PEDANTIC
#endif

#include "bits/stdc++.h"
#define ff first
#define ss second
#define szof(_x) ((int) (_x).size())
#define TASK_NAME ""

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int INF = 1e9 + 7;
const ll INFL = 1e18 + 123;
const long double PI = atan2(0, -1);
mt19937 tw(960172);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(tw) % (y - x + 1) + x; }

const long double eps = 1e-9;

struct point {
	long double x, y;
	point() : x(0), y(0) {}
	point(long double _x, long double _y) : x(_x), y(_y) {}

	point operator+(point const& other) const {
		return point(x + other.x, y + other.y);
	}

	point operator-(point const& other) const {
		return point(x - other.x, y - other.y);
	}

	point operator/(long double num) {
		return point(x / num, y / num);
	}

	point operator*(long double num) {
		return point(x * num, y * num);
	}	

	long double len() {
		return sqrt(x * x + y * y);
	}
};

ostream& operator<<(ostream& o, point const& p) {
	o << "(" << p.x << ", " << p.y << ")";
	return o;
}

long double cross(point const& p1, point const& p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

struct line {
	long double a, b, c;
	point any;
	line(long double _a, long double _b, long double _c) : a(_a), b(_b), c(_c) {}

	line(point const& p1, point const& p2) : any(p1) {
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = -(a * p1.x + b * p1.y);
		// assert(abs(a * p2.x + b * p2.y + c) < eps);
		long double tmp = sqrt(a * a + b * b);
		a /= tmp;
		b /= tmp;
		c /= tmp;
	}

	long double dist(point const& p) {
		return a * p.x + b * p.y + c;
	}

	point ort() {
		return point(a, b);
	}
};

vector<point> read_polygon() {
	int n;
	cin >> n;
	vector<point> ret;
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		ret.push_back(point(x, y));
	}
	return ret;
}

bool intersect(line const& l1, line const& l2) {
	return abs(l1.a * l2.b - l1.b * l2.a) > eps;
}

point intersection(line const& l1, line const& l2) {
	long double d = l1.a * l2.b - l1.b * l2.a;
	long double d1 = -l1.c * l2.b + l1.b * l2.c;
	long double d2 = -l1.a * l2.c + l1.c * l2.a;
	return point(d1 / d, d2 / d);
}

bool check(vector<line>& lines) {
	shuffle(lines.begin(), lines.end(), tw);

	point cur = lines.front().any;
	for (int i = 1; i < szof(lines); ++i) {
		auto& l = lines[i];
		if (l.dist(cur) < -eps) {
			long double from = -1e100, to = 1e100;
			line ort = line(l.b, -l.a, 0);
			for (int j = 0; j < i; ++j) {
				if (intersect(lines[j], lines[i])) {
					point p = intersection(lines[j], lines[i]);
					long double val = ort.dist(p);

					if (cross(lines[i].ort(), lines[j].ort()) < 0) {
						from = max(from, val);
					} else {
						to = min(to, val);
					}
				} else {
					if (lines[j].dist(lines[i].any) < -eps) {
						to = -1e100;
						from = 1e100;
						break;
					}
				}
			}
			if (from <= to + eps) {
				if (from == -1e100 && to != 1e100) {
					from = to - 1;
				}
				if (from != -1e100 && to == 1e100) {
					to = from + 1;
				}
				ort.c = -(from + to) / 2;
				cur = intersection(lines[i], ort);
				// for (int j = 0; j <= i; ++j) {
				// 	if (lines[j].dist(cur) < -eps) {
				// 		cerr << lines[j].dist(cur) << endl;
				// 	}
				// 	assert(lines[j].dist(cur) >= -5e-7);
				// }
			} else {
				return false;
			}
		}
	}
	return true;
}

void solve() {
	vector<point> poly1 = read_polygon();
	vector<point> poly2 = read_polygon();

	long double l = 0, r = 1000;
	for (int q = 0; q < 100; ++q) {
		long double mid = (l + r) / 2;

		vector<line> lines;
		for (int i = 0; i < szof(poly1); ++i) {
			int next = (i + 1) % szof(poly1);
			point p1 = poly1[i], p2 = poly1[next];
			point v = p2 - p1;
			v = v / v.len();
			v = point(-v.y, v.x);
			p1 = p1 + v * mid;
			p2 = p2 + v * mid;
			for (int j = 0; j < szof(poly2); ++j) {
				lines.push_back(line(p1 - poly2[j], p2 - poly2[j]));
			}
		}

		if (check(lines)) {
			l = mid;
		} else {
			r = mid;
		}
	}

	cout << l << "\n";
}


int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cerr << fixed << setprecision(5);
	cout << fixed << setprecision(9);
	ios::sync_with_stdio(false);

	int tests = 1;
	// cin >> tests;
	for (int it = 1; it <= tests; ++it) {
		solve();
	}
	
	#ifdef LOCAL
		cerr << "time: " << clock() << " ms\n";
	#endif
	return 0;
}
