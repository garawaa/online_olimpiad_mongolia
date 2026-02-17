// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast,no-stack-protector")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
// #pragma GCC optimize("unroll-loops")

#include <stdio.h>
#include <bits/stdc++.h>

#ifdef PERVEEVM_LOCAL
    #define debug(x) std::cerr << (#x) << ":\t" << (x) << std::endl
#else
    #define debug(x) 238
#endif

#define fastIO std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0)
#define NAME "File"

using ll = long long;
using ld = long double;

#ifdef PERVEEVM_LOCAL
    std::mt19937 rnd(238);
#else
    std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
#endif

template<typename T>
bool smin(T& a, const T& b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template<typename T>
bool smax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

const double PI = atan2(0.0, -1.0);
const int INF = 0x3f3f3f3f;
const ll LINF = (ll)2e18;

template<typename TI, typename TF>
class generic_point {
public:
    TI x, y;

    generic_point() = default;

    generic_point(TI _x, TI _y) : x(_x), y(_y) {}

    generic_point<TI, TF> operator+() const {
        return *this;
    }

    generic_point<TI, TF> operator-() const {
        return generic_point<TI, TF>(-x, -y);
    }

    generic_point<TI, TF> operator+(const generic_point<TI, TF>& other) const {
        return generic_point<TI, TF>(x + other.x, y + other.y);
    }

    generic_point<TI, TF> operator-(const generic_point<TI, TF>& other) const {
        return generic_point<TI, TF>(x - other.x, y - other.y);
    }

    generic_point<TI, TF> operator*(TI k) const {
        return generic_point<TI, TF>(x * k, y * k);
    }

    generic_point<TI, TF>& operator+=(const generic_point<TI, TF>& other) {
        *this = (*this) + other;
        return *this;
    }

    generic_point<TI, TF>& operator-=(const generic_point<TI, TF>& other) {
        *this = (*this) - other;
        return *this;
    }

    generic_point<TI, TF>& operator*=(TI k) {
        *this = (*this) * k;
        return *this;
    }

    template<typename T = TI>
    typename std::enable_if<std::is_floating_point<T>::value, generic_point<TI, TF>>::type
    operator/(TI k) const {
        return generic_point<TI, TF>(x / k, y / k);
    }

    template<typename T = TI>
    typename std::enable_if<std::is_floating_point<T>::value, generic_point<TI, TF>&>::type
    operator/=(TI k) {
        *this = (*this) / k;
        return *this;
    }

    TI operator*(const generic_point<TI, TF>& other) const {
        return x * other.x + y * other.y;
    }

    TI operator%(const generic_point<TI, TF>& other) const {
        return x * other.y - y * other.x;
    }

    TI lenSqr() const {
        return x * x + y * y;
    }

    TF len() const {
        return sqrt(lenSqr());
    }

    TI distSqr(const generic_point<TI, TF>& other) const {
        return (other - *this).lenSqr();
    }

    TF dist(const generic_point<TI, TF>& other) const {
        return sqrt(distSqr(other));
    }

    generic_point<TI, TF> norm() const {
        return *this / len();
    }

    // Counterclockwise rotation by 90 degrees
    generic_point<TI, TF> ort() const {
        return generic_point<TI, TF>(-y, x);
    }

    // Counterclockwise rotation by c = cos(alpha), s = sin(alpha)
    template<typename T = TI>
    typename std::enable_if<std::is_floating_point<T>::value, generic_point<TI, TF>>::type
    rot(TF c, TF s) const {
        return *this * c + ort() * s;
    }

    // Counterclockwise rotation by alpha
    generic_point<TI, TF> rot(TF alpha) const {
        return rot(cos(alpha), sin(alpha));
    }

    TF arg() const {
        return atan2(y, x);
    }

    int quad() const {
        if (x >= 0 && y >= 0) {
            return 1;
        } else if (x < 0 && y >= 0) {
            return 2;
        } else if (x < 0 && y < 0) {
            return 3;
        } else if (x >= 0 && y < 0) {
            return 4;
        }
        throw;
    }

    template<typename T = TI>
    typename std::enable_if<std::is_floating_point<T>::value>::type
    scan() {
        double _x, _y;
        scanf("%lf%lf", &_x, &_y);
        x = _x;
        y = _y;
    }

    template<typename T = TI>
    typename std::enable_if<std::is_integral<T>::value>::type
    scan() {
        ll _x, _y;
        scanf("%lld%lld", &_x, &_y);
        x = _x;
        y = _y;
    }

    template<typename T = TI>
    typename std::enable_if<std::is_floating_point<T>::value>::type
    print() {
        printf("%.10lf %.10lf\n", (double)x, (double)y);
    }

    template<typename T = TI>
    typename std::enable_if<std::is_integral<T>::value>::type
    print() {
        printf("%lld %lld\n", (ll)x, (ll)y);
    }
};

using point = generic_point<ll, double>;

const int N = 2010;

point a[N];
int g[N * N];
std::vector<int> gr[N * N];
int position[N];
int type[N]; // 1 - green, 2 - blue, 3 - red
int used[N * N], par[N * N];
bool inCycle[N * N];
int tin[N * N], tout[N * N];
int timer = 0;

void findCycle(int v) {
    used[v] = 1;

    int to = g[v];
    if (to != -1) {
        if (used[to] == 0) {
            par[to] = v;
            findCycle(to);
        } else if (used[to] == 1 && !inCycle[to]) {
            for (int i = v; i != to; i = par[i]) {
                inCycle[i] = true;
            }
            inCycle[to] = true;
        }
    }

    used[v] = 2;
}

void dfs(int v) {
    used[v] = 1;
    tin[v] = timer++;

    for (auto to : gr[v]) {
        if (!inCycle[to] && used[to] == 0) {
            dfs(to);
        }
    }

    tout[v] = timer++;
}

bool isParent(int v1, int v2) {
    return tin[v1] <= tin[v2] && tout[v1] >= tout[v2];
}

void run() {
    memset(g, -1, sizeof(g));

    int n, shift;
    scanf("%d%d", &n, &shift);
    --shift;

    for (int i = 0; i < n; ++i) {
        a[i].scan();
    }

    std::vector<std::pair<point, int>> points;
    for (int j = 0; j < n; ++j) {
        points.clear();
        for (int i = 0; i < n; ++i) {
            if (i == j) {
                continue;
            }

            points.emplace_back(a[i] - a[j], i);
        }

        std::sort(points.begin(), points.end(), [&](const std::pair<point, int>& p1, const std::pair<point, int>& p2) {
            const auto& pt1 = p1.first;
            const auto& pt2 = p2.first;

            if (pt1.quad() != pt2.quad()) {
                return pt1.quad() < pt2.quad();
            }

            ll cross = pt1 % pt2;
            if (cross != 0) {
                return cross > 0;
            } else {
                return pt1.lenSqr() < pt2.lenSqr();
            }
        });

        for (int i = 0; i < n; ++i) {
            if (i == j) {
                continue;
            }

            auto pos = std::lower_bound(points.begin(), points.end(), std::make_pair(a[j] - a[i], -1), [&](const std::pair<point, int>& p1, const std::pair<point, int>& p2) {
                const auto& pt1 = p1.first;
                const auto& pt2 = p2.first;

                if (pt1.quad() != pt2.quad()) {
                    return pt1.quad() < pt2.quad();
                }

                ll cross = pt1 % pt2;
                if (cross != 0) {
                    return cross > 0;
                } else {
                    if (p1.second == -1) {
                        return true;
                    } else if (p2.second == -1) {
                        return false;
                    } else {
                        return pt1.lenSqr() < pt2.lenSqr();
                    }
                }
            }) - points.begin();

            int vertexId = i * n + j;
            int nextPos = (pos + shift) % (n - 1);
            int nextVertexId = j * n + points[nextPos].second;

            g[vertexId] = nextVertexId;
            gr[nextVertexId].push_back(vertexId);
        }

        // auto prevPoint = points[0].first;
        // int prevI = 0;
        // for (int i = 0; i < (int)points.size(); ++i) {
        //     const auto&[curPoint, curId] = points[i];
        //     ll cross = prevPoint % curPoint;
        //     ll dot = prevPoint * curPoint;
        //     if (cross == 0 && dot > 0) {
        //         continue;
        //     }

        //     for (int k = prevI; k < i; ++k) {
        //         const auto&[thatPoint, thatId] = points[k];
        //         position[thatId] = prevI;
        //     }
        //     prevPoint = curPoint;
        //     prevI = i;
        // }
        // for (int k = prevI; k < (int)points.size(); ++k) {
        //     const auto&[thatPoint, thatId] = points[k];
        //     position[thatId] = prevI;
        // }

        // for (int i = 0; i < n; ++i) {
        //     if (i == j) {
        //         continue;
        //     }

        //     int vertexId = i * n + j;
        //     int pos = position[i];
        //     int nextPos = (pos + i + j) % (n - 1);
        //     int nextVertexId = j * n + points[nextPos].second;

        //     g[vertexId] = nextVertexId;
        //     gr[nextVertexId].push_back(vertexId);
        // }
    }

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         if (i == j) {
    //             continue;
    //         }

    //         std::cout << g[i * n + j] / n << ' ' << g[i * n + j] % n << std::endl;
    //     }
    // }

    for (int i = 0; i < n; ++i) {
        type[i] = 3;
    }

    for (int i = 0; i < n * n; ++i) {
        if (used[i] == 0) {
            findCycle(i);
        }
    }
    memset(used, 0, sizeof(used));
    for (int i = 0; i < n * n; ++i) {
        if (inCycle[i] && used[i] == 0) {
            dfs(i);
        }
    }

    for (int i = 0; i < n * n; ++i) {
        if (!inCycle[i]) {
            continue;
        }

        int from = i / n;
        int to = i % n;
        if (from == to) {
            continue;
        }

        type[from] = 1;
        type[to] = 1;
    }

    std::vector<int> curVertices;
    for (int i = 0; i < n; ++i) {
        if (type[i] == 1) {
            continue;
        }

        curVertices.clear();
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            curVertices.push_back(i * n + j);
            // curVertices.push_back(j * n + i);
        }

        std::sort(curVertices.begin(), curVertices.end(), [&](int v1, int v2) {
            return tin[v1] < tin[v2];
        });

        for (int j = 1; j < (int)curVertices.size(); ++j) {
            int v1 = curVertices[j - 1];
            int v2 = curVertices[j];
            
            if (isParent(v1, v2) || isParent(v2, v1)) {
                type[i] = 2;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (type[i] == 1) {
            printf("G");
        } else if (type[i] == 2) {
            printf("B");
        } else {
            printf("R");
        }
    }
    printf("\n");
}

int main(void) {
    // freopen(NAME".in", "r", stdin);
    // freopen(NAME".out", "w", stdout);

    #ifdef PERVEEVM_LOCAL
        auto start = std::chrono::high_resolution_clock::now();
    #endif

    run();

    #ifdef PERVEEVM_LOCAL
        auto end = std::chrono::high_resolution_clock::now();
        std::cerr << "Execution time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;
    #endif

    return 0;
}