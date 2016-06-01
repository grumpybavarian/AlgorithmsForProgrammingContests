#include <iostream>
#include <vector>

long const C = 299792458;

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        long m;
        cout << "Case #" << ti << ": " << (m*C*C) << "\n";
    }
}
