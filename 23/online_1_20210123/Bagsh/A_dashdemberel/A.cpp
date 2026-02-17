#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define ZERO (1e-10)
#define INF int(1e9+1)
#define CL(A,I) (memset(A,I,sizeof(A)))
#define DEB printf("DEB!\n");
#define D(X) cout<<"  "<<#X": "<<X<<endl;
#define EQ(A,B) (A+ZERO>B&&A-ZERO<B)
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
#define IN(n) int n;scanf("%d",&n);
#define FOR(i, m, n) for (int i(m); i < n; i++)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define FT(m, n) FOR(k, m, n)
#define aa first
#define bb second
void ga(int N,int *A){F(N)scanf("%d",A+i);}
#define MX (1<<20)
ll pw(ll n,ll k,ll MOD){
    ll r(1);
    while(k){
        if(k&1)r*=n,r%=MOD;
        n*=n,n%=MOD,k>>=1;
    }
    return r;
}
ll inv(ll a,ll MOD){return pw(a,MOD-2,MOD);}
struct HSH{
    int MOD,N,I[MX],F[MX],P;
    void ini(char*r,int M=1000000007,ll b=257){
        MOD=M,N=strlen(r),P=1,*I=1,I[1]=inv(b,MOD),*F=*r;
        FT(2,N)I[k]=I[k-1]*ll(I[1])%MOD;
        FT(1,N)P=P*b%MOD,F[k]=(ll(P)*r[k]+F[k-1])%MOD;
    }
    ll get(int b,int e){if(b>e)swap(b,e);return (F[e]-ll(b?F[b-1]:0)+MOD)*I[b]%MOD;}
}t,T,r,R;
char s[MX];
int N,X=INF;
bool isP(int b,int e){
    int H=(e-b+1)/2;
    if((e-b+1)&1)return t.get(b,b+H)==r.get(N-1-b-H,N-1-e)&&T.get(b,b+H)==R.get(N-1-b-H,N-1-e);
    return t.get(b,b+H-1)==r.get(N-1-b-H,N-1-e)&&T.get(b,b+H-1)==R.get(N-1-b-H,N-1-e);
}
int main(void){
    scanf("%d%s",&N,s);
    t.ini(s),T.ini(s,1e9+9,661);
    reverse(s,s+N),r.ini(s),R.ini(s,1e9+9,661);
    F(N)if(isP(i,N-1))return printf("%d\n",i),0;
    assert(0);
    return 0;
}
