// ?????????. ?????????? 3.
    // 3C. ??????? [piggy]
    // ibelyaev: 02Mar2010
    #include <iostream>
    #include <vector>
    #include <limits.h>
     
    using namespace std;
     
    vector<int> P,W;
    int n;
    int E,F;
    vector<int> MAX, MIN;
    void input()
    {
        cin>>E>>F;
        cin>>n;
        MAX = vector<int>(F - E + 1,INT_MIN);
        MIN = vector<int>(F - E + 1,INT_MAX);
        P.resize(n); W.resize(n);
        for (int i=0;i<n;i++)
            cin>>P[i]>>W[i];
    }
    void solve()
    {
        MIN[0] = 0;
        MAX[0] = 0;
        for (int i = 0;i<MIN.size();i++)
        {
            for (int j=0;j<W.size();j++)
            {
                if (i - W[j]>=0 && MIN[i-W[j]]!=INT_MAX)
                {
                    MIN[i] = min(MIN[i],MIN[i-W[j]] + P[j]);
                    MAX[i] = max(MAX[i],MAX[i-W[j]] + P[j]);
                }
            }
        }
       
    }
    void output()
    {
        if (MIN.back()==INT_MAX)
            cout<<"This is impossible.";
        else
            cout<<MIN.back()<<' '<<MAX.back();
    }
    int main()
    {
        input();
        solve();
        output();
     
        return 0;
    }
