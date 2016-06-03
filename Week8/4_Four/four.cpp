#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int lcs(string a, string b) {
    int m = a.length();
    int n = b.length();
    int dp[m+1][n+1];
    
    for (int i=0; i<=m; ++i) {
        for (int j=0; j<=n; ++j) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (a.at(i-1) == b.at(j-1))
                dp[i][j] = dp[i-1][j-1]+1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    return dp[m][n];
}

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        string a, b;
        cin >> a >> b;
        
        int maxLCS = 0;
        for (int i=0; i<b.length(); ++i) {
            int x = lcs(a,b);
            string b2 = string (b.rbegin(), b.rend());
            int y = lcs(a,b2);
            maxLCS = max(maxLCS, max(x,y));
            rotate(b.begin(), b.begin()+1, b.end());
        }
        
        cout << "Case #" << ti << ": " << maxLCS << endl;
    }
    return 0;
}