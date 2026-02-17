#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
#include <cassert>

using namespace std;

long long a, c;

long long calc(long long r, long long g, long long b)
{
	return a * (r * r + g * g + b * b) + c * min(min(r, g), b);
}

int main()
{
//	ifstream cin("bet.in");
//	ofstream cout("bet.out");
	int t;
	cin >> t;
	while (t--)
	{
     	long long r, g, b;
     	cin >> a >> c;
     	cin >> r >> g >> b;
     	int color = 1;
     	long long ans = calc(r + 1, b, g);
     	if (ans < calc(r, b + 1, g))
     	{
     		ans = calc(r, b + 1, g);
     		color = 2;
     	}
     	if (ans < calc(r, b, g + 1))
     	{
     		ans = calc(r, b, g + 1);
     		color = 3;
     	}
     	switch (color) 
     	{
     		case 1: cout << "RED\n"; break;
     		case 2: cout << "BLUE\n"; break;
     		case 3: cout << "GREEN\n"; break;
     		default: assert(false); break;	
     	}
	}
}
