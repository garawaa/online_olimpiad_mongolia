#include <iostream>
#include <vector>
#include <algorithm>

int main() {
   // freopen("chaos.in", "r", stdin);
  //  freopen("chaos.out", "w", stdout);
    int a, b, c, d;
    long long k;
    std::cin >> a >> b >> c >> d >> k;
    std::vector <int> day(d + 1, -1);
    std::vector <int> cnt;
    day[a] = 0;
    cnt.push_back(a);
    int x = a;
    int curDay;
    for (curDay = 1; ; ++curDay) {
        x = std::min(d, std::max(0, x * b - c));
        cnt.push_back(x);
        if (day[x] != -1) {
            break;
        }
        day[x] = curDay;
    }

    if (k < (long long)cnt.size()) {
        printf("%d\n", cnt[(int)k]);
    } else {
        printf("%d\n", cnt[int((k - day[x]) % (curDay - day[x])) + day[x]]);
    }
    return 0;
}