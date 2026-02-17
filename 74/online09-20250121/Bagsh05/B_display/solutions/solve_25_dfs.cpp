#include <iostream>
#include <queue>
#include <cassert>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <iomanip>
#define nextLine() { for (int c = getchar(); c != '\n' && c != EOF; c = getchar()); }
#define sqr(a) ((a)*(a))
#define has(mask,i) (((mask) & (1<<(i))) == 0 ? false : true)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define TASK "chameleon"
using namespace std;

#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

typedef long long LL;
typedef long double ldb;
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef vector <bool> vb;
typedef vector <vb> vvb;

const int INF = (1 << 30) - 1;
const int MAXIT = 5;
const ldb EPS = 1e-9;
const ldb PI = fabs(atan2(0.0, -1.0));

int n;
int ccolor[110][110];
int ncolor[110][110];
void load()
{
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			ccolor[i][j] = 0;
	}
	ccolor[0][0] = 1;

	char tmp[110] = {0};
	for (int i = 0; i < n; i++)
	{
		gets(tmp);
		for (int j = 0; j < n; j++)
			ncolor[i][j] = tmp[j] == 'B';
	}
}

const int dx[4] = {-1, 0, 1,  0};
const int dy[4] = { 0, 1, 0, -1};
const string MOVES = "URDL";

inline bool good(int x, int y)
{
	return 0 <= x && x < n && 0 <= y && y < n;
}

string answer = "";
int cx;
int cy;
bool was[110][110];
bool was2[110][110];
vi path;

void clean()
{
	memset(was, false, sizeof(was));
	path.resize(0);
}

void dfs(int x, int y)
{
	was[x][y] = true;
	for (int dd = 0; dd < 4; dd++)
	{
		int nx = x + dx[dd];
		int ny = y + dy[dd];
		if (!good(nx, ny)) continue;
		if (was[nx][ny] || ncolor[x][y] != ncolor[nx][ny])
			continue;
		dfs(nx, ny);	
	}
}

bool isConnected(int sx, int sy)
{
	clean();
	dfs(sx, sy);

	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (ncolor[x][y] == ncolor[sx][sy] && !was[x][y])
				return false;
		}
	}
	return true;
}

bool dfs0(int x, int y, int tx, int ty, int fx, int fy)
{
	if (x == tx && y == ty) return true;
	if (x == fx && y == fy) return false;
	if (!good(x, y)) return false;
	if (was[x][y]) return false;
	was[x][y] = true;
	for (int dd = 0; dd < 4; dd++)
	{
		int nx = x + dx[dd];
		int ny = y + dy[dd];
		path.pb(dd);
		if (dfs0(nx, ny, tx, ty, fx, fy))
			return true;
		path.pop_back();	
	}
	return false;
}

void paint(int x, int y, int cc)
{
	was2[x][y] = true;
	ccolor[x][y] = cc;
	for (int dd = 0; dd < 4; dd++)
	{
		int nx = x + dx[dd];
		int ny = y + dy[dd];
		if (!good(nx, ny) || was2[nx][ny]) continue;
		if (ncolor[nx][ny] != cc) continue;
		answer += MOVES[dd];
		paint(nx, ny, cc);
		answer += tolower(MOVES[(dd + 2) % 4]);
	}
}

void paintAll(int x, int y, int fx, int fy, int cc)
{
	was2[x][y] = true;
	ccolor[x][y] = cc;
	for (int dd = 0; dd < 4; dd++)
	{
		int nx = x + dx[dd];
		int ny = y + dy[dd];
		if (!good(nx, ny) || was2[nx][ny]) continue;
		if (nx == fx && ny == fy) continue;
		answer += MOVES[dd];
		paintAll(nx, ny, fx, fy, cc);
		answer += tolower(MOVES[(dd + 2) % 4]);
	}
}

void go(bool repaint)
{
	for (int i = 0; i < (int)path.size(); i++)
	{
		int dd = path[i];
		cx += dx[dd];
		cy += dy[dd];
		if (repaint)
			ccolor[cx][cy] = ccolor[cx - dx[dd]][cy - dy[dd]];
		answer += repaint ? MOVES[dd] : tolower(MOVES[dd]);
	}
}

void solve()
{
	int blackX = -1, blackY = -1;
	int whiteX = -1, whiteY = -1;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (ncolor[x][y] == 1 && blackX == -1)
			{
				blackX = x;
				blackY = y;
			}
			if (ncolor[x][y] == 0 && whiteX ==  -1 && !(x == 0 && y == 0))
			{
				whiteX = x;
				whiteY = y;
			}
		}
	}

	if (isConnected(blackX, blackY))
	{
		clean();
		assert(dfs0(cx, cy, blackX, blackY, whiteX, whiteY));
		go(true);
		assert(cx == blackX && cy == blackY);

		clean();
		paint(cx, cy, 1);
		
		clean();

		memset(was2, false, sizeof(was2));
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				if (was2[x][y]) continue;
				if (ncolor[x][y] == 1) continue;
				if (ccolor[x][y] != 0) continue;
				clean();
				assert(dfs0(cx, cy, x, y, -1, -1));
				go(false);
				assert(cx == x && cy == y);
				paint(cx, cy, 0);
			}
		}
	} else if (isConnected(whiteX, whiteY))
	{
		clean();
		paintAll(0, 0, whiteX, whiteY, 1);
		clean();
		assert(dfs0(cx, cy, whiteX, whiteY, -1, -1));
		go(false);
		assert(cx == whiteX && cy == whiteY);
		memset(was2, false, sizeof(was2));
		paint(cx, cy, 0);
	} else
	{
	}
	puts(answer.c_str());
}

int main()
{
#ifndef NOFILES
	//freopen("01.i", "r", stdin);
	//freopen("01.out", "w", stdout);
#endif	
	load();
	solve();
	return 0;
}
