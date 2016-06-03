#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct g {
    int id,l,s;
};

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int m,n;
        
        cin >> m >> n;
        ++m;
        vector<g> a;
        for (int i=0; i<n; ++i) {
            int p,s,l;
            cin >> p >> l >> s;
            for (int j=0; j<p; ++j) {
                a.push_back(g {i+1,l,s});
            }
        }
        n = a.size();
        ++n;
        vector<vector<int>> dp(n, vector<int>(m));
        for (int i=0; i<n; ++i) {
            dp[i][0] = 0;
        }
        for (int i=0; i<m; ++i) {
            dp[0][i] = 0;
        }
        
        vector<int> usedFood(m);
        for (int i=1; i<n; ++i) {
            for (int j=1; j<m; ++j) {
                if (j < a[i-1].l) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    if (dp[i-1][j] >= dp[i-1][j-a[i-1].l]+a[i-1].s) {
                        dp[i][j] = dp[i-1][j];
                    }
                    else {
                        dp[i][j] = dp[i-1][j-a[i-1].l]+a[i-1].s;
                        usedFood[j] = i-1;
                    }
                }
            }
        }
        cout << "Case #" << ti << ": ";

        int h = m-1;
        for (int i=dp.size()-1; i>0; --i) {
            if (dp[i][h] != dp[i-1][h]) {
                h -= a[i-1].l;
                cout << a[i-1].id << " ";
            }
        }
        
        
        cout << endl;
        
    }
    return 0;
}