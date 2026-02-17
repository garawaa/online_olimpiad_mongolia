#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

void ac(const string& okmessage) {
    cout << "1" << endl;
    cerr << okmessage;
    exit(0);
}

void wa(const string& errorMessage) {
    cout << "0" << endl;
    cerr << errorMessage;
    exit(0);
}

	class Point {
		public: 
			double x, y;

		Point(double x, double y):x(x),y(y){}
		
		double length() {
			return sqrt(x * x + y * y);
		}
		
		double dist(Point &p2) {
			return sqrt((x - p2.x) * (x - p2.x) + (y - p2.y) * (y - p2.y)); 
		}
	};

	double veryBig = 1100;
	double eps = 0.000001;
	

int main(int argc, char **argv) {

    ifstream inf(argv[1]), ouf(argv[2]), ans(argv[3]);
	double xx,yy,r,l;
		ans>>xx>>yy;
		Point p1(xx,yy);
		ans>>xx>>yy;
		Point p2(xx, yy);
		if (p1.x >= veryBig || p1.x <= -veryBig ||
				p1.y >= veryBig || p1.y <= -veryBig ||
						p2.x >= veryBig || p2.x <= -veryBig ||
								p2.y >= veryBig || p2.y <= -veryBig) {
			wa("Too big coordinates");
		}

		inf>>r>>l;
		
		if (abs(p1.length() - r) > eps) {
			wa("Point1 out of circle");
		}
		if (abs(p2.length() - r) > eps) {
			wa("Point2 out of circle");
		}
		l = min(2 * r, l);
		if (abs(p1.dist(p2) - l) > eps) {
			wa("Distance between points differ from right distance");
		}
        ac("Таны хариулт зөв байна");
}
