#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <math.h>
using namespace std;

#define x first
#define y second
typedef pair<double,double> Point;

double area(vector<Point> p) {
    double sumCP = 0;
    int n = p.size();
    for (int i=0; i<n-1; ++i) {
        sumCP += (p[i].x+p[i+1].x) * (p[i].y-p[i+1].y);
    }
    sumCP += (p[n-1].x+p[0].x) * (p[n-1].y-p[0].y);
    sumCP = fabs(sumCP);
    return sumCP;
}

int main() {
    cout.precision(15);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,m;
        cin >> n >> m;
        vector<Point> p(n);
        for (int i=0; i<n; ++i) {
            double a,b;
            cin >> a >> b;
            p[i] = {m*a,m*b};
        }
        double origArea = area(p);
        
        vector<Point> newPoints;
        
        
        for (int i=0; i<n; ++i) {
            Point a = p[i];
            Point b;
            if (i==0) b = p[n-1];
            else b = p[i-1];
            
            Point c,d;
            c.x = b.x + 1.0/m * (a.x-b.x);
            c.y = b.y + 1.0/m * (a.y-b.y);
            
            newPoints.push_back(c);
            if (m == 2) continue;
            
            d.x = a.x + 1.0/m * (b.x-a.x);
            d.y = a.y + 1.0/m * (b.y-a.y);
            newPoints.push_back(d);
        }

        
        double newArea = area(newPoints);
        
        cout << "Case #" << ti << ": " << (origArea-newArea) << "/" << origArea << endl;
    }
    return 0;
}

/*
 2 4 2 1 0 1 1 0 1 0 0
 3 10 20 0 0 20 1 1
*/
/*
 8
 5 96
 82 395
 96 446
 666 862
 855 996
 285 506
 4 990
 311 318
 974 475
 332 394
 77 287
 3 828
 332 59
 118 981
 904 105
 4 558
 825 462
 573 575
 127 304
 639 284
 7 48
 928 669
 919 803
 837 842
 275 972
 170 414
 209 104
 787 55
 7 709
 661 162
 974 323
 985 803
 206 542
 67 429
 27 170
 28 97
 5 263
 983 359
 943 900
 228 821
 14 694
 538 15
 4 857
 580 163
 167 745
 364 826
 601 516
*/