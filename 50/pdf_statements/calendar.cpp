#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>
#include <cstring>

#define all(x) (x).begin(),(x).end()

using namespace std;

const int nmax = 1e5 + 10;
const int mmax = 1e2 + 10;

const int NONE = -1;
const int ANY = 10;

char** s;			//char s[nmax][mmax];
bool** valid_shift;	//bool valid_shift[nmax][mmax];
int* D; 			//int D[mmax];

int** first_digit; 	//int first_digit[nmax][mmax];
int** p; 			// int p[nmax][mmax];
int*** cnt;			// int cnt[nmax][mmax][10];

int n,m;

template <typename T>
T* allocate(int n)
{
	return (T*)calloc(n, sizeof(T));
}

template <typename T>
T** allocate(int n, int m)
{
	T** result = (T**)calloc(n, sizeof(T*));
	for (int i = 0; i < n; i ++)
		result[i] = (T*)calloc(m, sizeof(T));
	return result;
}

template <typename T>
T*** allocate(int n, int m, int k)
{
	T*** result = (T***)calloc(n, sizeof(T**));
	for (int i = 0; i < n; i ++)
	{
		result[i] = (T**)calloc(m, sizeof(T*));
		for (int j = 0; j < m; j ++)
			result[i][j] = (T*) calloc(k, sizeof(T));
	}
	return result;
}

void allocate()
{
	int N = n + 10;
	int M = m + 10;
	s = allocate<char>(N, M);
	valid_shift = allocate<bool>(N,M);
	D = allocate<int>(M);
	first_digit = allocate<int>(N,M);
	p = allocate<int>(N,M);
	cnt = allocate<int>(N,M,11);
}

void init()
{
	for (int i = 0; i < n; i ++)
			for (int j = 0; j < m; j ++)
				first_digit[i][j] = -1;
	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i ++)
		{
			if (i > 0)
			{
				for (int k = 0; k < 10; k ++)
					cnt[i][j][k] = cnt[i-1][j][k];
			}
			if (isdigit(s[i][j]))
				cnt[i][j][s[i][j] - '0'] ++;
		}
	}
};

int get(int column, int row_from, int row_to, int digit)
{
	if (row_from == 0)
		return cnt[row_to][column][digit];
	else
		return cnt[row_to][column][digit] - cnt[row_from - 1][column][digit];
};

int is_unique_range(int column, int row_from, int row_to)
{
	row_to = min(row_to, n - 1);
	int result = 0;
	for (int digit = 0; digit < 10; digit ++)
		result += bool(get(column, row_from, row_to, digit));
	return result <= 1;
};

int get_unique_digit(int column, int row_from, int row_to)
{
	row_to = min(row_to, n - 1);
	int result = -1;
	for (int digit = 0; digit < 10; digit ++)
		if (get(column, row_from, row_to, digit))
		{
			assert(result == -1);
			result = digit;
		}
	return result;
};

int get_first_digit(int column, int shift, int block_size) // -1 - no, 0-9 - d
{
	if (shift > 0) if (!is_unique_range(column, 0, shift - 1)) return NONE;
	for (int i = shift; i < n; i += block_size)
		if (!is_unique_range(column, i, i + block_size - 1)) return NONE;
	int step = 0;
	int uniform = -1;
	if (shift > 0) 
	{
		int d = get_unique_digit(column, 0, shift - 1);
		if (d != -1) 
		{
			int cur_uniform = ((d - step) % 10 + 10) % 10;
			if (uniform != -1 && cur_uniform != uniform) return NONE;
			uniform = cur_uniform;
		}
	}
	for (int i = shift; i < n; i += block_size)
	{
		step ++;
		int d = get_unique_digit(column, i, i + block_size - 1);
		if (d != -1) 
		{
			int cur_uniform = ((d - step) % 10 + 10) % 10;
			if (uniform != -1 && cur_uniform != uniform) return NONE;
			uniform = cur_uniform;
		}
	}
	if (uniform == -1) 
		return ANY;
	else
		return uniform;
};

int next(int digit)
{
	if (digit == 9) return 0;
	return digit + 1;
}

int main()
{
//	freopen("calendar.in","r",stdin);
//	freopen("calendar.out","w",stdout);
	scanf("%d%d\n", &n, &m);
	allocate();
	for (int i = 0; i < n; i ++)
		scanf("%s", s[i]);
	init();
	int d = 1;
	valid_shift[0][m-1] = 1;
	for (int j = m - 1; j >= 0; j --)
	{
		D[j] = d;
		int nextd = min(n, d * 10);
		for (int shift = 0; shift < d; shift ++)
			if (valid_shift[shift][j])
			{
				int digit = get_first_digit(j, shift, d);
				if (digit == NONE) 
				{
					valid_shift[shift][j] = 0;
					continue;
				}
				if (j > 0)
				{
					for (int k = 0; k < 10; k ++)
						if (digit == ANY || ((digit + k) % 10 == 9))
						{
							int pos = shift + k * d;
							if (pos >= n) pos = 0;
							if (!valid_shift[pos][j-1])
							{
								valid_shift[pos][j-1] = 1;
								p[pos][j-1] = shift;
								first_digit[pos][j-1] = ((9 - k) % 10 + 10) % 10;
							}
						}
				}
			}
		if (j > 0)
			d = nextd;
	}
	int shift = -1;
	for (int i = 0; i < d; i ++)
		if (valid_shift[i][0])
			shift = i;
	if (shift == -1)
	{
		assert(false);
		return 0;
	}
	int digit = get_first_digit(0, shift, D[0]);
	if (digit == ANY) digit = 0;
	for (int j = 0; j < m; j ++)
	{
		for (int i = 0; i < shift; i ++)
			s[i][j] = digit + '0';
		int _digit = digit;
		for (int i = shift; i < n; i += D[j])
		{	
			_digit = next(_digit);
			for (int k = i; k < i + D[j] && k < n; k ++)
				s[k][j] = _digit + '0';
		}
		digit = first_digit[shift][j];
		shift = p[shift][j];
	}
	printf("%s\n", s[0]);
	return 0;
};
