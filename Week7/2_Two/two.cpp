#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int l,n,d;
        cin >> l >> n >> d;
        vector<int> positions(n);
        for (int i=0; i<n; ++i) {
            cin >> positions[i];
        }
        sort(positions.begin(), positions.end());
        int numLights = 0;
        
        int curPos = 0;
        int index = -1;
        while (true) {
            if (curPos >= l || index == n-1 || positions[index+1] > curPos + d) {
                break;
            }
            for (int i=index; i<n; ++i) {
                if (positions[i] > curPos + d) break;
                index = i;
            }
            ++numLights;
            curPos = positions[index] + d;
        }
        
        if (curPos < l)
            cout << "Case #" << ti << ": impossible\n";
        else
            cout << "Case #" << ti << ": " << numLights << endl;
    }
    
    return 0;
}
