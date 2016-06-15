#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

vector<bool> prime = {};

void sieveEra(int n)
{
    prime = vector<bool>(n+1, true);
    prime[0] = false;
    prime[1] = false;
    for (int p=2; p*p<=n; ++p)
    {
        if (prime[p])
        {
            for (int i=p*2; i<=n; i += p)
                prime[i] = false;
        }
    }
}

int main() {
    sieveEra(100000000);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        cout << "Case #" << ti << ": ";
        if (n % 2 == 0) {
            if (prime[n-2]) {
                cout << 2 << " " << n-2 << endl;
                goto end;
            }
            for (int i=3; i<n; i+=2) {
                if (prime[i] && prime[n-i]) {
                    cout << i << " " << n-i << endl;
                    goto end;
                }
            }
        }
        else {
            for (int i=2; i<n; ++i) {
                if (!prime[i]) continue;
                for (int j=i; j<n; ++j) {
                    if (prime[j] && prime[n-i-j]) {
                        cout << i << " " << j << " " << n-i-j << endl;
                        goto end;
                    }
                }
            }
        }
    end: continue;
    }
    
    return 0;
}
