#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
    long double a,b;
};

struct Line {
    double a, b, c;
};

//used from http://math.stackexchange.com/questions/65503/point-reflection-over-a-line
Point mirrorPoint (Point p, double x1, double y1, double x2, double y2) {
    double dx,dy,a,b;
    dx = x2-x1;
    dy = y2-y1;
    
    a = (dx*dx - dy*dy) / (dx*dx+dy*dy);
    b = 2 * dx * dy / (dx*dx + dy*dy);
    
    double xN, yN;
    xN = a*(p.a-x1) + b*(p.b-y1)+x1;
    yN = b*(p.a-x1) - a*(p.b-y1)+y1;
    
    return Point {xN,yN};
}
//end of used code from: http://math.stackexchange.com/questions/65503/point-reflection-over-a-line

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        long double xLea, yLea;
        cin >> xLea >> yLea;
        long double xSnow, ySnow;
        cin >> xSnow >> ySnow;
        long double xWall1, xWall2, yWall1, yWall2;
        cin >> xWall1 >> yWall1 >> xWall2 >> yWall2;
        long double xEnemy, yEnemy;
        cin >> xEnemy >> yEnemy;
        long double xAct, yAct;

        Point act = mirrorPoint(Point {xEnemy, yEnemy}, xWall1, yWall1, xWall2, yWall2);
        xAct = act.a;
        yAct = act.b;

        cout << "Case #" << ti << ": " << xAct << " " << yAct << "\n";
    }
    
    return 0;
}
