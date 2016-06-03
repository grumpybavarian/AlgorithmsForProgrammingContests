#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int c, n;
        cin >> n >> c;
        ++c;
        vector<int> v(n);
        for (int i=0; i<n; ++i) {
            cin >> v[i];
        }
        
        vector<vector<int>> dp(n, vector<int>(c));
        vector<int> usedCoins(c-1);
        for (int i=0; i<n; ++i) {
            dp[i][0] = 0;
        }
        for (int i=0; i<c; ++i) {
            dp[0][i] = i;
        }
        for (int i=1; i<n; ++i) {
            for (int j=1; j<c; ++j) {
                if (j < v[i]) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    if (dp[i-1][j] < dp[i][j-v[i]]+1) {
                        dp[i][j] = dp[i-1][j];
                    }
                    else {
                        dp[i][j] = dp[i][j-v[i]]+1;
                        usedCoins[j] = i;
                    }
                }
            }
        }
        
        int sum = c-1;
        vector<int> u(n);
        while (sum > 0) {
            ++u[usedCoins[sum]];
            sum -= v[usedCoins[sum]];
        }
        
        cout << "Case #" << ti << ": ";
        
        for (int i=0; i<n; ++i) {
            cout << u[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
