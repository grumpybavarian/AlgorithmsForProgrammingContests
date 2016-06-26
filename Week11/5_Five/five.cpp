#include <iostream>
#include <stack>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <climits>
using namespace std;

#define INF 10000.0

struct Point
{
    double x, y;
};



//code from: http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
Point p0;

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
    (q.x - p.x) * (r.y - q.y);
    
    if (fabs(val) <= 1e-6) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

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
double distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
    (p1.y - p2.y)*(p1.y - p2.y);
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

stack<Point> convexHull(vector<Point> points)
{
    int n = points.size();
    if (n == 1) {
        stack<Point> s;
        s.push(points[0]);
        return s;
    }
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;
        
        // Pick the bottom-most or choose the left
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
    if (m < 3) {
        stack<Point> st;
        for (int i=0; i<m; ++i) {
            st.push(points[i]);
        }
        return st;
    }
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

//used code from http://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
int doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    
    // General case
    if (o1 != o2 && o3 != o4)
        return 1;
    
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return -1;
    
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return -1;
    
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return -1;
    
    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return -1;
    
    return 0; // Doesn't fall in any of the above cases
}

// Returns true if the point p lies inside the polygon[] with n vertices
bool isInside(vector<Point> polygon, Point p)
{
    int n = polygon.size();
    // There must be at least 3 vertices in polygon[]
    
    if (n == 1) {
        return polygon[0].x == p.x && polygon[0].y == p.y;
    }
    if (n == 2) {
        return orientation(polygon[0], p, polygon[1]) == 0 && onSegment(polygon[0], p, polygon[1]);
    }
    if (n < 3)  return false;
    double y = -1000;
    // Create a point for line segment from p to infinite
define_point:
    ++y;
    Point extreme = Point {INF,y};
    
    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do {
        int next = (i+1)%n;
        
        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'
        
        if (doIntersect(polygon[i], polygon[next], p, extreme) == -1) {
            goto define_point;
        }
        if (doIntersect(polygon[i], polygon[next], p, extreme))
        {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(polygon[i], p, polygon[next]) == 0)
                return onSegment(polygon[i], p, polygon[next]);
            
            count++;
        }
        i = (next+1)%n;
    } while (i != 0);
    
    // Return true if count is odd, false otherwise
    return count&1;  // Same as (count%2 == 1)
}
//end of used code from http://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        vector<Point> posts(2*n);
        double minX = 1000, maxX = 0, minY = 1000, maxY = 0;
        for (int i=0; i<n; ++i) {
            double a,b;
            cin >> a >> b;
            if (a > maxX) {
                maxX = a;
            }
            if (a < minX) {
                minX = a;
            }
            if (b > maxY) {
                maxY = b;
            }
            if (b < minY) {
                minY = b;
            }
            posts[2*i] = Point {a,b};
            if (i != 0)
                posts[(2*i-1)] = Point {a,b};
            else
                posts[2*n-1] = Point {a,b};
        }
        
        vector<Point> shards;
        for (int i=minX-1; i<=maxX+1; ++i) {
            for (int j=minY-1; j<=maxY+1; ++j) {
                if (isInside(posts, Point {1.0*i,1.0*j})) {
                    shards.push_back(Point {1.0*i,1.0*j});
                }
            }
        }
        
        stack<Point> s;
        if (!shards.empty())
            s = convexHull(shards);
        
        
        cout << "Case #" << ti << ":\n" << s.size() << "\n";
        while (!s.empty()) {
            Point p = s.top();
            s.pop();
            cout << p.x << " " << p.y << "\n";
        }
    }
    
    return 0;
}

/*
 4
 4 0 0 1 0  1 1 0 1
 4
 0.5 0.5
 2.5 0.5
 1.75 1.75
 0.5 2.5
 3
 0.5 0.5
 1 0.5
 0.5 1
 3
 0.5 0.5
 1.5 0.5
 0.5 1.5
 
*/

/*
 4
 4
 1.375 7.578125
 1.484375 7.046875
 9.546875 0.203125
 9.4375 0.734375
 6
 2.15625 5.125
 5.375 1.859375
 8.109375 2.65625
 9.0 4.796875
 5.78125 8.0625
 3.046875 7.265625
 6
 2.296875 9.140625
 2.5 6.828125
 4.875 5.28125
 8.34375 3.234375
 8.140625 5.546875
 5.765625 7.09375
 4
 1.75 8.875
 3.359375 6.609375
 9.109375 3.796875
 7.5 6.0625
*/
/*
 1
 6
 0.9 1.1
 1.1 1
 2.1 2
 3.1 2.9
 2.9 3
 1.9 2
 
*/
/*
 1
 10
 1 1
 2 2
 3 3
 4 4
 5 5
 6 6
 7 7
 8 8
 9 9
 10 10
*/

/*
 1
 4
 1 1
 2 2
 3 3
 4 2
*/