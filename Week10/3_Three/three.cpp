#include <iostream>
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
        int k;
        cin >> k;
        int digits = log10(k)+1;
        int upperBound = pow(10, digits)-1;
        
        int x = k+1;
        while (x <= upperBound) {
            if (prime[x]) {
                int neededPermutations = log10(x)+1;
                int permPrime = 0;
                string s = to_string(x);
                sort(s.begin(), s.end());
                bool allPermPrime = true;
                do {
                    if (prime[stoi(s)]) ++permPrime;
                    else allPermPrime = false;
                } while (next_permutation(s.begin(), s.end()));
                
                if (permPrime >= neededPermutations or allPermPrime) {
                    break;
                }
            }
            ++x;
        }
        
        cout << "Case #" << ti << ": " << x << endl;
    }
    
    return 0;
}
