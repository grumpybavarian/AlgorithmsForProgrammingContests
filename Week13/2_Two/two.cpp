#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

//code similar to: http://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
int mod_exp(int x, int a, int e) {
    int result = 1;
    
    while (e > 0) {
        if (e & 1) {
            result *= x;
            result %= 13;
        }
        
        e >>= 1;
        x = (x*x) % 13;
    }
    
    return (a*(result % 13)) % 13;
}
//end of similar code

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        string s;
        cin >> s;
        int result = 3;
        for (int i=0; i<s.length(); ++i) {
            int a = s[s.length()-i-1] - '0';
            result += mod_exp(8,a,i);
            result %= 13;
        }
        if (result == 0) result = 13;
        
        cout << "Case #" << ti << ": " << result << "\n";
    }
    return 0;
}