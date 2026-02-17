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
int ccomps[2];
vector <pii> comps[2][110 * 110];

int comp[110][110];

void clean()
{
	memset(was, false, sizeof(was));
	memset(was2, false, sizeof(was2));
	path.resize(0);
}

void dfs(int x, int y, int c, int cc)
{
	if (comp[x][y] != -1) return;
	comps[c][cc].pb(mp(x, y));
	comp[x][y] = cc;
	for (int dd = 0; dd < 4; dd++)
	{
		int nx = x + dx[dd];
		int ny = y + dy[dd];
		if (!good(nx, ny)) continue;
		if (ncolor[x][y] != ncolor[nx][ny]) continue;
		dfs(nx, ny, c, cc);
	}
}

void colorComponents()
{
	memset(comp, -1, sizeof(comp));
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (comp[x][y] != -1) continue;
			int c = ncolor[x][y];
			dfs(x, y, c, ccomps[c]++);
		}
	}
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

void go(int dd, bool repaint)
{
	cx += dx[dd];
	cy += dy[dd];
	answer += repaint ? MOVES[dd] : tolower(MOVES[dd]);
	if (repaint)
		ccolor[cx][cy] = ccolor[cx - dx[dd]][cy - dy[dd]];
}

void go(int toX, int toY, bool repaint)
{
	while (cx > toX)
		go(0, repaint);
	while (cx < toX)
		go(2, repaint);
	while (cy > toY)
		go(3, repaint);
	while (cy < toY)
		go(1, repaint);	
}

void solve()
{
	colorComponents();
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

	paintAll(cx, cy, whiteX, whiteY, 1);
	clean();

	if (whiteX != -1)
	{
		go(whiteX, whiteY, false);
		
		for (int i = 0; i < ccomps[0]; i++)
		{
			clean();
			int toX = comps[0][i][0].fi;
			int toY = comps[0][i][0].se;
			go(toX, toY, true);
			paint(toX, toY, 0);
		}

		for (int i = 0; i < ccomps[1]; i++)
		{
			clean();
			int toX = -1;
			int toY = -1;
			for (int j = 0; j < (int)comps[1][i].size(); j++)
			{
				int x = comps[1][i][j].fi;
				int y = comps[1][i][j].se;
				if (ccolor[x][y] == 1)
				{	
					toX = x;
					toY = y;
					break;
				}
			}
			if (toX == -1) continue;
			go(toX, toY, false);
			paint(cx, cy, 1);
		}
	}	

	puts(answer.c_str());
}

int main()
{
#ifndef NOFILES
	//freopen(TASK".in", "r", stdin);
	//freopen(TASK".out", "w", stdout);
#endif	
	load();
	solve();
	return 0;
}
