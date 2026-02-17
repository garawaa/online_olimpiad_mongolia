
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define NMAX 50000
#define LENMAX 20

string cows[NMAX];

struct Entry {
    string st;
    int index;
    bool is_rev;
    bool operator<(Entry const& o) const {
        if (st == o.st) {
            return (!is_rev) && o.is_rev;
        }
        return st < o.st;
    }
};
Entry entries[NMAX*2];

int lowest[NMAX];
int highest[NMAX];

void compute(int n) {
    for (int i = 0; i < n; i++) {
        sort(cows[i].begin(), cows[i].end());

        entries[2*i].st = cows[i];
        entries[2*i].index = i;
        entries[2*i].is_rev = false;

        entries[2*i+1].st = cows[i];
        reverse(entries[2*i+1].st.begin(), entries[2*i+1].st.end());
        entries[2*i+1].index = i;
        entries[2*i+1].is_rev = true;
    }

    sort(entries, entries + (2*n));

    int rev_count = 0;
    for (int i = 0; i < 2*n; i++) {
        if (entries[i].is_rev) {
            rev_count++;
        } else {
            int index = entries[i].index;
            lowest[index] = rev_count + 1;
        }
    }

    int fwd_count = 0;
    for (int i = 2*n-1; i >= 0; i--) {
        if (!entries[i].is_rev) {
            fwd_count++;
        } else {
            int index = entries[i].index;
            highest[index] = n - fwd_count;
        }
    }
}

int main() {
   
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i];
    }

    compute(n);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", lowest[i], highest[i]);
    }
}