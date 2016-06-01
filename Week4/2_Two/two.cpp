#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
using namespace std;

struct edge {
    int a;
    int b;
    long double r;
};

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    long double min_val = 0;
    for (int ti=1; ti<=t; ++ti) {
        int n,m;
        cin >> n >> m;
        vector<edge> edges(m);
        for (int i=0; i<m; ++i) {
            int v,w;
            long double c;
            cin >> v >> w >> c;
            if (c < 1.0) {
                min_val += log(c);
            }
            edges[i] = edge {v-1,w-1,c};
        }
        vector<long double> dist(n, INT_MAX);
        vector<bool> visited(n);
        
        visited[0] = true;
        dist[0] = 0;
        for (int i=0; i<=n; ++i) {
            for (edge e : edges) {
                if (visited[e.a]) {
                    if (dist[e.b] > dist[e.a] + log(e.r)) {
                        dist[e.b] = dist[e.a] + log(e.r);
                        visited[e.b] = true;
                    }
                }
            }
        }
        bool jackpot = false;
        for (edge e : edges) {
            if (visited[e.a]) {
                if (dist[e.b] > dist[e.a] + log(e.r)) {
                    jackpot = true;
                    break;
                }
            }
        }
        
        if (jackpot)
            cout << "Case #" << ti << ": Jackpot\n";
        else if (!visited[n-1])
            cout << "Case #" << ti << ": impossible\n";
        else
            cout << "Case #" << ti << ": " << exp(dist[n-1]) << "\n";
    }
    return 0;
}