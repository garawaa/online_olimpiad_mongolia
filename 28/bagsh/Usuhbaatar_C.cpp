#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int N, M, L[100001], R[100001];
	
	cin >> N >> M;
	for (int i = 0; i < N; i++) cin >> L[i];
	for (int i = 0; i < M; i++) cin >> R[i];
	sort(L, L + N);
	sort(R, R + M);
	
	int dL = -1, dR = abs(R[M - 1] - L[0]);
	
	while (dR - dL > 1) {
		int d = ((dL + dR) >> 1);
		int p = 0, i = 0, j = 0;
		while (i < N && j < M) {
			if (abs(L[i] - R[j]) <= d) {
				i++; j++; p++;
			} else {
				if (L[i] < R[j]) i++;
				else j++;
			}
		}
		if (p == min(N, M)) {
			dR = d;
		} else {
			dL = d;
		}
	}
	
	cout << dR << endl;
	return 0;
}