#include<iostream>
using namespace std;

  int x[1001], y[1001];
  int ix[1001], iy[1001];
  int c[1001];
  int i, j, k, num, m, n, t;

int main(){
  //freopen("09.i","r",stdin);
 // freopen("09.aa","w",stdout);

  cin>>n>>m;

  for(i=1;i<=n;i++)
  {
    cin>>x[i];
    ix[i] = i; 
  }
for(i=1;i<=m;i++)
{
    cin>>y[i];
    iy[i] = i; 
}

  for(i=1;i<n;i++)
    for(j= i+1; j<=n;j++)
      if (x[ix[i]] < x[ix[j]])
      {
        t = ix[i]; ix[i] = ix[j]; ix[j] = t;
      }

  for(i = 1; i<m;i++)
    for (j = i + 1;j<=m;j++)
      if (y[iy[i]] < y[iy[j]])
      {
        t = iy[i]; iy[i] = iy[j]; iy[j] = t;
      }

  num = 0; 
  j = 1; 
  for (i=1; i<=n;i++)
  {
    if (x[ix[i]] < y[iy[j]]) 
    {
      c[ix[i]] = iy[j];
      j++;
      num++;
    }
  }

  cout<<num<<endl;
  for (i = 1;i<=n;i++)
    cout<<c[i]<<" ";
return 0;
}
