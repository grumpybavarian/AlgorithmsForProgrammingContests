#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <map>
#include <set>
using namespace std;
typedef long long LL;

//This method is from: http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
vector<LL> primeFactors(long n)
{
    vector<LL> primeFactors;
    // Print the number of 2s that divide n
    while (n%2 == 0)
    {
        primeFactors.push_back(2);
        n = n/2;
    }
    
    // n must be odd at this point.  So we can skip one element (Note i = i +2)
    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        // While i divides n, print i and divide n
        while (n%i == 0)
        {
            primeFactors.push_back(i);
            n = n/i;
        }
    }
    
    // This condition is to handle the case whien n is a prime number
    // greater than 2
    if (n > 2)
        primeFactors.push_back(n);
    
    return primeFactors;
}
//End of used code from: http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/

LL lcm(LL a, LL b) {
    LL gcd = __gcd(a,b);
    return (a*b)/gcd;
}

pair<long,long> extEuclid(long a, long b) {
    long s = 1, t = 0;
    long s1 = 0, t1 = 1;
    long q, r, m, n;
    while(a != 0) {
        q = b / a;
        r = b % a;
        m = s1 - q * s;
        n = t1 - q * t;
        s1 = s, t1 = t;
        s = m, t = n;
        b = a, a = r;
    }
    return {s1,t1};
}

int main() {
    int t = 1;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int k;
        cin >> k;
        vector<LL> ai(k);
        LL l = 1;
        for (int i=0; i<k; ++i) {
            cin >> ai[i];
            l = lcm(l,ai[i]);
        }
        
        LL m = ai[0];
        
        set<pair<LL,LL>> modSet;
        map<LL,bool> inserted;
        for (int i=0; i<k; ++i) {
            vector<LL> pf = primeFactors(ai[i]);
            for (int j=0; j<pf.size(); ++j) {
                if (!inserted[pf[j]]) {
                    modSet.insert({(ai[i]-i)%pf[j], pf[j]});
                    inserted[pf[j]] = true;
                }
            }
        }
        
        //CRT
        LL x = 0;
        LL N = 1;
        for (auto item : modSet) {
            N *= item.second;
        }
        for (auto item : modSet) {
            x += item.first * extEuclid(item.second, N/item.second).second * N/item.second;
        }
        bool pos = false;
        while (x < 0) {
            x += N;
        }
        while (x - N > 0) {
            x -= N;
        }
        while (!pos) {
            pos = true;
            for (int i=0; i<k; ++i) {
                if ((x+i) % ai[i] != 0) pos = false;
            }
            if (pos) break;
            
            x += N;
        }
        
        
        cout << "Case #" << ti << ": " << x << " " << l << endl;
        
    }
    
    return 0;
}

/*
 2
 4 3 2 1 6
 4 1 2 3 4
 */
/*
 9
 3 5 4 3
 5 4 5 6 7 8
 10
 10 3 2 1 6 5 2 3 2 11
 7
 3 2 1 30 17 2 3
 9
 7 2 3 2 5 6 1 14 9
 10
 3 14 11 12 1 2 3 4 7 6
 6
 84 1 2 3 4 11
 6
 2 3 14 5 6 1
 4
 18 7 10 3
 */
