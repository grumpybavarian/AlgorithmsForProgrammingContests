#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <cmath>
using namespace std;

struct Point {
    double x,y,z;
};

Point crossproduct (Point a, Point b) {
    Point p;
    p.x = a.y*b.z - a.z*b.y;
    p.y = a.z*b.x - a.x*b.z;
    p.z = a.x*b.y - a.y*b.x;
    return p;
}

Point norm(Point a) {
    a.x /= a.z;
    a.y /= a.z;
    a.z = 1;
    double l = sqrt(a.x*a.x+a.y*a.y);
    a.x /= l;
    a.y /= l;
    return a;
}

int main() {
    cout.precision(15);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,d,a;
        string s;
        cin >> n >> d >> a >> s;
        map<char,string> prod;
        for (int i=0; i<n; ++i) {
            char c,e,p;
            cin >> c >> e >> p; //ignore e and p (=>)
            string r;
            cin >> r;
            prod[c] = r;
        }
        double theta = a*M_PI/180.0;
        
        string t = "";
        for (int j=0; j<d; ++j) {
            t = "";
            for (int i=0; i<s.length(); ++i) {
                if (s[i] == '+' || s[i] == '-') {
                    t += s[i];
                    continue;
                }
                t.append(prod[s[i]]);
            }
            s = t;
        }
        cout << "Case #" << ti << ":\n";
        Point p {0,0,1};
        Point dir {1,0,1};
        
        cout << p.x << " " << p.y << "\n";
        for (int i=0; i<s.length(); ++i) {
            if (s[i] == '+') {
                double cs = cos(theta);
                double sn = sin(theta);
                double px = dir.x*cs - dir.y*sn;
                double py = dir.x*sn + dir.y*cs;
                dir.x = px;
                dir.y = py;
            }
            else if (s[i] == '-') {
                double cs = cos(-theta);
                double sn = sin(-theta);
                double px = dir.x*cs - dir.y*sn;
                double py = dir.x*sn + dir.y*cs;
                dir.x = px;
                dir.y = py;
            }
            else {
                p.x = p.x + dir.x;
                p.y = p.y + dir.y;
                cout << p.x << " " << p.y << "\n";
            }
        }
    }
    return 0;
}

/*
 3
 1 3 30 L
 L=>LL+
 2 3 45 L
 R=>+R--L+
 L=>-R++L-
 2 1 60 L
 R=>R+L++L-R--RR-L+
 L=>-R+LL++L+R--R-L
*/
/*
 1
 2 15 45 L
 R=>+R--L+
 L=>-R++L-
*/
/*
 1
 2 5 60 L
 R=>R+L++L-R--RR-L+
 L=>-R+LL++L+R--R-L
*/
/*
 1
 1 6 60 F--F--F
 F=>F+F--F+F
*/
/*
 1
 1 15 45 F
 F=>+F--F+
*/
/*
 1
 2 8 60 FXF--FF--FF
 X=>--FXF++FXF++FXF--
 F=>FF
*/
/*
 1
 1 5 60 +L--L
 L=>LL
 */
/*
 1
 1 10 37 L
 L=>L+L
*/