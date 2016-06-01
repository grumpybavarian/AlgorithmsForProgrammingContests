#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,x,m;
        cin >> n >> x >> m;
        vector<int> ms(n);
        for (int i=0; i<n; ++i) {
            cin >> ms[i];
        }
        vector<vector<int>> succ(n);
        for (int i=0; i<n; ++i) {
            int b;
            cin >> b;
            for (int j=0; j<b; ++j) {
                int b_i;
                cin >> b_i;
                if (i != b_i-1) {
                    succ[i].push_back(b_i-1);
                }
            }
        }
        int currDir = 0;
        stack<int> history;
        for (int i=0; i<m; ++i) {
            int m_i;
            cin >> m_i;
            if (m_i == 0) {
                currDir = history.top();
                history.pop();
            }
            else {
                int next = m_i-1;
                history.push(currDir);
                currDir = next;
            }
        }
        vector<int> dist(n, INT_MAX);
        int node = currDir;
        dist[node] = ms[node];
        set<pair<int,int>> pq;
        pq.insert({0,node});
        while(!history.empty()) {
            dist[history.top()] = ms[history.top()];
            pq.insert({dist[history.top()], history.top()});
            history.pop();
        }
        while (!pq.empty()) {
            int next = pq.begin()->second;
            if (next == n) {
                break;
            }
            pq.erase(pq.begin());
            for (int i : succ[next]) {
                if (dist[i] > dist[next] + ms[i]) {
                    pq.erase({dist[i], i});
                    dist[i] = dist[next] + ms[i];
                    pq.insert({dist[i], i});
                }
            }
        }
        
        if (dist[x-1] != INT_MAX)
            cout << "Case #" << ti << ": " << dist[x-1] << "\n";
        else
            cout << "Case #" << ti << ": impossible\n";
    }
    return 0;
}