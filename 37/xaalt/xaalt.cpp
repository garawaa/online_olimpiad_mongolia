
  #include <iostream>
  #include <cstdio>
  #include <string>
  #include <vector>
   
  using namespace std;
  const int MAX_VALUE = 1000000000;
  int n;
  string str;
  vector<vector<int> > mas;
  void input()
  {
      cin>>str;
      n = str.size();
      mas = vector<vector<int> >(n,vector<int>(n,0));
  }
  string open = "([";
  string clos = ")]";
  bool isPair(char f, char s)
  {
      int posF = open.find(f);
      int posS = clos.find(s);
      return posF == posS && posF != -1;
  }
  string Pair(char one)
  {
      int pos = open.find(one);
      if (pos == -1)
          pos = clos.find(one);
      
      return string(&open[pos],1) + string(&clos[pos],1);
  }
  string getAnswer(int l, int r)
  {
      if (l > r) return "";
      if (l == r)
          return Pair(str[l]);
      int border = (isPair(str[l],str[r]) ? mas[l+1][r-1] : MAX_VALUE);
      if (border == mas[l][r])
          return str[l] + getAnswer(l+1,r-1) + str[r];
      for (int m = l; m < r; m++)
      {
          if (mas[l][m] + mas[m+1][r] == mas[l][r])
              return getAnswer(l,m) + getAnswer(m+1,r);
      }
  }
  void solve()
  {
      for (int i=0;i<n;i++)
          mas[i][i] = 1;
      for (int len = 1; len < n; len++) {
          for (int i=0;i<n;i++) {
              int j = i + len;
              if (j>=n) break;
   
              int curLen = MAX_VALUE;
              if (isPair(str[i],str[j]))
                  curLen = mas[i+1][j-1];
              for (int m = i; m < j; m++)
                  curLen = min(curLen, mas[i][m] + mas[m+1][j]);
              mas[i][j] = curLen;
          }
      }
   
      string answer = "";
      answer = getAnswer(0,n-1);
      cout<<answer;
  }
  int main()
  {
     // freopen("input.txt","r",stdin);
     // freopen("output.txt","w",stdout);
   
      input();
      solve();
      return 0;
  }
