#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct edge {
    int a,b,c;
};

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        vector<vector<edge>> adj(n);
        int time;
        for (int i=0; i<n; ++i) {
            int p,s;
            cin >> p >> s;
            if (i == n-1) {
                time = p;
            }
            for (int j=0; j<s; ++j) {
                int k;
                cin >> k;
                adj[i].push_back(edge {i,k-1,p});
            }
        }
        vector<int> dist(n, 0);
        int node = 0;
        dist[node] = 0;
        set<pair<int,int>> pq;
        pq.insert({0,node});
        while (!pq.empty()) {
            int next = pq.begin()->second;
            if (next == n) {
                break;
            }
            pq.erase(pq.begin());
            for (edge e : adj[next])
                if (dist[e.b] < dist[next] + e.c) {
                    pq.erase({dist[e.b], e.b});
                    dist[e.b] = dist[next] + e.c;
                    pq.insert({dist[e.b], e.b});
                }
        }
        cout << "Case #" << ti << ": " << dist[n-1]+time << "\n";
        
    }
    return 0;
}
