#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
unsigned long long n, m;
unsigned long long sum;
unsigned long long solvex(unsigned long long mid){
 unsigned long long a;
 if (mid%2==1 && m%2==1) a=(1 + mid * m)/2* (mid * m);
 else a=(mid * m)/2*(1 + mid * m);
 unsigned long long b = sum - a;
 unsigned long long k;
 if(a > b) k = a - b;
 else k = b - a;
  return k;
}
unsigned long long solvey(long long mid){
  unsigned long long a= n * ((n - 1)) / 2 * m * mid + (1 + mid) * (mid )/ 2 * n;
  unsigned long long b = sum - a;
  unsigned long long k;
  if(a > b) k = a - b;
  else k = b - a;
  return k;
}

int main() {
  unsigned long long t;
  cin >> t;
  while(t--){
    cin >> n >> m;
   
    if(n * m >= 1e19){
       while(1);
    }
    char type;
    unsigned long long res;
    unsigned long long ans = 1e19;
    if (n%2 && m%2) sum=(1+n*m)/2*(n*m);
    else sum =  (n * m)/2*(1 + n * m);
    unsigned long long l, r;
    // muriin daguu
    l = 1;
    r = n;
    while(l <= r){
     unsigned long long mid = (l + r) / 2;

    unsigned long long x = solvex(mid);
    unsigned long long y = solvex(mid + 1);
      if(x > y){
         l = mid + 1;
         if(ans > x){
           ans = x;
           type = 'H';
           res = mid + 1;
         }
      }
      else {
        r = mid - 1;
         if(ans > x){
           ans = x;
           type = 'H';
           res = mid + 1;
         }
      }
    }
  // baganiin daguu
    l = 1;
    r = m;
    while(l <= r){
     unsigned long long mid = (l + r) / 2;

     unsigned long long x = solvey(mid);
     unsigned long long y = solvey(mid + 1);
      if(x > y){
         l = mid + 1;
         if(ans > x){
           ans = x;
           type = 'V';
           res = mid + 1;
         }
      }
      else {
        r = mid - 1;
         if(ans > x){
           ans = x;
           type = 'V';
           res = mid + 1;
         }
      }
    }
    cout << type << " " << res << endl;
  }
}
