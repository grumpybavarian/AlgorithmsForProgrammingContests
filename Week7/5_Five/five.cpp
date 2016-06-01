#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <stack>
using namespace std;

struct city {
    int id;
    city* p;
    int size;
};

struct city* find(struct city* a) {
    if (a->p->id == a->id) {
        return a;
    }
    struct city* p;
    p = find(a->p);
    a->p = p;
    return p;
}

void merge(struct city* a, struct city* b) {
    struct city* fx,* fy;
    fx = find(a);
    fy = find(b);
    if (fx->id == fy->id) return;
    if (fx->size <= fy->size) {
        fx->p = fy;
        fy->size += fx->size;
    }
    else {
        merge(b,a);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        vector<vector<int>> dist(n, vector<int>(n));
        vector<vector<int>> adj(n, vector<int>(n));
        vector<city> cities(n);
        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                cin >> dist[i][j];
            }
            cities[i] = city {i, &cities[i], 0};
        }
        
        while (find(&cities[0])->id != find(&cities[n-1])->id) {
            vector<bool> con(n);
            vector<int> toMerge(n,-1);
            for (int i=0; i<n; ++i) {
                if (con[i]) continue;
                int minDist = INT_MAX;
                for (int j=0; j<n; ++j) {
                    if (i==j) continue;
                    if (dist[i][j] < minDist && find(&cities[i])->id != find(&cities[j])->id) {
                        bool flag = true;
                        minDist = dist[i][j];
                        toMerge[i] = j;
                    }
                }
            }
            for (int i=0; i<n; ++i) {
                if (toMerge[i] != -1 && toMerge[toMerge[i]] == i) {
                    merge(&cities[i], &cities[toMerge[i]]);
                    adj[i][toMerge[i]] = 1;
                    adj[toMerge[i]][i] = 1;
                }
            }
        }
        
        stack<int> s;
        vector<bool> visited(n);
        vector<int> parent(n,-1);
        visited[0] = true;
        parent[0] = 0;
        s.push(0);
        while (!s.empty()) {
            int next = s.top();
            if (next == n-1) break;
            s.pop();
            
            for (int i=0; i<n; ++i) {
                if (adj[next][i] == 0 or visited[i]) continue;
                visited[i] = true;
                s.push(i);
                parent[i] = next;
            }
        }
        cout << "Case #" << ti << ": ";
        int curr = n-1;
        vector<int> path;
        while (curr != 0) {
            path.push_back(curr+1);
            curr = parent[curr];
        }
        path.push_back(1);
        reverse(path.begin(), path.end());
        for (int i=0; i<path.size(); ++i) {
            cout << path[i] << " ";
        }
        cout << endl;
        
        
    }
    
    return 0;
}
