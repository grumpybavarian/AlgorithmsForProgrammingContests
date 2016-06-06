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
        
        set<pair<int,int>> pq;
        vector<int> dist(n+1, INT_MAX);
        pq.insert({0,g});
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
                }
            }
        }
        int distFuture = dist[0];
        
        
        
        vector<vector<int>> dp(n+1, vector<int>(distFuture,-1));
        dp[n][0] = o[n];
        for (int i=n; i>=0; --i) {
            for (int j=0; j<distFuture; ++j) {
                if (dp[i][j] == -1) continue;
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