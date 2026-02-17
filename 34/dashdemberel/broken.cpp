#include <bits/stdc++.h>
using namespace std;

bool solve(string s, string t){
	int n = s.size();
	if(n == 0) return 1;
	string a = "", b = "";
	for(int i = 1; i <= n; i++){
		a = s[n - i] + a;
		b = b + t[i - 1];
		if(a == b){
			a = "";
			b = "";
			for(int j = 0; j < n - i; j++){
				a += s[j];
			}
			for(int j = i; j < n; j++){
				b += t[j];
			}
			return solve(a, b);
		}
	}
	return 0;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	string s, t;
	cin >> s >> t;
	cout << (solve(s, t) == 1 ? "Yes" : "No");
}