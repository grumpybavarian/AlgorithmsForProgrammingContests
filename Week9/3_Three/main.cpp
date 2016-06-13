#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
typedef unsigned long long LL;
using namespace std;

vector<LL> tree;

LL queryMax(LL node, LL l, LL r, LL _l, LL _r) {
    if (l == _l && r == _r) {
        return tree[node-1];
    }
    
    LL mid = (_l+_r)/2;
    LL a = 0;
    LL b = 0;
    
    if (max(l,_l) <= min(r,mid) && 2*node <= tree.size()) {
        a = queryMax(2*node, max(l,_l), min(r,mid), _l, mid);
    }
    if (max(l,mid+1) <= min(r,_r) && 2*node+1 <= tree.size()) {
        b = queryMax(2*node+1, max(l,mid+1), min(r,_r), mid+1, _r);
    }
    return max(a,b);
}

//l r actual LLerval bounds
// _l _r bouns of node LLerval
void insert(LL node, LL l, LL r, LL _l, LL _r, LL v) {
    if (_l == _r) {
        tree[node-1] = v;
        return;
    }
    LL mid = (_l+_r)/2;
    
    //left: _l bis mid
    //right: mid+1 bis _r
    //check if LLerval [l,r] LLersects with left child
    if (max(l,_l) <= min(r,mid)) {
        insert(2*node, max(l,_l), min(r,mid), _l, mid, v);
    }

    //check if LLerval [l,r] LLersects with left child
    if (max(l,mid+1) <= min(r,_r)) {
        insert(2*node+1, max(l,mid+1), min(r,_r), mid+1, _r, v);
    }
    
    tree[node-1] = max(tree[2*node-1],tree[2*node]);
}

int main() {
    ios_base::sync_with_stdio(false);
    LL t;
    cin >> t;
    for (LL ti=1; ti<=t; ++ti) {
        LL n,k;
        cin >> n >> k;
        n = pow(2, ceil(log(n)/log(2)));
        tree = vector<LL>(2*n-1);
        cout << "Case #" << ti << ": ";
        for (LL i=0; i<k; ++i) {
            LL w,h,p;
            cin >> w >> h >> p;
            LL diff = queryMax(1, p, p+w-1, 0, n-1);
            insert(1, p, p+w-1, 0, n-1, h+diff);
            cout << tree[0] << " ";
        }
        cout << endl;
    }
    return 0;
}
/*
 3
 12 3 2 1 2 6 2 3 2 2 9
 15 4
 2 5 10 6 3 2 9 2 5 1 1 1
 2 3 1 1 1 1 1 0 2 2 0
 */
/*
 4
 7 9 3 4 2 4 4 3 4 2 1 1 2 4 4 4 2 3 3 2 5 2 1 1 3 2 3 1 1
 13 10 3 2 3   3 2 4   4 5 4   1 5 6   4 2 0   2 5 4   2 2 8   5 2 7   4 3 5   5 5 3
 12 3 4 3 8   3 4 6   2 3 9
 13 9 3 4 4   1 5 3   4 2 2   2 1 7   3 4 4   5 4 4   4 3 5 1 3 11 1 2 0
*/
/*
 1
 2 3
 1 3 0
 1 2 1
 1 2 1
 */