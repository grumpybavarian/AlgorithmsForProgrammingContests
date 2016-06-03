#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> degrees;
int maxDegree;

vector<int> backtrack(vector<int> c) {
    if (c.size() == maxDegree+1) return c;
    vector<int> largestSubset = c;
    for (int i=0; i<adj.size(); ++i) {
        bool possible = true;
        for (int j=0; j<c.size(); ++j) {
            if (i == c[j] or adj[c[j]][i] == 0) {
                possible = false;
                break;
            }
        }
        if (possible) {
            vector<int> next = c;
            next.push_back(i);
            next = backtrack(next);
            if (next.size() > largestSubset.size())
                largestSubset = next;
        }
    }
    
    return largestSubset;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    double start = clock();
    for (int ti=1; ti<=t; ++ti) {
        int n,m;
        cin >> n >> m;
        adj = vector<vector<int>>(n, vector<int>(n,0));
        degrees = vector<int>(n,0);
        maxDegree = 0;
        for (int i=0; i<m; ++i) {
            int a,b;
            cin >> a >> b;
            adj[a-1][b-1] = 1;
            adj[b-1][a-1] = 1;
            if (++degrees[a-1] > maxDegree) {
                maxDegree = degrees[a-1];
            }
            
            if (++degrees[b-1] > maxDegree) {
                maxDegree = degrees[b-1];
            }
        }
        vector<int> subset = backtrack(vector<int>());
        
        
        cout << "Case #" << ti << ": ";
        for (auto i : subset) {
            cout << i+1 << " ";
        }
        cout << endl;
    }
    double end = clock() - start;
    cout << end/CLOCKS_PER_SEC << endl;
    return 0;
}