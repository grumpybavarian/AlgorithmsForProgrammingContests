#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

vector<int> chaps;
vector<int> ind;
vector<int> charChaps;

int backtrack(vector<int> config, vector<bool> left, vector<vector<int>> adj) {
    if (config.size() == left.size()) {
        return 1;
    }
    int sum = 0;
    bool allClear = true;
    for (int i=0; i<left.size(); ++i) {
        if (left[i] && (adj[i].size() != 0 || (config.size() > 0 && charChaps[i] == charChaps[config[config.size()-1]]))) {
            allClear = false;
            break;
        }
    }
    if (allClear) {
        sum = 1;
        for (int i=1; i<=left.size()-config.size(); ++i) {
            sum *= i;
        }
        return sum;
    }
    for (int i=0; i<left.size(); ++i) {
        if (!left[i] or adj[i].size() != 0 or (config.size() > 0 && charChaps[i] == charChaps[config[config.size()-1]])) continue;
        vector<vector<int>> newAdj = adj;
        config.push_back(i);
        left[i] = false;
        for (int j=0; j<newAdj.size(); ++j) {
            newAdj[j].erase(remove(newAdj[j].begin(), newAdj[j].end(), i), newAdj[j].end());
        }
        sum += backtrack(config, left, newAdj);
        config.pop_back();
        left[i] = true;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,m;
        cin >> n >> m;
        chaps = vector<int>(n);
        ind = vector<int>(n);
        charChaps = vector<int>();
        int sumOfChaps = 0;
        for (int i=0; i<n; ++i) {
            cin >> chaps[i];
            ind[i] = sumOfChaps;
            sumOfChaps += chaps[i];
            for (int j=0; j<chaps[i]; ++j) {
                charChaps.push_back(i);
            }
        }
        vector<vector<int>> adj(sumOfChaps);
        for (int i=0; i<n; ++i) {
            for (int j=1; j<chaps[i]; ++j) {
                for (int k=0; k<j; ++k) {
                    adj[ind[i]+j].push_back(ind[i]+k);
                }
            }
        }
        for (int i=0; i<m; ++i) {
            int c,p,d,q;
            cin >> c >> p >> d >> q;
            adj[ind[d-1]+q-1].push_back(ind[c-1]+p-1);
        }
        
        int sum = backtrack(vector<int>(), vector<bool>(sumOfChaps,1), adj);
        
        
        cout << "Case #" << ti << ": " << sum << "\n";
    }
    return 0;
}
