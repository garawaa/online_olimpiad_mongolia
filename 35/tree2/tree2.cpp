#include <cstdio>
#include <vector>
using namespace std;

const int INF = 1000000007;

bool chmin(int &a, int b) {
	if (b < a) {
		a = b;
		return true;
	}
	return false;
}

int main() {
	int N;
	scanf("%d", &N);
	int H[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", H + i);
		H[i]--;
	}
	int invH[N];
	for (int i = 0; i < N; i++) invH[H[i]] = i;

	int cntup[N][N + 1];  //cntup[pos][num] = count #(position > pos && number >= num)
	fill(cntup[N - 1], cntup[N], 0);
	for (int j = N - 1; j; j--) {
		for (int i = 0; i <= H[j]; i++) cntup[j - 1][i] = cntup[j][i] + 1;
		for (int i = H[j] + 1; i <= N; i++) cntup[j - 1][i] = cntup[j][i];
	}

	int dp[N + 1];
	dp[0] = 0;
	for (int i = 1; i <= N; i++) {
		dp[i] = INF;
		int tmp = 0;
		for (int j = i - 1; j >= 0; j--) {
			tmp += (N - i) + cntup[invH[j]][j] - 2 * cntup[invH[j]][i];
			chmin(dp[i], dp[j] + tmp);
		}
	}
	printf("%d\n", dp[N]);
	return 0;
}