#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct activity {
    string name;
    int fun;
    int len;
};

bool compareActivities (activity a, activity b) {
    return a.fun > b.fun;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,m;
        cin >> n >> m;
        m *= 60;
        vector<activity> v(n);
        for (int i=0; i<n; ++i) {
            string name;
            int fun, len;
            cin >> name >> fun >> len;
            v[i] = activity {name,fun,len};
        }
        
        sort(v.begin(), v.end(), compareActivities);
        
        int minutes = 0;
        int fun = 0;
        for (int i=0; i<n; ++i) {
            if (v[i].len <= m) {
                fun += v[i].len * v[i].fun;
                m -= v[i].len;
            }
            else {
                fun += m * v[i].fun;
                break;
            }
        }
        
        cout << "Case #" << ti << ": " << fun << endl;
    }
    
    return 0;
}
