#include <bits/stdc++.h>

using namespace std;

struct Cell {
    int x, y, dist;
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

char grid[110][110];
bool visited[110][110];
int N, M;

int bfs(int sx, int sy, int ex, int ey) {
	grid[ey][ex]='.';
    memset(visited, false, sizeof(visited));
    queue<Cell> q;
    q.push({sx, sy, 0});
    visited[sy][sx] = true;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        if (current.x == ex && current.y == ey) {
        	grid[ey][ex]='X';
            return current.dist;
            
        }

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (nx >= 0 &&nx<110 && ny<110 && ny >= 0 && !visited[ny][nx] && grid[ny][nx] == '.') {
                visited[ny][nx] = true;
                q.push({nx, ny, current.dist + 1});
            }
        }
    }
	grid[ey][ex]='X';
    return 0; 
}

int main() {
    cin >> N >> M;
    for (int i = 0; i <= M+1; ++i) {
        for (int j = 0; j <= N+1; ++j) {
            grid[i][j]='.';
        }
    }
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> grid[i][j];
        }
    }

    int sx, sy, ex, ey;
    while (cin >> sx >> sy >> ex >> ey) {
        if (sx == 0 && sy == 0 && ex == 0 && ey == 0) break;
        cout <<bfs(sx, sy, ex, ey)<<"\n";
    }

    return 0;
}
