/*#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define MAX 502

int n,m,mark[MAX][MAX];
string mat[MAX];

struct Point
{int y,x; };

// comparison criteria for priority queue
bool operator<(Point a,Point b)
{
// smaller number of flips first
return mark[a.y][a.x]>mark[b.y][b.x];
}

priority_queue<Point> q;

// falling down in the given direction dir={-1:up,1:down}
Point fall(Point p,int dir)
{
for (; ; p.y+=dir)
{
if (mat[p.y][p.x]=='D') break;
if (p.y+dir<0 || p.y+dir>=n) return {-1,-1};
if (mat[p.y+dir][p.x]=='#') break;
}
return p;
}

// make move k={-1:left,0:flip,1:right}
//in the given direction dir={-1:up,1:down}
Point action(Point p,int k,int dir)
{
// move left or right
if (k)
{
p.x+=k;
if (p.x<0 || p.x>=m || mat[p.y][p.x]=='#') return {-1,-1};
}
// flip
else dir=-dir;
return fall(p,dir);
}

int main()
{
 freopen("input.txt", "r", stdin);
cin >> n >> m;
for (int i=0; i<n; i++)
cin >> mat[i];
//fin.close();

Point c,d;
for (int i=0; i<n; i++)
for (int j=0; j<m; j++)
if (mat[i][j]=='C') c=fall({i,j},1);
else if (mat[i][j]=='D') d={i,j};

if (c.y>=0)
{
q.push(c);
mark[c.y][c.x]=1;
for ( ; !q.empty(); )
{
Point e=q.top();
q.pop();
if (e.y==d.y && e.x==d.x) break;

// add legal moves to the priority queue
for (int i=-1,dir=mark[e.y][e.x]%2 ? 1 : -1; i<=1; i++)
{
Point p=action(e,i,dir);
if (p.y!=-1 && !mark[p.y][p.x])// add if not visited before
{
mark[p.y][p.x]=mark[e.y][e.x];
if (!i) mark[p.y][p.x]++;// if the move is a flip
q.push(p);
}
}
}
}

cout << mark[d.y][d.x]-1;
}
*/
//BFS implementation sample is below:

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define MAX 502
#define DIR(e) (mark[e.y][e.x]%2 ? 1 : -1)

int n,m,mark[MAX][MAX];
string mat[MAX];

struct Point
{int y,x; } c,d;

queue<Point> q;

// falling down in the given direction dir={-1:up,1:dowm}
Point fall(Point p,int dir)
{
for (; ; p.y+=dir)
{
if (mat[p.y][p.x]=='D') break;
if (p.y+dir<0 || p.y+dir>=n) return {-1,-1};
if (mat[p.y+dir][p.x]=='#') break;
}
return p;
}

// make move k={-1:left,0:flip,1:right}
//in the given direction dir={-1:up,1:down}
Point action(Point p,int k,int dir)
{
// move left or right
if (k)
{
p.x+=k;
if (p.x<0 || p.x>=m || mat[p.y][p.x]=='#') return {-1,-1};
}
// flip
else dir=-dir;
return fall(p,dir);
}

// try all points that has same flip using DFS
int dfs(Point p,int flip)
{
if (p.y==-1 || mark[p.y][p.x]) return 0;
mark[p.y][p.x]=flip;
if (p.y==d.y && p.x==d.x) return 1;
q.push(p);
int dir=DIR(p);
return dfs(action(p,-1,dir),flip) || dfs(action(p,1,dir),flip);
}

int main()
{
freopen("input.txt", "r", stdin);
//freopen("output.20", "w", stdout);
cin >> n >> m;
for (int i=0; i<n; i++)
cin >> mat[i];
//fin.close();

for (int i=0; i<n; i++)
for (int j=0; j<m; j++)
{
if (mat[i][j]=='C') c=fall({i,j},1);
else if (mat[i][j]=='D') d={i,j};

}

// BFS
if (!dfs(c,1))
for (; !q.empty(); )
{
Point e=q.front();
q.pop();
Point p=action(e,0,DIR(e));// flip the gravity
// push all the points that has the same flip
if (dfs(p,mark[e.y][e.x]+1)) break;
}

//ofstream fout("gravity.out");
cout << mark[d.y][d.x]-1 << endl;
//fout.close();
}
