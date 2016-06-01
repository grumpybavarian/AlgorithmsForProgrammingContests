#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;

struct edge {
    int b, c;
};

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,m;
        cin >> n >> m;
        vector<vector<edge>> adj(n);
        for (int i=0; i<m; ++i) {
            int v,w,c;
            cin >> v >> w >> c;
            if (v != w) {
                adj[v-1].push_back(edge {w-1,c});
                adj[w-1].push_back(edge {v-1,c});
            }
        }
        vector<int> dist(n, INT_MAX);
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
                if (dist[e.b] > dist[next] + e.c) {
                    pq.erase({dist[e.b], e.b});
                    dist[e.b] = dist[next] + e.c;
                    pq.insert({dist[e.b], e.b});
                }
        }
        cout << "Case #" << ti << ": " << dist[n-1] << "\n";
    }
    return 0;
}
