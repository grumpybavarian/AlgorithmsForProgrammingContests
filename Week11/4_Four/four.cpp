#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <climits>
#include <string>
using namespace std;

struct Point {
    double x,y;
};
struct Line {
    Point a,b;
    int id;
};

bool pointEqual(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

bool lineEqual(Line a, Line b) {
    return pointEqual(a.a, b.a) && pointEqual(a.b, b.b);
}

bool pointCompare(Point a, Point b) {
    if (a.x == b.x) {
        return a.y > b.y;
    }
    return a.x > b.x;
}

bool lineCompare(Line a, Line b) {
    return pointCompare(a.a, b.a);
}

bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

Point intersection(Line a, Line b) {
    double Ab = b.b.y - b.a.y;
    double Bb = b.a.x - b.b.x;
    double Cb = Ab*b.a.x + Bb*b.a.y;
    
    double Aa = a.b.y - a.a.y;
    double Ba = a.a.x - a.b.x;
    double Ca = Aa*a.a.x + Ba*a.a.y;
    
    double det = Aa*Bb - Ab*Ba;
    if (fabs(det) <= 1e-6) {
        return Point {-1,-1};
    }
    
    double x = (Bb*Ca-Ba*Cb)/det;
    double y = (Aa*Cb-Ab*Ca)/det;
    
    if (x < 0 || x > 1000 || y < 0 || y > 1000) {
        //point outside the box
        return Point {-1,-1};
    }
    
    //check if Point is really on both halflines
    bool onLineA = onSegment(a.a, Point {x,y}, a.b);
    bool onLineB = onSegment(b.a, Point {x,y}, b.b);
    if (onLineA && onLineB) {
        return Point {x,y};
    }
    else {
        return Point {-1,-1};
    }
}

//http://rosettacode.org/wiki/Combinations#C.2B.2B
Point commonIntersection(vector<Line> lines, int k) {
    
    vector<bool> bitmask(lines.size());
    for (int i=0; i<k; ++i) bitmask[i] = true;
    bool possible = true;
    int failedIndex = 0;
    do {
        if (!possible) {
            while (bitmask[failedIndex]) {
                if (!prev_permutation(bitmask.begin(), bitmask.end())) {
                    return Point {-1,-1};
                }
            }
        }
        possible = true;
        //find intersection point
        int c = 0,j = 0;
        Line a,b;
        while (c < 2) {
            if (bitmask[j]) {
                if (c == 0) a = lines[j];
                else b = lines[j];
                ++c;
            }
            ++j;
        }
        Point p = intersection(a, b);
        if (p.x < 0 || p.x > 1000 || p.y < 0 || p.y > 1000) continue;
        for (int i=j; i<lines.size(); ++i) {
            Line l = lines[i];
            if (bitmask[i]) {
                //check if point is on line
                double crossproduct = (p.y-l.a.y)*(l.b.x-l.a.x) - (p.x-l.a.x)*(l.b.y-l.a.y);
                if (fabs(crossproduct) >= 1e-9) {
                    possible = false;
                    failedIndex = i;
                    break;
                }
                if (!onSegment(l.a, p, l.b)) {
                    possible = false;
                    failedIndex = i;
                    break;
                }
            }
        }
        if (possible) return p;
    } while (prev_permutation(bitmask.begin(), bitmask.end()));
    
    return Point {-1,-1};
}


int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,k;
        cin >> n >> k;
        vector<Line> lines(n);
        set<pair<double,double>> intersections;
        for (int i=0; i<n; ++i) {
            double a,b,c,d;
            cin >> a >> b >> c >> d;
            pair<double,double> dir = {c-a,d-b};
            double fac1 = INT_MAX, fac2 = INT_MAX;
            if (fabs(dir.first) > 1e-9) {
                if (dir.first > 0) {
                    fac1 = (1000-a) / dir.first;
                }
                else {
                    fac1 = - a / dir.first;
                }
            }
            if (fabs(dir.second) > 1e-9) {
                if (dir.second > 0) {
                    fac2 = (1000-b) / dir.second;
                }
                else {
                    fac2 = - b / dir.second;
                }
            }
            if (fac1 < fac2) {
                c = a + fac1*dir.first;
                d = b + fac1*dir.second;
            }
            else {
                c = a + fac2*dir.first;
                d = b + fac2*dir.second;
            }
            lines[i] = Line {Point {a,b}, Point {c,d}, i};
            intersections.insert({a,b});
        }
        Point c = commonIntersection(lines, k);
        
        if (c.x == -1) {
            cout << "Case #" << ti << ": no\n";
        }
        else {
            cout << "Case #" << ti << ": " << c.x << " " << c.y << "\n";
        }
    }
    
    return 0;
}

/*
 2
 6 3
 1 1 2 2
 2 5 3 5
 1 7 2 4
 5 1 5 3
 7 3 6 2
 8 2 8 4
 4 3   1 1 1 3   3 1 3 2   2 2 4 3   5 5 3 5
 */
/*
 5
 4 2
 5 9 14 7 5 11 6 10 10 13 3 8 15 4 12 2
 5 4
 8 15 7 13 12 17 9 14 6 19 6 15 22 19 14 15 13 1 10 5
 4 2
 17 3 10 5 19 1 11 4 9 6 13 6 1 6 6 6
 7 6
 1 6 2 13
 15 5 9 2
 10 10 11 13 15 4 6 14
 6 14 8 10
 8 15 6 2
 14 3 1 5
 8 3
 13 11 11 8 2 8 14 6 12 10 12 9 3 12 1 12 11 9 3 1
 6 11 9 11 9 10 10 7 6 14 7 14
 */
/*
 1
 2 2
 1 1 2 2
 0 0 3 3
 */
/*
 1
 10 10
 1 1 2 2
 1 1 2 2
 1 1 2 2
 1 1 2 2
 1 1 2 2
 1 1 2 2
 1 1 2 2
 1 1 2 2
 1 1 2 2
 1 1 2 2
 */