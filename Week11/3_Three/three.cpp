//code used from:http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Point
{
    long x, y;
};

// A globle point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;

// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
    (p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    long val = (q.y - p.y) * (r.x - q.x) -
    (q.x - p.x) * (r.y - q.y);
    
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    
    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
    
    return (o == 2)? -1: 1;
}

// Prints convex hull of a set of n points.
stack<Point> convexHull(vector<Point> points, int n)
{
    // Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;
        
        // Pick the bottom-most or chose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y &&
                           points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }
    
    // Place the bottom-most point at first position
    swap(points[0], points[min]);
    
    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted ouput if p2
    // has larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);
    
    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i=1; i<n; i++)
    {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        while (i < n-1 && orientation(p0, points[i],
                                      points[i+1]) == 0)
            i++;
        
        
        points[m] = points[i];
        m++;  // Update size of modified array
    }
    
    // If modified array of points has less than 3 points,
    // convex hull is not possible
    if (m < 3) return stack<Point>();
    
    // Create an empty stack and push first three points
    // to it.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
    
    // Process remaining n-3 points
    for (int i = 3; i < m; i++)
    {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }
    
    return S;
}
//end of used code from: http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/

bool compPoints(Point a, Point b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    else {
        return a.y < b.y;
    }
}

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        vector<Point> p(n);
        for (int i=0; i<n; ++i) {
            int a,b,c,d;
            cin >> a >> b >> c >> d;
            p[i] = Point {a,b};
        }
        
        stack<Point> s = convexHull(p, n);
        vector<Point> points;
        while (!s.empty()) {
            points.push_back(s.top());
            s.pop();
        }
        sort(points.begin(), points.end(), compPoints);
        
        cout << "Case #" << ti << ":\n" << points.size() << "\n" ;
        for (int i=0; i<points.size(); ++i) {
            cout << points[i].x << " " << points[i].y << "\n";
        }
    }
    
    
    
    return 0;
}

/*
 2
 4
 0 0 5 1206819015
 2 0 3 1370787905
 0 2 2 1437771333
 1 1 1 1206819015
 6
 0 0 1 1119068743
 5 0 0 1396647891
 2 2 6 1288114097
 2 2 4 1312119233
 0 5 2 1353372240
 4 4 3 1132073132
 */
/*
 3
 5
 4 3 6 1278834253
 6 4 3 1200462317
 6 5 3 1338036361
 1 2 7 1451894583
 7 1 4 1163900825
 5
 6 2 0 1401981377
 3 7 1 1288451418
 3 6 0 1117297905
 3 3 5 1394979583
 2 2 1 1216124543
 6
 1 1 6 1188646063
 4 3 6 1278834253
 6 4 3 1200462317
 6 5 3 1338036361
 1 2 7 1451894583
 7 1 4 1163900825
 */
/*
 1
 10
 700484 890872 0 0
 764998 400030 0 0
 402569 736647 0 0
 918897 810398 0 0
 823613 954714 0 0
 292949 282641 0 0
 978295 431456 0 0
 442009 711204 0 0
 309039 142224 0 0
 605114 923605 0 0
*/