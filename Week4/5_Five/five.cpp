#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;

const pair<int,int> wall = pair<int,int>(-1,-1);

struct triple {
    int cost;
    int dist;
    pair<int,int> coord;
    vector<pair<int,int>> usedShortcuts;
};

bool operator==(triple const &a, triple const &b) {
    return a.coord == b.coord && a.cost == b.cost && a.dist == b.dist;
}

bool operator<(triple const &a, triple const &b) {
    if (a.cost != b.cost) {
        return a.cost < b.cost;
    }
    if (a.dist != b.dist) {
        return a.dist < b.dist;
    }
    if (a.coord.first != b.coord.first) {
        return a.coord.first < b.coord.first;
    }
    return a.coord.second < b.coord.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int w,h;
        cin >> w >> h;
        vector<vector<pair<int,int> > > maze(h, vector<pair<int,int> >(w,wall));
        pair<int,int> start;
        pair<int,int> exit;
        for (int i=0; i<h; ++i) {
            for (int j=0; j<w; ++j) {
                char c = ' ';
                while (!(c=='_' || c=='@' || c=='*'))
                    cin >> c;
                if (c == '_') {
                    maze[i][j] = make_pair(INT_MAX, 0);
                }
                if (c == '*') {
                    maze[i][j] = make_pair(INT_MAX,0);
                    start = make_pair(i,j);
                }
                if ((i==0 || i==h-1) && c == '_') {
                    exit = make_pair(i,j);
                }
                if ((j==0 || j==w-1) && c == '_') {
                    exit = make_pair(i,j);
                }
            }
        }
        multiset<triple> pq;
        pq.insert(triple {0,0,start,vector<pair<int,int>>()});
        
        vector<pair<int,int>> shortcuts(0);
        
        while (!pq.empty()) {
            triple next = *pq.begin();
            int cost = next.cost;
            int dist = next.dist;
            int x = next.coord.first;
            int y = next.coord.second;
            if (next.coord == exit) shortcuts = next.usedShortcuts;
            pq.erase(next);
            
            if (dist < maze[x][y].first) {
                maze[x][y].first = dist;
                maze[x][y].second = cost;
                
                vector<pair<int,int>> neighbors = {{x+1,y},{x-1,y},{x,y+1},{x,y-1}};
                vector<pair<int,int>> transNeighbors = {{x+2,y},{x-2,y},{x,y+2},{x,y-2}};
                for (int i=0; i<4; ++i) {
                    pair<int,int> f = neighbors[i];
                    if (f.first>0 && f.first<h && f.second>0 && f.second<w && maze[f.first][f.second] == wall) f = transNeighbors[i];
                    if (f.first>=0 && f.first<h && f.second>=0 && f.second<w && maze[f.first][f.second] != wall) {
                        if (cost+(f==transNeighbors[i]) <= 3) {
                            vector<pair<int,int>> newShortcuts = next.usedShortcuts;
                            if (f == transNeighbors[i]) {
                                newShortcuts.push_back({neighbors[i]});
                            }
                            pq.insert(triple {cost+(f==transNeighbors[i]), dist+1, f, newShortcuts});
                        }
                    }
                }
            }
        }
        
        int used = shortcuts.size();
        for (int i=0; i<3-used; ++i) {
            shortcuts.push_back(make_pair(-1,-1));
        }
        
        cout << "Case #" << ti << ":\n";
        for (int i=0; i<shortcuts.size(); ++i) {
            if (shortcuts[i] == wall) {
                cout << "unused\n";
            }
            else {
                cout << shortcuts[i].second+1 << " " << shortcuts[i].first+1 << "\n";
            }
        }
    }
    return 0;
}







