// Меньшиков. Тренировка 10.
    // 10E. Путь спелеолога [speleo]
    // ibelyaev: 23Dec2010
     
    #include <iostream>
    #include <cstdio>
    #include <vector>
    #include <string>
    #include <queue>
    #include <limits>
     
    using namespace std;
     
    const int EMPTY = 0;
    const int USED = 1;
    int n;
    vector<vector<vector<int> > > mas;
    struct point
    {
        int x,y,z;
        point(){}
        point(int Z, int X, int Y)
        {
            z = Z; x = X; y = Y;
        }
    };
    point base;
    void input()
    {
        scanf("%d\n",&n);
        mas = vector<vector<vector<int> > >(n,vector<vector<int> >(n,vector<int>(n,0)));
        char c;
        for (int z = 0; z < n; z++)
        {
            for (int x = 0; x < n; x++)
            {
                for (int y = 0; y < n; y++)
                {
                    c = getchar();
                    if (c == 'S')
                        base = point(z,x,y);
                    mas[z][x][y] = (c == '#' ? USED : EMPTY);
                }
                getchar(); // '\n'
            }
            getchar(); // '\n'
        }           
    }
    int moveX[6] = {0 ,0, 0,0,-1,1};
    int moveY[6] = {0 ,0,-1,1, 0,0};
    int moveZ[6] = {-1,1, 0,0, 0,0};
    bool correct(int z, int x, int y)
    {
        if (z<0 || x<0 || y <0)
            return false;
        if (z==n || x==n || y==n)
            return false;
        return true;
    }
    void BFS()
    {
        int steps = -1;
        queue<point> q;
        int init = 2;
        mas[base.z][base.x][base.y] = init; // количество шагов
        q.push(base);
        while (!q.empty())
        {
            point cur = q.front(); q.pop();
            if (cur.z == 0)
            {
                steps = mas[cur.z][cur.x][cur.y];
                break;
            }
            for (int i=0;i<6;i++)
            {
                int x = cur.x + moveX[i];
                int y = cur.y + moveY[i];
                int z = cur.z + moveZ[i];
                if (correct(z,x,y) && mas[z][x][y] == EMPTY)
                {
                    mas[z][x][y] = mas[cur.z][cur.x][cur.y] + 1;
                    q.push(point(z,x,y));
                }
            }
        }
        cout<<steps - init;
    }
    int main()
    {
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
     
        input();
        BFS();
        return 0;
    }