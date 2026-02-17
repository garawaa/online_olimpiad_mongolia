// . ?????????? 10. 
// 10C. ???? ? ???????????? [crossgam]
// ??????? ??????: http://e-maxx.ru/algo/sprague_grundy
// ibelyaev: 22Dec2010
 
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
using namespace std;
const int NAN = -1;
int n,k;
string str;
vector<int> mem;
void input()
{
    cin>>n>>k;
    mem.resize(n+1);
    cin>>str;
}
void GetInitState(const string &str, vector<int> &mas)
{
    int pos = 0;
    while (pos<str.size())
    {
        int num = 0;
        while (pos < str.size() && str[pos] == 'O')
        {
            num++;
            pos++;
        }
        if (num>=k)
            mas.push_back(num);
        pos++;
    }
}
int Grundy(const int state)
{
    if (mem[state]!=NAN)
        return mem[state];
    set<int> next;
    for (int i=0; state - k - i>=0;i++)
    {
        int value = Grundy(i) ^ Grundy(state - k - i);
        next.insert(value);
    }
 
    int res = 0;
    while (next.find(res) != next.end())
        res++;
 
    mem[state] = res;
    return res;
}
void solve()
{
    fill(mem.begin() + k, mem.end(),NAN);
 
    vector<int> state;
    GetInitState(str,state);
    if (state.empty())
        cout<<0;
    else
    {
        int res = Grundy(state[0]);
        for (int i=1; i<state.size(); i++)
            res ^= Grundy(state[i]);
        
        cout<<(res == 0 ? 2:1);
    }
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
 
    input();
    solve();
    return 0;
}
