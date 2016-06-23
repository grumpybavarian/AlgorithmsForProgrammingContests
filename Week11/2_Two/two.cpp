//Code used from: http://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/ (slightly modified)
#include <iostream>
#include <vector>
using namespace std;

// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000

struct Point
{
    int x;
    int y;
};

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
    (q.x - p.x) * (r.y - q.y);
    
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
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
bool isInside(vector<Point> polygon, int n, Point p)
{
    // There must be at least 3 vertices in polygon[]
    if (n < 3)  return false;
    int y = -1000;
    // Create a point for line segment from p to infinite
define_point:
    ++y;
    Point extreme = {INF, y};
    
    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
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
        int x,y,n;
        cin >> x >> y >> n;
        
        vector<Point> polygon(2*n);
        for (int i=0; i<n; ++i) {
            int a,b,c,d;
            cin >> a >> b >> c >> d;
            polygon[2*i] = Point {a,b};
            polygon[2*i+1] = Point {c,d};
        }
        
        if (isInside(polygon, 2*n, Point {x,y}))
            cout << "Case #" << ti << ": jackpot\n";
        else
            cout << "Case #" << ti << ": too bad\n";
    }
    
    return 0;
}

/*
 2
 1 1 3 1 0 2 2 2 2 0 1 0 1 1 0
 0 1 5
 -1 -1 -1 2 1 1 1 0
 1 0 -1 -1 0 0 1 1
 -1 2 0 0
*/
/*
 3
 -3 4 10
 5 0 2 -2
 1 -2 0 -5
 2 -2 1 -2
 -2 -1 -5 -1
 0 -5 -1 -1
 -5 -1 -5 0
 -2 3 5 0
 -5 0 -2 4
 -2 4 -2 3
 -1 -1 -2 -1
 
 -2 0 10
 -4 -1 -5 0
 -1 1 0 4
 -5 0 -5 1
 -5 1 -1 1
 5 0 3 -4
 3 -4 2 -5
 0 4 4 4
 -2 -1 -4 -1 
 4 4 5 0
 2 -5 -2 -1
 
 3 -3 9 
 1 3 5 0
 -5 0 -5 3
 5 0 1 -4
 -5 3 -3 3 0 3 1 3
 -3 3 0 3
 -3 -2 -5 -3 -5 -3 -5 0 1 -4 -3 -2
*/
/*
 1
 -1 0 4
 4 4 0 4
 0 0 0 4
 4 0 0 0
 4 0 4 4
*/