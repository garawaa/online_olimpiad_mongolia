#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Сегмент мод: Y тэнхлэгийн дагуух интервалуудын "сондгой" тоог хадгална
struct SegTree
{
    int n;
    vector<ll> odd, total; // odd: сондгой тоогоор хамрагдсан нүдний тоо, total: нийт нүдний тоо (тогтмол)
    vector<bool> lazy;     // lazy flag: хүүхдүүдээ эрвүүлэх шаардлагатай эсэх

    // Барих функц: len массив нь Y интервал бүрийн урт (хэдэн нүдтэй)
    SegTree(const vector<ll> &len)
    {
        n = len.size();
        odd.assign(4 * n, 0);
        total.assign(4 * n, 0);
        lazy.assign(4 * n, false);
        build(1, 0, n - 1, len);
    }

    // Сегмент модыг барих
    void build(int node, int l, int r, const vector<ll> &len)
    {
        if (l == r)
        {
            total[node] = len[l]; // навч зангилаа: нийт урт
            odd[node] = 0;        // эхэндээ бүгд тэгш (хамрагдаагүй)
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, len);
        build(node * 2 + 1, mid + 1, r, len);
        total[node] = total[node * 2] + total[node * 2 + 1];
        odd[node] = 0;
    }

    // Хүүхдүүд рүү lazy тэмдэглэгээг дамжуулах
    void push(int node)
    {
        if (lazy[node])
        {
            int left = node * 2, right = node * 2 + 1;
            // Эрвүүлэх: odd = total - odd
            odd[left] = total[left] - odd[left];
            lazy[left] = !lazy[left];
            odd[right] = total[right] - odd[right];
            lazy[right] = !lazy[right];
            lazy[node] = false;
        }
    }

    // [ql, qr] интервалыг эрвүүлэх (update)
    void update(int node, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            odd[node] = total[node] - odd[node];
            lazy[node] = !lazy[node];
            return;
        }
        push(node); // хүүхдүүд рүү түлхэх
        int mid = (l + r) / 2;
        if (ql <= mid)
            update(node * 2, l, mid, ql, qr);
        if (qr > mid)
            update(node * 2 + 1, mid + 1, r, ql, qr);
        odd[node] = odd[node * 2] + odd[node * 2 + 1];
    }

    // Бүх Y интервалын сондгой нүдний нийт тоог буцаана
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

    // Компресс хийхэд хэрэглэгдэх координатуудыг цуглуулах
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
        xs.push_back(x2 + 1); // тэгш өнцөгтийн баруун талын дараах х
        ys.push_back(y1);
        ys.push_back(y2 + 1); // тэгш өнцөгтийн доод талын дараах у
    }

    // X координатыг эрэмбэлж давхардлыг арилгах
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    // Y координатыг эрэмбэлж давхардлыг арилгах
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int X = xs.size();     // X интервалын тоо +1 (xs[i] цэгүүд)
    int Y = ys.size() - 1; // Y интервалын тоо (ys[i]-с ys[i+1] хүртэл)

    // Үйл явдлын жагсаалт: events[x индекс] -> (yL, yR) хосын жагсаалт
    vector<vector<pair<int, int>>> events(X);
    for (auto &rect : rects)
    {
        int x1 = get<0>(rect), y1 = get<1>(rect);
        int x2 = get<2>(rect), y2 = get<3>(rect);

        // X индексүүдийг олох
        int xi1 = lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
        int xi2 = lower_bound(xs.begin(), xs.end(), x2 + 1) - xs.begin();

        // Y индексүүдийг олох (Y интервалын индекс)
        int yL = lower_bound(ys.begin(), ys.end(), y1) - ys.begin();
        int yR = lower_bound(ys.begin(), ys.end(), y2 + 1) - ys.begin() - 1;

        // Эхлэх ба дуусах цэгүүдэд үйл явдал нэмэх
        events[xi1].emplace_back(yL, yR);
        events[xi2].emplace_back(yL, yR);
    }

    // Y интервал бүрийн уртыг тооцох
    vector<ll> len(Y);
    for (int i = 0; i < Y; ++i)
    {
        len[i] = ys[i + 1] - ys[i];
    }

    SegTree seg(len); // сегмент модыг барих
    ll ans = 0;

    // X тэнхлэгийн дагуу скан хийх (интервалууд)
    for (int i = 0; i < X - 1; ++i)
    {
        // Энэ x цэг дээр идэвхжих/идэвхгүй болох бүх үйл явдлыг хэрэгжүүлэх
        for (auto &p : events[i])
        {
            int l = p.first, r = p.second;
            seg.update(1, 0, Y - 1, l, r);
        }
        ll width = xs[i + 1] - xs[i]; // одоогийн X интервалын өргөн
        ll odd = seg.query();         // сондгой нүдний тоо Y тэнхлэг дээр
        ans += width * odd;           // энэ X интервалд хэдэн нүд сондгой вэ
    }

    cout << ans << "\n";
    return 0;
}