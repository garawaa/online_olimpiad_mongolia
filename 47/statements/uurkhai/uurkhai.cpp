// . ?????????? 11. 
  // 11E. ????? ?????? [homer]
  // ibelyaev: 27Dec2010
   
  #include <iostream>
  #include <cstdio>
  #include <vector>
   
  using namespace std;
   
  const int MAX_VALUE = 1<<30;
  int f,s,n;
  vector<int> amounts,ostatok;
   
  void input()
  {
      cin>>f>>s>>n;
      amounts.resize(n+1);
      ostatok = vector<int>(n+1,MAX_VALUE);
  }
  void go(int f)
  {
      for (int i=f; i <= n; i++)
      {
          if (ostatok[i-f] < ostatok[i])
          {
              ostatok[i] = ostatok[i-f];
              amounts[i] = amounts[i-f] + 1;
          }
      }
  }
  void solve()
  {
      if (f>s) swap(f,s);
      for (int i=0;i<f;i++)
      {
          amounts[i] = 0;
          ostatok[i] = i;
      }
      
      go(f);
      if (f!=s)
          go(s);
      
   
      cout<<amounts[n];
      if (ostatok[n] != 0)
          cout<<" "<<ostatok[n];
  }
  int main()
  {
      freopen("input.txt","r",stdin);
      freopen("output.txt","w",stdout);
   
      input();
      solve();
      return 0;
  }
