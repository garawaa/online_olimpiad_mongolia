// . ?????????? 13. 
  // 13B. ?????????????????? ????????? [fiboseq]
  // ?? ??????? + ????????
  // ibelyaev: 06Jan2011
   
  #include <iostream>
  #include <cstdio>
  #include <stdlib.h>
   
  using namespace std;
   
  int n,i,j;
  long long Fi,Fj;
  void input()
  {
      cin>>i>>Fi>>j>>Fj>>n;
  }
  long long Fib(int n)
  {
      long long prev = 1, cur = 1;
      for (int i = 2; i<=n; i++)
      {
          prev += cur;
          swap(cur, prev);
      }
      return cur;
  }
  //                       F[i]         F[i+1] 
  long long Fib(long long prev, long long cur, int n)
  {
      // forward
      if (n > i) {
          for (int pos = i + 2; pos <= n; pos++) { 
              prev += cur;
              swap(cur, prev);
          }
          return cur;
      }
      // back
      else {
          for (int pos = i - 1; pos>=n; pos--) {
              cur -= prev;
              swap(cur, prev);
          }
          return prev;
      }
  }
  void solve()
  {
      if (n == i) { cout<<Fi; return; }
      if (n == j) { cout<<Fj; return; }
   
      if (i > j) {
          swap(i,j);
          swap(Fi,Fj);
      }
   
      // A(i)   = 1 * A(i) + 0 * A(i+1)
      // A(i+1) = 0 * A(i) + 1 * A(i+1)
      // A(i+2) = 1 * A(i) + 1 * A(i+1)
      // A(i+3) = 1 * A(i) + 2 * A(i+1)
      // A(i+4) = 2 * A(i) + 3 * A(i+1)
      // A(i+5) = 3 * A(i) + 5 * A(i+1)
      // A(i+6) = 5 * A(i) + 8 * A(i+1)
   
      // F(0) = 1
      // F(1) = 1
      // F(2) = 2
      // F(3) = 3
      // F(4) = 5
      // F(5) = 8
   
      // A(i+x) = F(x-2) * A(i) + F(x-1) * A(i+1)
      // i + x = j
      // A(j) = F(j-i-2) * A(i) + F(j-i-1) * A(i+1);
      // A(i+1) = [A(j) - F(j-i-2) * A(i)] / F(j-i-1);
      // FiNxt = A(i+1);
      
      int k = j - i;
      long long FiNxt;
      if (k == 1)
          FiNxt = Fj;
      else
          FiNxt =  (Fj - Fib(k-2) * Fi) / Fib(k-1);   
      cout<<Fib(Fi, FiNxt, n);
  }
  int main()
  {
      freopen("input.txt","r",stdin);
      freopen("output.txt","w",stdout);
   
      input();
      solve();
      return 0;
  }
