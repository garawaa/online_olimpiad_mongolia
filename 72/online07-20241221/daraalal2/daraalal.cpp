#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<long long> vl;

int N;
vl A;

vl f(){
	vl B(N);
	for(int i=1;i<N;i++) B[i]=max(A[i-1]-A[i]+1,0LL)+B[i-1];
	reverse(A.begin(),A.end());
	return B;
}

int main(){
	cin>>N;
	A=vl(N);
	for(int i=0;i<N;i++) cin>>A[i];
	vl B=f(),C=f();
	long long res=1LL<<60;
	for(int i=0;i<N;i++) res=min(res,max(B[i],C[N-i-1]));
	cout<<res<<endl;
}