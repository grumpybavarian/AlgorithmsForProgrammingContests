#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
    double x,y;
};

double distance(Point a, Point b) {
    return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}

int main() {
    cout.precision(20);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        vector<Point> p(n);
        for (int i=0; i<n; ++i) {
            double a,b;
            cin >> a >> b;
            p[i] = Point {a,b};
        }
        
        double r = 1000000;
        for (int i=1; i<n; ++i) {
            for (int j=i+1; j<n; ++j) {
                double d = distance(p[i], p[j]);
                if (d < r) r = d;
            }
        }
        if (r == 1000000) r = 0;
        r /= 2;
        
        double r2 = 1000000;
        double r3 = 1000000;
        for (int i=1; i<n; ++i) {
            double d = distance(p[0], p[i]);
            if (d-r < r2) r2 = d-r;
            if (d < r3) r3 = d;
            if (d < r) {
                r = d;
                r2 = 0;
            }
        }
        
        double area = M_PI * r2 * r2 + (n-1) * M_PI * r * r;
        double area2 = M_PI * r3 * r3;
        
        
        cout << "Case #" << ti << ": " << max(area,area2) << "\n";
    }
    
    return 0;
}

/*
 3
 7
 0.0 0.0
 -2.0 0.0
 2.0 0.0
 -1.0 1.732
 1.0 1.732
 -1.0 -1.732
 1.0 -1.732
 3
 -1.0 0.0
 0.0 0.0
 1.0 0.0
 2
 0.0 0.0
 1.0 0.0
*/

/*
 6
 3
 85.89749 8.041092
 13.502266 80.74486
 1.2792587 28.864044
 2
 10.871872 98.02222
 -10.477295 -23.74871
 5
 6.6840286 99.15872
 63.19284 37.411926
 -99.12375 6.2733994
 13.110519 -79.276566
 51.04373 -90.824745
 5
 41.790314 22.764038
 69.2648 -50.786854
 0.49011993 -74.49112
 5.434021 75.42493
 18.820465 -99.197754
 4
 96.94888 -62.5437
 -52.94235 -28.406075
 -36.57235 4.2853622
 27.117096 -20.070099
 5
 -76.06155 -0.68807983
 12.408653 -34.555946
 -44.162727 -99.990585
 79.7007 -27.338135
 -56.049953 22.013031
*/