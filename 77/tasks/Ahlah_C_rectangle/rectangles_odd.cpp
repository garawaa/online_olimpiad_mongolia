#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegTree
{
    int n;
    vector<ll> odd, total;
    vector<bool> lazy;     

    SegTree(const vector<ll> &len)
    {
        n = len.size();
        odd.assign(4 * n, 0);
        total.assign(4 * n, 0);
        lazy.assign(4 * n, false);
        build(1, 0, n - 1, len);
    }

    void build(int node, int l, int r, const vector<ll> &len)
    {
        if (l == r)
        {
            total[node] = len[l]; 
            odd[node] = 0;        
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, len);
        build(node * 2 + 1, mid + 1, r, len);
        total[node] = total[node * 2] + total[node * 2 + 1];
        odd[node] = 0;
    }

    void push(int node)
    {
        if (lazy[node])
        {
            int left = node * 2, right = node * 2 + 1;
            odd[left] = total[left] - odd[left];
            lazy[left] = !lazy[left];
            odd[right] = total[right] - odd[right];
            lazy[right] = !lazy[right];
            lazy[node] = false;
        }
    }

    void update(int node, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            odd[node] = total[node] - odd[node];
            lazy[node] = !lazy[node];
            return;
        }
        push(node);
        int mid = (l + r) / 2;
        if (ql <= mid)
            update(node * 2, l, mid, ql, qr);
        if (qr > mid)
            update(node * 2 + 1, mid + 1, r, ql, qr);
        odd[node] = odd[node * 2] + odd[node * 2 + 1];
    }

    ll query()
    {
        return odd[1];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K;
    cin >> N >> M >> K;

    vector<int> xs, ys;
    xs.push_back(1);
    xs.push_back(N + 1);
    ys.push_back(1);
    ys.push_back(M + 1);

    vector<tuple<int, int, int, int>> rects;
    for (int i = 0; i < K; ++i)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rects.emplace_back(x1, y1, x2, y2);
        xs.push_back(x1);
        xs.push_back(x2 + 1); 
        ys.push_back(y1);
        ys.push_back(y2 + 1);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int X = xs.size();     
    int Y = ys.size() - 1; 

    vector<vector<pair<int, int>>> events(X);
    for (auto &rect : rects)
    {
        int x1 = get<0>(rect), y1 = get<1>(rect);
        int x2 = get<2>(rect), y2 = get<3>(rect);

        int xi1 = lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
        int xi2 = lower_bound(xs.begin(), xs.end(), x2 + 1) - xs.begin();

        int yL = lower_bound(ys.begin(), ys.end(), y1) - ys.begin();
        int yR = lower_bound(ys.begin(), ys.end(), y2 + 1) - ys.begin() - 1;

        events[xi1].emplace_back(yL, yR);
        events[xi2].emplace_back(yL, yR);
    }

    vector<ll> len(Y);
    for (int i = 0; i < Y; ++i)
    {
        len[i] = ys[i + 1] - ys[i];
    }

    SegTree seg(len); 
    ll ans = 0;

    for (int i = 0; i < X - 1; ++i)
    {
        for (auto &p : events[i])
        {
            int l = p.first, r = p.second;
            seg.update(1, 0, Y - 1, l, r);
        }
        ll width = xs[i + 1] - xs[i]; 
        ll odd = seg.query();         
        ans += width * odd;           
    }

    cout << ans << "\n";
    return 0;
}
