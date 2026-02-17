#include <cmath>
#include <stack>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#define PI 3.14159265358979323846
#define eps 0.0000001

using namespace std; 
  
struct Point {
    int x, y; 
} p0;

Point nextToTop(stack<Point> &S) { 
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

  
int dist(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(Point p, Point q, Point r) { 
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return val == 0 ? 0 : ((val > 0) ? 1 : 2);
}

int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1;

    return (o == 2)? -1: 1;
}
  
double convexHull(Point points[], int n) { 
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) { 
        int y = points[i].y; 
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) 
            ymin = points[i].y, min = i; 
    }

    swap(points[0], points[min]);
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);
    int m = 1;
    for (int i=1; i<n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i+1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    if (m < 2) return 0;
    if (m < 3) return 2 * sqrt(dist(points[0], points[1]));
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
  
    for (int i = 3; i < m; i++) {
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    vector<Point> hull;
    while (!S.empty()) {
       Point p = S.top();
       hull.push_back(p);
       S.pop();
    }

    double perimeter = 0;
    hull.push_back(hull[0]);
    for (int i = 0; i < hull.size() - 1; i++) {
        perimeter += sqrt(dist(hull[i], hull[i + 1]));
    }
    return perimeter;
}
  
int main() {
    int N, R;
    cin >> N >> R;
    Point points[N];
    for (int i = 0; i < N; i++)
        cin >> points[i].x >> points[i].y;
    double perimeter = convexHull(points, N) + 2 * PI * R - eps;
    cout << round(perimeter) << endl;
    return 0; 
} 