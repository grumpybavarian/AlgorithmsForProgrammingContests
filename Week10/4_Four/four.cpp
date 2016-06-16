#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> changeBase(int k, int p) {
    vector<int> res;
    
    while (k != 0) {
        res.push_back(k%p);
        k /= p;
    }
    
    //result is reverted, but this makes it easier later
    return res;
}

long long binCoeffStandard(int n, int k) {
    if (k == 0 || k == n) return 1;
    
    return (((n*binCoeffStandard(n-1,k-1))/k) % 223092870);
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

long long binCoeff(int n, int m) {
    if (n == m) return 1;
    vector<int> p = {2,3,5,7,11,13,17,19,23};
    
    vector<int> x;
    vector<int> y;
    vector<int> rem;
    for (int i=0; i<p.size(); ++i) {
        x = changeBase(n, p[i]);
        y = changeBase(m, p[i]);
        
        long result = 1;
        
        if (y.size() > x.size()) {
            rem.push_back(0);
            continue;
        }
        for (int j=0; j<min(x.size(), y.size()); ++j) {
            result *= binCoeffStandard(x[j], y[j]);
        }
        rem.push_back(result%p[i]);
    }
    
    
    //chinese remainder theorem
    int N = 2*3*5*7*11*13*17*19*23;
    long long X = 0;
    //extended euclidean algorithm
    
    for (int i=0; i<p.size(); ++i) {
        pair<long,long> rs = extEuclid(p[i], N/p[i]);
        long e = rs.second * N / p[i];
        X += e * rem[i];
        X %= N;
    }
    while (X < 0) {
        X += N;
    }
    
    return X;
}

int main() {
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,m;
        cin >> n >> m;
        if (n == m) {
            cout << "Case #" << ti << ": 1\n" ;
        }
        else {
            cout << "Case #" << ti << ": " << binCoeff(n,m) << endl;
        }
    }
    
    return 0;
}
