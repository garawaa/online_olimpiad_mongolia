#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define B 0
#define E 1
struct KeyPoint {
    int t;
    int cow;
    int newdir;
    KeyPoint(int t, int cow, int newdir)
        : t(t), cow(cow), newdir(newdir) { }
    bool operator<(KeyPoint const& o) const {
        return t < o.t;
    }
};

vector<KeyPoint> keyPoints;
int readKeyPoints(int n, int cow) {
    int t = 0;
    int initdir;
    for (int i = 0; i < n; i++) {
        int dt;
        scanf("%d", &dt);

        char c;
        do {
            c = fgetc(stdin);
        } while (c != 'L' && c != 'R');
        int dir = (c == 'R' ? 1 : -1);

        if (t == 0) {
            initdir = dir;
        } else {
            keyPoints.push_back(KeyPoint(t, cow, dir));
        }

        t += dt;
    }
    keyPoints.push_back(KeyPoint(t, cow, 0));
    return initdir;
}

int main() {
    int nSteps1, nSteps2;
    freopen("input.0", "r", stdin);
    scanf("%d", &nSteps1);
    scanf("%d", &nSteps2);

    int dir1 = readKeyPoints(nSteps1, B);
    int dir2 = readKeyPoints(nSteps2, E);

    sort(keyPoints.begin(), keyPoints.end());
    
    int t = 0;
    int x1 = 0;
    int x2 = 0;

    int nMoos = 0;

    for (int i = 0; i < keyPoints.size(); i++) {      
        int new_t = keyPoints[i].t;
        int new_x1 = x1 + (new_t - t) * dir1;
        int new_x2 = x2 + (new_t - t) * dir2;
        if (x1 != x2 && (new_x1 == new_x2 || ((x1 < x2) ^ (new_x1 < new_x2)))) {
            nMoos++;
        }
        t = new_t;
        x1 = new_x1;
        x2 = new_x2;
        if (keyPoints[i].cow == B) {
            dir1 = keyPoints[i].newdir;
        } else {
            dir2 = keyPoints[i].newdir;
        }
    }
    printf("%d\n", nMoos);
}

//http://www.usaco.org/index.php?page=viewproblem2&cpid=205