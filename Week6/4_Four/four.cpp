#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        vector<vector<int>> adj(n, vector<int>(n));
        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                cin >> adj[i][j];
            }
        }
        
        vector<int> order(n);
        
        for (int i=0; i<n; ++i) {
            order[i] = i;
        }
        
        bool x = true;
        int minDist = INT_MAX;
        vector<int> minPath = order;
        while (x) {
            int dist = 0;
            for (int i=0; i<n-1; ++i) {
                dist += adj[order[i]][order[i+1]];
            }
            dist += adj[order[n-1]][order[0]];
            if (dist < minDist) {
                minDist = dist;
                minPath = order;
            }
            x = next_permutation(order.begin(), order.end());
        }
        
        
        cout << "Case #" << ti << ":";
        for (int i=0; i<n; ++i) {
            cout << minPath[i]+1 << " ";
        }
        cout << endl;
    }
    return 0;
}
