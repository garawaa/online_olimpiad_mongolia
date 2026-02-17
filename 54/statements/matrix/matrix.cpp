#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
 
const int marked = -1000*1000*1000;
int n;
vector<vector<int> > mas,waves;
struct point
{
    int x,y;
    point(){}
    point(int X, int Y)
    {
        x = X;
        y = Y;
    }
};
struct viewPoint
{
    int x, y;
    int num;
    viewPoint(){}
    viewPoint(int X, int Y, int Num)
    {
        x = X;
        y = Y;
        num = Num;
    }
};
bool operator == (const viewPoint &a, const viewPoint &b)
{
    return a.x == b.x && a.y == b.y;
}
vector<viewPoint> mainQueue;
vector<point> initPoints;
void input()
{
    cin>>n;
    mas   = vector<vector<int> > (n,vector<int>(n,0));
    waves = vector<vector<int> > (n,vector<int>(n,0));
    int amount = 1;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            scanf("%d", &mas[i][j]);
            if (mas[i][j] != 0)
            {
                initPoints.push_back(point(i,j));
                mainQueue.push_back(viewPoint(i,j,amount++));
            }
        }
    }
}
int moveX[4] = {-1,0,1,0};
int moveY[4] = {0,-1,0,1};
bool correct(int x, int y)
{
    if (x<0 || y<0)
        return false;
    if (x == n || y == n)
        return false;
    return true;
}
void solve()
{
    vector<viewPoint> nextQueue;
    int wavesAmount = 1;
    do
    {
        while (!mainQueue.empty())
        {
            viewPoint cur = mainQueue.back(); mainQueue.pop_back();
            for (int i = 0;i<4;i++)
            {
                int x = cur.x + moveX[i];
                int y = cur.y + moveY[i];
                if (correct(x,y))
                {
                    if (mas[x][y] == 0) // ?????? ???
                    {
                        mas[x][y] = cur.num == -1 ? marked : -cur.num;
                        nextQueue.push_back(viewPoint(x,y,cur.num));
                        waves[x][y] = wavesAmount;
                    }
                    else if (waves[x][y] == wavesAmount && mas[x][y] != -cur.num && mas[x][y] != marked)
                    {
                        mas[x][y] = marked;
                        viewPoint newViewPoint(x,y,-1);
                        for (int i=0;i<nextQueue.size();i++)
                        {
                            if (nextQueue[i] == newViewPoint)
                            {
                                nextQueue[i].num = - 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
        swap(mainQueue,nextQueue);
        wavesAmount++;
    }while (!mainQueue.empty());
 
}
void output()
{
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (mas[i][j] == marked)
                mas[i][j] = 0;
            if (mas[i][j] < 0)
            {
                point p = initPoints[-mas[i][j]-1];
                mas[i][j] = mas[p.x][p.y];
            }
            printf("%d ",mas[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
 
    input();
    solve();
    output();
 
    return 0;
}
