#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct tn {
    int a,b,p;
};

bool comp(tn a, tn b) {
    return a.b < b.b;
}

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        vector<tn> t(n);
        for (int i=0; i<n; ++i) {
            int a,b,p;
            cin >> a >> b >> p;
            t[i] = tn {a,b,p};
        }
        sort(t.begin(), t.end(), comp);
        
        vector<int> m(n);
        for (int i=0; i<n; ++i) {
            m[i] = t[i].p;
        }
        for (int i=1; i<n; ++i) {
            for (int j=0; j<i; ++j) {
                if ((t[i].a <= t[j].a && t[i].b >= t[j].a) || (t[i].a <= t[j].b && t[i].b >= t[j].b)) continue;
                if (m[j] + t[i].p > m[i]) {
                    m[i] = m[j] + t[i].p;
                }
            }
        }
        
        int w = 0;
        for (int i=0; i<n; ++i) {
            if (m[i] > w) w = m[i];
        }
        
        
        cout << "Case #" << ti << ": " << w << endl;
    }
    return 0;
}
