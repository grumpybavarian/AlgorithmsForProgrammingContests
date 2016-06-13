#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <math.h>
using namespace std;

vector<unsigned long long> tree;

//l r actual interval bounds
// _l _r bouns of node interval
void insert(int node, int l, int r, int _l, int _r, int v) {
    if (l == _l && r == _r) {
        tree[node-1] += v;
        return;
    }
    int mid = (_l+_r)/2;
    
    //left: _l bis mid
    //right: mid+1 bis _r
    //check if interval [l,r] intersects with left child
    if (max(l,_l) <= min(r,mid)) {
        insert(2*node, max(l,_l), min(r,mid), _l, mid, v);
    }
    //check if interval [l,r] intersects with left child
    if (max(l,mid+1) <= min(r,_r)) {
        insert(2*node+1, max(l,mid+1), min(r, _r), mid+1, _r, v);
    }
}

unsigned long long query(int node, int l, int r, int _l, int _r) {
    if (2*node-1 >= tree.size() || (l == _l && r == _r)) {
        return tree[node-1];
    }
    //left: _l bis mid
    //right: mid+1 bis _r
    //check if interval [l,r] intersects with left child
    int mid = (_l+_r)/2;
    unsigned long long sum = tree[node-1];
    if (max(l,_l) <= min(r,mid)) {
        sum += query(2*node, max(l,_l), min(r,mid), _l, mid);
    }
    //check if interval [l,r] intersects with left child
    if (max(l,mid+1) <= min(r,_r)) {
        sum += query(2*node+1, max(l,mid+1), min(r,_r), mid+1, _r);
    }
    
    return sum;
}


unsigned long long query(int i, int n) {
    return query(1,i,i,0,n-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,k;
        cin >> n >> k;
        n = pow(2, ceil(log(n)/log(2)));
        tree = vector<unsigned long long>(2*n-1);
        unsigned long long res = 0;
        for (int i=0; i<k; ++i) {
            char c;
            cin >> c;
            if (c == 'i') {
                int l,r,v;
                cin >> l >> r >> v;
                insert(1, l-1, r-1, 0, n-1, v);
            }
            else {
                int a;
                cin >> a;
                res += query(a-1, n);
                res %= 1000000007;
            }
        }
        cout << "Case #" << ti << ": " << res << "\n";
    }
    return 0;
}
/*
 3
 4 3 i 1 3 1 q 3
 q 1
 6 5 i 2 5 2 i 1 6 3 q 3 i 1 3 1 q 1
 5 2 i 1 5 4 q 2
*/
/*
 5
 4 7
 i 1 2 645 i 2 4 945 q 3
 q 2
 q 1
 i 1 3 606 q 1
 5 6
 i 2 5 695 i 3 5 863 q 3
 q 2
 q 3
 q 4
 8 7
 i 3 6 488 i 4 6 234 q 1
 i 5 8 179 q 3
 i 4 8 930 q 8
 4 3
 i 2 3 519 q 2
 q 2
 4 8
 q 2
 i 1 3 664 i 2 3 545 i 2 4 724 q 4
 i 1 3 305 q 2
 q 2
*/