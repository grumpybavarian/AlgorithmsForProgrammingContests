#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        vector<vector<int>> t(n,vector<int>(n));
        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                cin >> t[i][j];
            }
        }
        
        vector<bool> visited(n);
        vector<int> dist(n);
        set<pair<int,int>> pq;
        pq.insert({0,0});
        visited[0] = true;
        while (!pq.empty()) {
            int next = pq.begin()->second;
            visited[next] = true;
            pq.erase(pq.begin());
            for (int i=1; i<n; ++i) {
                if (t[i][next] == 0) continue;
                if (dist[i] < t[i][next]) {
                    pq.erase({-dist[i],i});
                    dist[i] = t[i][next];
                    pq.insert({-dist[i],i});
                }
            }
        }
        int sum = 0;
        for (auto i : dist) {
            sum += i;
        }
        
        cout << "Case #" << ti << ": " << sum << "\n";
    }
    return 0;
}

/*
 2
 4 0 0 0 1   5 0 0 0   1 5 0 5   1   10   5   0
 5 0 3 4 3 0   3 0 3 0 0  4 3 0 10 0 0 0 0 0 0   0 2 3 5 0
*/
/*
 5
 6 0 0 0 7 0 5   1 0 4 8 0 6   0 5 0 2 0 4   9 1 7 0 3 7   0 5 0 0 0 0   3 6 2 0 0 0
 5 0 0 1 6 0   0   0   10   9   0   0 9 0 0 0   0 2 0 0 0   4 0 0 0 0
 6
 0 0 2 5 3 8   0 0 5 0 3 5   0 8 0 0 3 0
 0 0 10 0 10 0 3 10 1 9 0 5 0 0 1 3 8 0
 7 0 8 0 0 0 0 4   7 0 5 4 3 0 0   6 4 0 0 0 6 3   0 4 0 0 7 0 9   0 9 1 1 0 0 2   0 0 0 0 8 0 0  8 0 0 1 10 2 0
 8
 0 8 0 3 0 0 8 1
 1 0 0 8 0 0 0 10 0 7 0 0 6 0 4 0   0 0 7 0 9 0 0 7   0 0 0 0 0 0 2 0   10 4 6 0 0 0 10 0 0 7 1 4 0 0 0 4
 0 10 1 10 7 0 0 0
*/