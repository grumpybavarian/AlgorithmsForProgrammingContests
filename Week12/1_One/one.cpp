#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    long double x,y,z;
};



Point crossproduct (Point a, Point b) {
    Point p;
    p.x = a.y*b.z - a.z*b.y;
    p.y = a.z*b.x - a.x*b.z;
    p.z = a.x*b.y - a.y*b.x;
    return p;
}

Point orthogonalize(Point a) {
    Point b;
    b.x = -a.y;
    b.y = a.x;
    b.z = a.z;
    return b;
}

int main() {
    cout.precision(18);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        long double x,y;
        Point a, b, c;
        cin >> x >> y;
        a = Point {x,y,1};
        cin >> x >> y;
        b = Point {x,y,1};
        cin >> x >> y;
        c = Point {x,y,1};

        Point lineAB, lineAC, lineBC;
        lineAB = crossproduct(a, b);
        lineAC = crossproduct(a, c);
        lineBC = crossproduct(b, c);
        
        cout << "Case #" << ti << ":\n";
        //centroid (intersection of medians)
        cout << (a.x+b.x+c.x)/3 << " " << (a.y+b.y+c.y)/3 << "\n";
        
        //orthocenter (intersection of altitudes)
        Point altAB, altAC;
        altAB = crossproduct(crossproduct(lineAB, crossproduct(c, orthogonalize(crossproduct(lineAB, Point {0,0,1})))),c);
        altAC = crossproduct(crossproduct(lineAC, crossproduct(b, orthogonalize(crossproduct(lineAC, Point {0,0,1})))),b);
        Point intersect = crossproduct(altAB, altAC);
        intersect.x /= intersect.z;
        intersect.y /= intersect.z;
        cout << intersect.x << " " << intersect.y << "\n";
        
        //circumcenter (intersection of perpendicular bisectors)
        Point midAB, midAC;
        midAB = Point {(a.x+b.x)/2, (a.y+b.y)/2,1};
        midAC = Point {(a.x+c.x)/2, (a.y+c.y)/2,1};
        Point bisecAB, bisecAC;
        Point oAB = Point {-(b.y-a.y)+midAB.x, b.x-a.x+midAB.y, 1};
        Point oAC = Point {-(c.y-a.y)+midAC.x, c.x-a.x+midAC.y, 1};
        bisecAB = crossproduct(midAB, oAB);
        bisecAC = crossproduct(midAC, oAC);
        intersect = crossproduct(bisecAB, bisecAC);
        intersect.x /= intersect.z;
        intersect.y /= intersect.z;
        cout << intersect.x << " " << intersect.y << "\n";
    }
    return 0;
}

/*
 2
 0.0 0.0
 1.0 0.0
 0.0 1.0
 1.0 1.0
 99.123 -12.5
 58.54 -32.643
 
 */



















