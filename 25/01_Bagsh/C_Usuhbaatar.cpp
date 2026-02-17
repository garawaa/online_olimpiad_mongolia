#include <vector>
#include <iostream>

using namespace std;

int N;
vector<int> adj[1001];
int C[1001];
char T[1001];

void solve(int u, int level) {
	if (T[u] == 'L') return;
	int count[3] = {0};
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		solve(v, level + 1);
		count[C[v]]++; 
	}
	int color = 0;
	
	if (level % 2) {
		if (count[1] > 0) C[u] = 1;
		else if (count[0] > 0) C[u] = 0;
		else C[u] = 2;
	} else {
		if (count[2] > 0) C[u] = 2;
		else if (count[0] > 0) C[u] = 0;
		else C[u] = 1;
	}
}

void init() {
	char t; int p;
	cin >> N;
	for (int i = 2; i <= N; i++) {
		cin >> T[i] >> p;
		if (T[i] == 'L') {
			cin >> C[i];
			if (C[i] == -1)
				C[i] = 2;
		}
		adj[p].push_back(i);
	}
}

int main() {
	init();
	solve(1, 1);
	cout << (C[1] == 1 ? "+1" : (C[1] == 0 ? "0" : "-1")) << endl;
}