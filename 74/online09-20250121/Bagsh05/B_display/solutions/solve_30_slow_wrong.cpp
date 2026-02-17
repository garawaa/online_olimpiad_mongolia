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
const int MAXIT = 2;
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
int cx = 0;
int cy = 0;
int sx[2];
int sy[2];
int ds[110][110];

inline bool cmp(const pii &a, const pii &b)
{
	if (ds[a.fi][a.se] != ds[b.fi][b.se])
		return ds[a.fi][a.se] > ds[b.fi][b.se];
	return a.fi > b.fi;	
}

int d[110][110];
int p[110][110];
pii q[110 * 110];
void bfs(int sx, int sy, int fx, int fy)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			d[i][j] = INF;
			p[i][j] = -1;
		}	
	}

	d[sx][sy] = 0;
	int qh = 0;
	int qt = 0;
	q[qt++] = mp(sx, sy);
	while (qh < qt)
	{
		int x = q[qh].fi;
		int y = q[qh].se;
		qh++;
		for (int dd = 0; dd < 4; dd++)
		{
			int nx = x + dx[dd];
			int ny = y + dy[dd];
			if (!good(nx, ny) || (nx == fx && ny == fy)) continue;
			if (d[nx][ny] > d[x][y] + 1)
			{
				d[nx][ny] = d[x][y] + 1;
				p[nx][ny] = dd;
				q[qt++] = mp(nx, ny);
			}
		}
	}
}

void go(int tx, int ty, int fx, int fy, int color, bool needReturn)
{
	bfs(cx, cy, fx, fy);
	vi way;
	while (tx != cx || ty != cy)
	{
		int dd = p[tx][ty];
		way.pb(dd);
		tx -= dx[dd];
		ty -= dy[dd];
	}

	reverse(way.begin(), way.end());

	for (int i = 0; i < (int)way.size(); i++)
	{
		int dd = way[i];
		cx += dx[dd];
		cy += dy[dd];
		if (color != -1)
		{
			ccolor[cx][cy] = color;
			answer += MOVES[dd];
		}
		else answer += tolower(MOVES[dd]);	
	}

	if (needReturn)
	{
		for (int i = (int)way.size() - 1; i >= 0; i--)
		{
			int dd = (way[i] + 2) % 4;
			answer += tolower(MOVES[dd]);
			cx += dx[dd];
			cy += dy[dd];
		}
	}
}

void fix()
{
	if (sx[0] == 0 && sy[0] == 0)
	{
		swap(sx[0], sx[1]);
		swap(sy[0], sy[1]);
	}
}

void solve()
{
	bool same = false;
	for (int x = 0; !same && x < n; x++)
	{
		for (int y = 0; !same && y < n; y++)
		{
			for (int dd = 0; dd < 4; dd++)
			{
				int xx = x + dx[dd];
				int yy = y + dy[dd];
				if (!good(xx, yy)) continue;
				if (ncolor[x][y] == ncolor[xx][yy])
				{
					sx[0] = x; sx[1] = xx;
					sy[0] = y; sy[1] = yy;
					same = true;
					break;
				}
			}
		}
	}
	assert(same);
	
	fix();

	eprintf("start found: (%d, %d) (%d, %d)\n", sx[0], sy[0], sx[1], sy[1]);	
	go(sx[1], sy[1], sx[0], sy[0], 1, false);
	
	/*for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
			cerr << ccolor[x][y] << " ";
		cerr << "\n";	
	}*/

	bfs(sx[0], sy[0], -1, -1);
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (ncolor[x][y] == 0) ds[x][y] = d[x][y];
		}
	}

	bfs(sx[1], sy[1], -1, -1);
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (ncolor[x][y] == 1) ds[x][y] = d[x][y];
		}
	}

	vector <pii> all;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (x == sx[0] && y == sy[0]) continue;
			if (x == sx[1] && y == sy[1]) continue;
			all.pb(mp(x, y));
		}
	}
	sort(all.begin(), all.end(), cmp);

	for (int it = 0; it < MAXIT; it++)
	{
		for (int i = 0; i < (int)all.size(); i++)
		{
			int tx = all[i].fi;
			int ty = all[i].se;
			int cl = ncolor[tx][ty];
			if (ccolor[tx][ty] == cl) continue;

			//eprintf("we are at (%d, %d) need to color (%d, %d) in %d\n", cx, cy, tx, ty, cl);
			//eprintf("going to (%d, %d) without coloring\n", sx[cl], sy[cl]);
			go(sx[cl], sy[cl], -1, -1, -1, false);
			go(tx, ty, sx[cl ^ 1], sy[cl ^ 1], cl, true);

			/*eprintf("after coloring:\n");
			for (int x = 0; x < n; x++)
			{
				for (int y = 0; y < n; y++)
					cerr << ccolor[x][y] << " ";
				cerr << "\n";	
			}
			cerr << "\n";*/
		}
	}	

	/*cerr << "board:\n";
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
			cerr << ccolor[x][y] << " ";
		cerr << "\n";	
	}*/
	

	int cl = ncolor[cx][cy];
	if (ccolor[cx][cy] != ncolor[cx][cy])
		go(sx[cl], sy[cl], -1, -1, -1, false);

	go(sx[cl ^ 1], sy[cl ^ 1], -1, -1, cl, false);

	/*cerr << "our board:\n";
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
			cerr << ccolor[x][y] << " ";
		cerr << "\n";	
	}
	cerr << "need board:\n";
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
			cerr << ncolor[x][y] << " ";
		cerr << "\n";	
	}*/

	/*for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
			assert(ccolor[x][y] == ncolor[x][y]);
	}*/

	/*for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (ccolor[x][y] != ncolor[x][y])
				eprintf("(%d, %d) : %d != %d\n", x, y, ccolor[x][y], ncolor[x][y]);
		}
	}*/
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