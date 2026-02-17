#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int size;
    cin >> size;
    --size;
    
    int nlog = 0;
    while ((1 << nlog) <= size) ++nlog;

    std::string inputstring;
    cin >> inputstring;
    assert((int)inputstring.size() == size + 1);

    vector<int> a(size);
    for (int i = 0; i < size; ++i) {
        a[i] = inputstring[i] == inputstring[i + 1] ? 0 : 1;
    }

    vector<vector<int>> xors(nlog);
    for (int steplog = 1; steplog < nlog; ++steplog) {
        int step = 1 << steplog;
        xors[steplog].assign(size + 1, 0);
        for (int i = 0; i < size; ++i) {
            xors[steplog][i] = a[i] + (i >= step ? xors[steplog][i - step] : 0);
        }
    }

    int q;
    cin >> q;
    for (int it = 0; it < q; ++it) {
        int l, r;
        cin >> l >> r;
        r -= 1;
        int length = r - l + 1;
        int answer = 0;
        for (int steplog = 1; (1 << steplog) < length; ++steplog) {
            int step = 1 << steplog;
            int last = ((r - l) & ~(step - 1)) + l;
            int delta = xors[steplog][last];
            if (l >= step) {
                delta -= xors[steplog][l - step];
            }
            int cnt = 1 + ((last - l) >> steplog);
            answer += min(delta, cnt - delta);
            l += 1 << (steplog - 1);
            if (l > r) break;
        }
        answer = (answer + 1) >> 1;
        cout << answer << '\n';
    }
}
