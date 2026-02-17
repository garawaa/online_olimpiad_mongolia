#include <bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;
char a[5],b[5],c[5],d[5];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int i=0;i<5;i++){
		cin >> a[i];
	}
	for(int i=0;i<5;i++){
		cin >> b[i];
	}
	for(int i=0;i<5;i++){
		cin >> c[i];
	}
	for(int i=0;i<5;i++){
		cin >> d[i];
	}
	ll a1=(a[0]-'0');
	ll a2=(a[1]-'0');
	ll a3=(a[3]-'0');
	ll a4=(a[4]-'0');
	ll b1=(b[0]-'0');
	ll b2=(b[1]-'0');
	ll b3=(b[3]-'0');
	ll b4=(b[4]-'0');
	ll c1=(c[0]-'0');
	ll c2=(c[1]-'0');
	ll c3=(c[3]-'0');
	ll c4=(c[4]-'0');
	ll d1=(d[0]-'0');
	ll d2=(d[1]-'0');
	ll d3=(d[3]-'0');
	ll d4=(d[4]-'0');
	ll aa=(a1*10+a2)*60+a3*10+a4;
	ll bb=(b1*10+b2)*60+b3*10+b4;
	ll cc=(c1*10+c2)*60+c3*10+c4;
	ll dd=(d1*10+d2)*60+d3*10+d4;
	// cout << aa << ' ' << bb << ' ' << cc << ' ' << dd << endl;
	ll o;
	bool flag=0;
	for(ll i=0;i<=20000000;i++){
		if(((cc*i+aa-bb)%dd+dd)%dd==0 && (cc*i+aa-bb)>=dd){
			flag=1;
			o=cc*i+aa;
			break;
		}
	}
	// cout << k << '\n';
	if(flag==0){
		cout << "Never";
		return 0;
	}
	else{
		// cout << o << '\n';
		ll y=o/1440;
		ll z=o%1440;
		if(y%7==0){
			cout << "Saturday\n";
		}
		if(y%7==1){
			cout << "Sunday\n";
		}
		if(y%7==2){
			cout << "Monday\n";
		}
		if(y%7==3){
			cout << "Tuesday\n";
		}
		if(y%7==4){	
			cout << "Wednesday\n";
		}
		if(y%7==5){
			cout << "Thursday\n";
		}
		if(y%7==6){
			cout << "Friday\n";
		}
		ll hour=z/60;
		ll minut=z%60;
		if(hour<10){
			cout << 0 << hour << ':';
		}
		else cout << hour << ':';
		if(minut<10){
			cout << 0 << minut;
		}
		else cout << minut;
	}
}