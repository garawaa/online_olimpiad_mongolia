#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;

const int ALPH_SIZE = 26;                       

int main()
{
    string s;
    cin >> s;
    vector<int> cnt(ALPH_SIZE, 0);
    int n = s.size();
    for (int i = 0; i < n; i++)
        cnt[s[i] - 'a']++;
    int evens = 0;
    for (int i = 0; i < ALPH_SIZE; i++)
        if (cnt[i] % 2 == 0)
            evens++;
    vector<vector<bool>> dp(s.size() + 1, vector<bool>(ALPH_SIZE + 1, false));
    for (int size = 1; size <= n; size++)
        for (int evens = 0; evens <= ALPH_SIZE; evens++)
        {
            if (size == ALPH_SIZE - evens) 
            {   
                dp[size][evens] = false;
                continue;  
            }
            bool res = false;
            if (evens > 0)
                res |= !dp[size - 1][evens - 1];
            if (evens < ALPH_SIZE)
                res |= !dp[size - 1][evens + 1];
            dp[size][evens] = res;
        }
    if (dp[s.size()][evens])
        cout << "Boroldoi" << endl;
    else
        cout << "Doldoi" << endl;
    return 0;
} 