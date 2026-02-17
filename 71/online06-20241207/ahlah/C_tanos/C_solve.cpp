#include <iostream>

using namespace std;
const int N = 1e6;

int ans[2][4 * N];
int add[2][4 * N];

void push(int i, int tl, int tr, int ind) {
    if (add[ind][i]) {
        ans[ind][i] = (tr - tl) - ans[ind][i];
        if (tl != tr - 1) {
            add[ind][2 * i + 1] = (add[ind][i] + add[ind][2 * i + 1]) % 2;
            add[ind][2 * i + 2] = (add[ind][i] + add[ind][2 * i + 2]) % 2;
        }
        add[ind][i] = 0;
    }
}

void upd(int i, int tl, int tr, int l, int r, int ind) {
    push(i, tl, tr, ind);
    if (tl >= r || tr <= l) {
        return;
    }
    if (l <= tl && tr <= r) {
        add[ind][i] = 1 - add[ind][i];
        push(i, tl, tr, ind);
        return;
    }
    int tm = (tl + tr) / 2;
    upd(2 * i + 1, tl, tm, l, r, ind);
    upd(2 * i + 2, tm, tr, l, r, ind);
    ans[ind][i] = ans[ind][2 * i + 1] + ans[ind][2 * i + 2];
}

int get(int i, int tl, int tr, int l, int r, int ind) {
    push(i, tl, tr, ind);
    if (tl >= r || tr <= l) {
        return 0;
    }
    if (l <= tl && tr <= r) {
        return ans[ind][i];
    }
    int tm = (tl + tr) / 2;
    return get(2 * i + 1, tl, tm, l, r, ind) + get(2 * i + 2, tm, tr, l, r, ind);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    int ind = 0, i = 0, j = 0;
    while (ind < n) {
        if (ind < n) {
            int a;
            cin >> a;
            if (a) upd(0, 0, n, i, i + 1, 0);
            ind++;
            i++;
        }
        if (ind < n) {
            int a;
            cin >> a;
            if (a) upd(0, 0, n, j, j + 1, 1);
            ind++;
            j++;
        }
    }
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        if (t == 1) {
            if (l % 2 == 0) {
                upd(0, 0, n, (l + 1) / 2, (r - 1) / 2 + 1, 0);
            }
            else {
                upd(0, 0, n, l / 2, r / 2, 1);
            }
        }
        else {
            if (l % 2 == 0) {
                cout << get(0, 0, n, (l + 1) / 2, (r - 1) / 2 + 1, 0) + get(0, 0, n, (l + 1) / 2, r / 2, 1) << "\n";
            }
            else {
                cout << get(0, 0, n, l / 2 + 1, (r - 1) / 2 + 1, 0) + get(0, 0, n, l / 2, r / 2, 1) << "\n";
            }
        }
    }
    return 0;
}
