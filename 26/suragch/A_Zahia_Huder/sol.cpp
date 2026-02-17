#include <iostream>

using namespace std;

long long solve(long long N, long long M, long long H, long long W)
{
    int ans = 0;
    while (H < N)
    {
        ans++;
        H *= 2;
    }
    while (W < M)
    {
        ans++;
        W *= 2;
    }
    return ans;
}

int main()
{
    long long N, M, H, W;
    cin >> N >> M >> H >> W;
    cout << min(solve(N, M, H, W), solve(M, N, H, W)) << "\n";
}