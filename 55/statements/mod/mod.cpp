#include <iostream>
#include <vector>
#include <list>
#include <cstdio>
 
using namespace std;
 
const int empty_value = 2;
vector<list<int> > adj;
vector<int> results;
int n;
void input()
{
    cin>>n;
    adj.resize(n);
    results.resize(n);
    results.assign(n,empty_value);
 
    char type;
    int parent;
    for (int i = 1;i<n;i++)
    {
        cin>>type>>parent;
        parent--;
        adj[parent].push_back(i);
        if (type == 'L')
            cin>>results[i];
    }
}
int bestFor(int player, int vertex)
{
    if (results[vertex] != empty_value)
        return results[vertex];
    list<int>::iterator it = adj[vertex].begin();
    int curRes;
    bool isDraw = false;
    for (;it!=adj[vertex].end();it++)
    {
        curRes = bestFor(-player,*it);
        if (curRes == player)
            return curRes;
        else if (curRes == 0)
            isDraw = true;
    }
    if (isDraw)
        return 0;
    else
        return -player;
}
void solve()
{
    int result = bestFor(1,0);
    if (result == 1)
        cout<<"+1";
    else
        cout<<result;
}
int main()
{
   // freopen("input.txt","r",stdin);
  //  freopen("output.txt","w",stdout);
    
    input();
    solve();
    return 0;
}
