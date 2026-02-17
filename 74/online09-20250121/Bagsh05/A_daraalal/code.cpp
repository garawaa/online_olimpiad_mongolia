// ?????????. ?????????? 12.
    // 12A. ?????????????????? [seq2]
    // ibelyaev: 30Dec2010
     
    #include <iostream>
    #include <cstdio>
    #include <vector>
     
    using namespace std;
     
    const int size = 1010;
    long long n;
    vector<int> mas;
    vector<int> mem;
    vector<int> pos;
    void input()
    {
        mas.resize(size);
        mem.resize(size);
        pos.resize(size);
        cin>>mas[0]>>mas[1]>>mas[2];
        mem[mas[2] + 10*mas[1] + 100*mas[0]] = 1;
     
        cin>>n;
        n--;
    }
    void solve()
    {
        int base = -1;
        int len = -1;
        for (int i=3;i<size;i++)
        {
            mas[i] = (mas[i-1] + mas[i-2] + mas[i-3])%10;
            int value = mas[i-1] + 10*mas[i-2] + 100*mas[i-3];
            if (mem[value] && i!=3)
            {
                base = pos[value];
                len = i - 3 - base;
                break;
            }
            mem[value] = 1;
            pos[value] = i-3;
        }
        if (n < base + len)
            cout<<mas[n];
        else
        {
            int index = base + (n - base) % len;
            cout<<mas[index];
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
