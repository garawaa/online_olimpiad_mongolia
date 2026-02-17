#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int n, m;
vector<vector<int> > a;
vector<pair<char, int> > ans;
bool ok;

void coloring(int color)
{
	ans.clear();
	ok = true;
	vector<vector<int> > b = a;

	vector<int> row(n), col(m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			row[i] += a[i][j] == color, col[j] += a[i][j] == color;

	bool make = true;
	while (make)
	{
		make = false;
		for (int i = 0; i < n; i++)
			if (row[i] > m / 2 && row[i] != m)
			{
				make = true;
				row[i] = m;
				ans.push_back(make_pair('R', i + 1));
				for (int j = 0; j < m; j++)
					col[j] += b[i][j] != color, b[i][j] = color;
			}
		for (int i = 0; i < m; i++)
			if (col[i] > n / 2 && col[i] != n)
			{
				make = true;
				col[i] = n;
				ans.push_back(make_pair('C', i + 1));
				for (int j = 0; j < n; j++)
					row[j] += b[j][i] != color, b[j][i] = color;
			}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ok &= b[i][j] == color;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n >> m;
	a = vector<vector<int> >(n, vector<int>(m));
	map<int, int> cnt;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j], cnt[a[i][j]]++;
	
	vector<pair<int, int> > color;
	for (map<int, int>::reverse_iterator it = cnt.rbegin(); it != cnt.rend(); it++)
		color.push_back(make_pair(it->second, it->first));
   	sort(color.rbegin(), color.rend());
	
	for (int i = 0; i < min(3, (int)color.size()); i++)
	{
		coloring(color[i].second);
		if (ok)
		{
			cout << ans.size() << "\n";
			for (int i = 0; i < ans.size(); i++)
				cout << ans[i].first << "\t" << ans[i].second << "\n"; 
			return 0;
		}	       
	}
	cout << "Impossible\n";

}

