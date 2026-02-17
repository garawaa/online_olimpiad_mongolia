#include <cstdio>
using namespace std;

#define MAXN 50000
#define MAXM 6

int N, M;
int word[MAXN];
int mask[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    char buf[MAXM + 1];
    for (int i = 0; i < N; ++i) {
        scanf(" %s", buf);
        int w = 0, m = 0;
        for (int j = 0; j < M; ++j) {
            if (buf[j] != '?') {
                w |= (buf[j] - 'a' + 1) << (5 * j);
                m |= 0x1f << (5 * j);
            }
        }
        word[i] = w;
        mask[i] = m;
    }

    int cnt = 0;
    for (int i = N - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if ((word[i] & mask[j]) == (word[j] & mask[i])) {
                ++cnt;
            }
        }
    }

    printf("%d\n", cnt);

    return 0;
}
