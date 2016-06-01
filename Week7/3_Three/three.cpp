#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,m;
        cin >> n >> m;
        vector<long> l(n);
        multiset<long> times;
        multiset<long> saws;
        long totalTime = 0;
        long maxTime = 0;
        for (int i=0; i<n; ++i) {
            long a;
            cin >> a;
            times.insert(a);
        }
        for (int i=0; i<m; ++i) {
            saws.insert(0);
        }
        
        while (!times.empty()) {
            long nextJob = *(--times.end());
            times.erase(--times.end());
            long nextSawLength = *saws.begin();
            nextSawLength += nextJob;
            saws.erase(saws.begin());
            saws.insert(nextSawLength);
        }
        
        
        
        cout << "Case #" << ti << ": " << *(--saws.end()) << endl;
    }
    
    return 0;
}
