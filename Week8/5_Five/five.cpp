#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
#include <queue>
#include <stack>
using namespace std;

struct tunnel {
    int b,l;
};

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,m,g;
        cin >> n >> m >> g;
        vector<int> o(n+1);
        for (int i=1; i<=n; ++i) {
            cin >> o[i];
        }
        vector<vector<tunnel>> adjLea(n+1);
        vector<vector<tunnel>> adjFuture(n+1);
        for (int i=0; i<m; ++i) {
            int x,y,l;
            cin >> x >> y >> l;
            if (x == y) continue;
            if (x < y) {
                adjLea[y].push_back(tunnel {x,l});
            }
            else {
                adjLea[x].push_back(tunnel {y,l});
            }
            
            adjFuture[x].push_back(tunnel {y,l});
            adjFuture[y].push_back(tunnel {x,l});
        }
        
        //dijkstra for future
        set<pair<int,int>> pq;
        vector<int> dist(n+1, INT_MAX);
        vector<int> pred(n+1);
        pq.insert({0,g});
        pred[g] = -1;
        dist[g] = 0;
        while (!pq.empty()) {
            int next = pq.begin()->second;
            if (next == 0) break;
            pq.erase(pq.begin());
            
            for (auto item : adjFuture[next]) {
                if (dist[item.b] > dist[next]+item.l) {
                    pq.erase({dist[item.b],item.b});
                    dist[item.b] = dist[next]+item.l;
                    pq.insert({dist[item.b],item.b});
                    pred[item.b] = next;
                }
            }
        }
        int distFuture = dist[0];
        vector<bool> usedNodes(n+1);
        int curr = pred[0];
        while (curr != -1) {
            usedNodes[curr] = true;
            curr = pred[curr];
        }
        
        vector<vector<int>> dp(n+1, vector<int>(distFuture,-1));
        dp[n][0] = o[n];
        for (int i=n; i>=0; --i) {
            for (int j=0; j<distFuture; ++j) {
                for (auto item : adjLea[i]) {
                    int newDist = j + item.l;
                    if (newDist >= distFuture) continue;
                    if (dp[item.b][newDist] < dp[i][j]+o[item.b]) {
                        dp[item.b][newDist] = dp[i][j]+o[item.b];
                    }
                }
            }
        }
        
        int result = -1;
        for (int i=0; i<distFuture; ++i) {
            if (dp[0][i] > result) result = dp[0][i];
        }
        
        
        cout << "Case #" << ti << ": ";
        if (result == -1) {
            cout << "impossible\n";
        }
        else {
            cout << result << "\n";
        }
    }
    return 0;
}
/*
 1 
 2 2 1
 1 1
 1 0 3
 2 0 2
 */
/*
 1
 5 6 1
 1 10 10 1 1
 0 1 100
 5 4 1
 5 3 1
 3 0 1
 4 2 1
 2 0 1
 */
/*
 1
 4 6 1
 1 1 1 1
 0 1 100
 4 3 1
 4 2 1
 3 0 1
 2 0 1
 2 3 1
 */
/*
 2 3 3 2 1 1 1 0 1 1 1 3 1 1 2 2
 3 3 2 1 1 1 0 1 1 1 2 1 1 3 2
 */
/*
 4 2 6 1 2 0 2 1 6 1 0 6 1 2 6 2 1 6 2 2 7 0 0 4
 4 5 2 2 2 3 3 0 4 4 4 1 2  1 3 6   3 2 6   3 4 7
 4 7 3   2 2 1 0   0 1 6   1 2 7   0 4 6   4 3 6   0 4 7   4 4 2   0 3 6
 4 7 3   3 4 0 3   2 4 4   2 3 6   4 1 3   1 0 6   1 0 7   1 1 6   0 0 2
 */