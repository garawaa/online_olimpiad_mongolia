#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n, m, a[MAXN], b[MAXN];

bool trial(int x){
	int ptr = 0;
	for(int i=0; i<n; i++){
		while(ptr < m && b[ptr] < a[i] - x) ptr++;
		if(ptr == m || b[ptr] > a[i] + x) return 0;
		ptr++;
	}
	return 1;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	for(int i=0; i<m; i++) scanf("%d",&b[i]);
	if(n > m){
		swap(n, m);
		for(int i=0; i<max(n, m); i++) swap(a[i], b[i]);
	}
	sort(a, a+n);
	sort(b, b+m);
	int s = 0, e = 1e9;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	cout << s << endl;
}
