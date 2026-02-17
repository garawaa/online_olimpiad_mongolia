#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
bool b;
int n, k;
vector<int> q;
void task(vector<int> v, int N, int K)
{
    if(b) return;
    if(K == 0 && N == 0)
    {
        cout << "YES" << endl;
        for(int i = 0; i < v.size(); i++)
        {
            cout << n - v[i] * v[i] << " ";
        }
        b = true;
        return;
    }
    if(K == 0 && N > 0) return;
    int x;
    vector<int> u;
    if(v.size() > 0) x = v[v.size() - 1];
    else x = 1000000;
    for(int i = int(sqrt((N + K - 1) / K)); i * i <= N && i < x && i * i < n; i++)
    {
        u = v;
        u.push_back(i);
        task(u, N - i * i, K - 1);
    }
}
int main()
{
    cin >> n >> k;
    int m = n * (k - 1);
    b = false;
    task({}, m, k);
    if(!b) cout << "NO";
    return 0;
}
