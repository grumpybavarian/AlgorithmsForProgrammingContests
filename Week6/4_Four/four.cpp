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

/*
 2
 4
 0 11 8 8
 11 0 11 3
 8 11 0 10
 8 3 10 0
 4
 0 10 12 5
 10 0 8 13
 12 8 0 7
 5 13 7 0
*/
/*
 1 8
 0 1 1 1 1 1 1 1
 1 0 1 1 1 1 1 1
 1 1 0 1 1 1 1 1
 1 1 1 0 1 1 1 1
 1 1 1 1 0 1 1 1
 1 1 1 1 1 0 1 1
 1 1 1 1 1 1 0 1
 1 1 1 1 1 1 1 0
*/
/*
 10
 4 0 7 4 2 7 0 1 4 4 1 0 9 2 4 9 0
 4 0 7 3 3 7 0 3 2 3 3 0 7 3 2 7 0
 3 0 2 2 2 0 2 2 2 0
 3 0 5 9 5 0 6 9 6 0
 4 0 9 1 7 9 0 2 10 1 2 0 9 7 10 9 0
 3 0 8 8 8 0 2 8 2 0
 3 0 2 1 2 0 4 1 4 0
 5 0 8 8 3 4 8 0 7 4 1 8 7 0 10 1 3 4 10 0 7 4 1 1 7 0
 4
 0 10 6 3 10 0 6 2 6 6 0 8 3 2 8 0
 3 0 2 1 2 0 1 1 1 0
*/