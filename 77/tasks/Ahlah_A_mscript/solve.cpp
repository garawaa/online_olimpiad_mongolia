#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

// маскны хамгийн их N битийг буцаана
unsigned long long make_mask(int N, int step) {
    unsigned long long mask = 0;
    int block = 1 << step; // block size
    for (int i = 0; i < N; i += block * 2) {
        for (int j = 0; j < block && i + j < N; j++) {
            mask |= 1ULL << (i + j);
        }
    }
    return mask;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<string> program;
    int steps = 0;

    for (int step = 0; (1 << step) < N && steps < K; step++) {
        unsigned long long mask = make_mask(N, step);
        int shift = 1 << step;

        // маск 2^N-аас бага байх ёстой (N <= 64 гэж үзэв, хэрэгтэй бол том тооны маск хэвлэж болно)
        string expr = "A=((A&" + to_string(mask) + ")+((A>>" + to_string(shift) + ")&" + to_string(mask) + "))";
        program.push_back(expr);
        steps++;
    }

    cout << program.size() << "\n";
    for (auto &line : program) cout << line << "\n";
    return 0;
}
