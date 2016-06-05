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
        
        for (int i=0; i<c; ++i) {
            cout << usedCoins[i] << " " ;
        }
        cout << endl << endl;
        
        for (int i=0; i<n; ++i) {
            for (int j=0; j<c; ++j) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
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
/*
 2
 6 29 1 2 4 5 6 8
 4 43
 1 6 7 13
 */
/*
 12
 4 780
 1 6 35 97
 9 827
 1 15 17 26 64 70 79 88 98
 5 598
 1 21 45 64 68
 2 756 1 55
 5 507
 1 23 33 35 58
 6 789
 1 9 70 73 79 98
 7 418
 1 15 19 64 74 87 88
 10 481
 1 13 16 27 38 44 51 59 75 100
 7 979
 1 9 11 49 68 76 100
 5 932
 1 57 80 81 89
 10 612
 1 6 28 30 36 67 69 74 96 99
 3 306
 1 18 19
 */
