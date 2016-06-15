#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cmath>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        int g;
        cin >> g;
        for (int i=0; i<n-1; ++i) {
            int b;
            cin >> b;
            g = __gcd(b,g);
        }
        cout << "Case #" << ti << ": " << g << endl;
    }
    
    return 0;
}

/*
 2
 3
 12 6 21
 4
 24 7 12 18
*/