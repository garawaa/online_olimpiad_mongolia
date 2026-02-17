// . ?????????? 10. 
// 10B. ?????? ????????? [fibostr]
// ibelyaev: 21Dec2010
 
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
 
using namespace std;
 
int n;
vector<string> mas;
vector<int> calc;
string str;
void input()
{
    cin>>n;
    calc.resize(n);
    cin>>str;
}
void precalc()
{
    int size = 10;
    mas.resize(size);
    mas[0] = "A";
    mas[1] = "B";
    for (int i=2;i<size;i++)
        mas[i] = mas[i-1] + mas[i-2];
}
inline int intersect(int N, string &str)
{
    // F(N) = F(N-1) + F(N-2)
    
    // ????? N-1
    int pos = N-1;
    while (pos>=mas.size())
        pos-=2;
    string begin = mas[pos];
    
    // ?????? N-2
    string end;
    if (N-2 < mas.size())
        end = mas[N-2];
    else
        end = mas.back();
 
    string common = begin + end;
    int left = begin.size() - str.size() + 1;
    left = max(left,0);
 
    int right = min (begin.size()-1, common.size() - str.size());
    for (int i=left; i<=right; i++)
    {
        bool isEqual = true;
        for (int j=0;j<str.size();j++)
        {
            if (common[i+j] != str[j])
            {
                isEqual = false;
                break;
            }
        }
        if (isEqual)
            return 1;
    }
    return 0;
}
void solve()
{
    precalc();
    if (str == "A") 
        calc[0] = 1;
    else if (str == "B")
        calc[1] = 1;
    for (int i=2;i<n;i++)
    {
        calc[i] = calc[i-1] + calc[i-2];
        calc[i] += intersect(i,str);
    }
    for (int i=2;i<n;i++)
   cout << mas[i];   
cout << endl;
cout<<calc.back();  
    
}
int main()
{
   // freopen("input.txt","r",stdin);
   // freopen("output.txt","w",stdout); 
    input();
    solve();
    return 0;
}
