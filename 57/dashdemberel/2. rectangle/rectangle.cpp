/*
	Time Complexity: O(HW * min(H, W))
	In this sample source code, we are using 1D array for representing the data of A[i][j].
	The main purpose is to simplify the code and to speed up, but this kind of speed up is not necessary.
	It is possible also possible to implement using vector<vector<int> > or some similar ways.
*/

#include <iostream>
using namespace std;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

// arrays: size > 50000 + 2 * sqrt(50000)
int H, W, A[51200], AT[51200];
int VP[9][9][51200], VQ[9][6][51200], V[6][6][51200], S[6][51200];
int SA[51200], SB[51200], cnt[51200];

int getsum(int id, int x, int ly, int ry) {
	if (ry - ly == 1) return V[id][0][x * W + ly];
	if (ry - ly == 2) return V[id][1][x * W + ly];
	if (ry - ly == 3) return V[id][2][x * W + ly];
	if (ry - ly == 4) return V[id][3][x * W + ly] + V[id][4][x * W + ly + 2];
	return V[id][3][x * W + ly] + V[id][4][x * W + ry - 2] + S[id][x * W + ry - 2] - S[id][x * W + ly + 2];
}

int main() {
	// step #0. read input
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> H >> W;
	for (int i = 0; i < H * W; i++) {
		cin >> A[i];
	}
	if (H < W) {
		for (int i = 0; i < H * W; i++) {
			AT[(i % W) * H + (i / W)] = A[i];
		}
		for (int i = 0; i < H * W; i++) {
			A[i] = AT[i];
		}
		swap(H, W);
	}
	
	// step #1. compute arrows
	// - e=0: .[!]. / e=1: .[!-] / e=2: .[!--
	// - e=3: [-!]. / e=4: [-!-] / e=5: [-!--
	// - e=6: --!]. / e=7: --!-] / e=8: --!--
	for (int ex = 0; ex < 9; ex++) {
		for (int ey = 0; ey < 9; ey++) {
			for (int x = 0; x < H; x++) {
				for (int y = 0; y < W; y++) {
					int lx = x - ex / 3, rx = x + ex % 3 + 1;
					int ly = y - ey / 3, ry = y + ey % 3 + 1;
					if (lx < 0 || ly < 0 || rx > H || ry > W) {
						continue;
					}
					int arrows = 0;
					for (int k = 0; k < 4; k++) {
						int tx = x + dx[k], ty = y + dy[k];
						if (lx <= tx && tx < rx && ly <= ty && ty < ry) {
							int mx = -1, my = -1, maxval = -1;
							for (int l = 0; l < 4; l++) {
								int ux = tx + dx[l], uy = ty + dy[l];
								if (lx <= ux && ux < rx && ly <= uy && uy < ry && A[ux * W + uy] < A[tx * W + ty] && maxval < A[ux * W + uy]) {
									maxval = A[ux * W + uy];
									mx = ux;
									my = uy;
								}
							}
							if (mx == x && my == y) {
								arrows++;
							}
						}
					}
					if (arrows == 0) {
						VP[ex][ey][x * W + y]++;
					}
				}
			}
		}
	}
	
	// step #2. gather nearby arrows for convenience
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < H * W; j++) {
			VQ[i][0][j] = VP[i][0][j];
			VQ[i][1][j] = VP[i][1][j] + VP[i][3][j + 1];
			VQ[i][2][j] = VP[i][2][j] + VP[i][4][j + 1] + VP[i][6][j + 2];
			VQ[i][3][j] = VP[i][2][j] + VP[i][5][j + 1];
			VQ[i][4][j] = VP[i][7][j] + VP[i][6][j + 1];
			VQ[i][5][j] = VP[i][8][j];
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < H * W; j++) {
			V[0][i][j] = VQ[0][i][j];
			V[1][i][j] = VQ[1][i][j] + VQ[3][i][j + W];
			V[2][i][j] = VQ[2][i][j] + VQ[4][i][j + W] + VQ[6][i][j + 2 * W];
			V[3][i][j] = VQ[2][i][j] + VQ[5][i][j + W];
			V[4][i][j] = VQ[7][i][j] + VQ[6][i][j + W];
			V[5][i][j] = VQ[8][i][j];
		}
	}
	
	// step #3. initialize range-summation system
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < H * W; j++) {
			S[i][j + 1] = S[i][j] + V[i][5][j];
		}
	}
	
	// step #4. counting phase
	long long answer = 0;
	for (int ly = 0; ly < W; ly++) {
		for (int ry = ly + 1; ry <= W; ry++) {
			for (int i = 0; i <= H; i++) {
				SA[i] = 0;
				SB[i] = 0;
			}
			int v8 = 0;
			for (int i = 0; i <= H - 2; i++) {
				if (i >= 2) {
					SA[i - 2] += v8;
					SB[i + 2] += v8;
				}
				SA[i] -= getsum(3, i, ly, ry);
				SB[i + 2] += getsum(4, i, ly, ry);
				v8 += getsum(5, i, ly, ry);
			}
			for (int i = 1; i <= H; i++) {
				if (i >= 4) {
					cnt[SA[i - 4] + 2 * W]++;
					answer += cnt[SB[i] + 2 * W - 1];
				}
				for (int j = i - 1; j >= i - 3 && j >= 0; j--) {
					int val = getsum(i - j - 1, j, ly, ry);
					if (val == 1) {
						answer += 1;
					}
				}
			}
			for (int i = 4; i <= H; i++) {
				cnt[SA[i - 4] + 2 * W]--;
			}
		}
	}
	
	// step #4. output the answer
	cout << answer << endl;
	
	return 0;
}
