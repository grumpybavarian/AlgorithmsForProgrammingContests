#include <cmath>
#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <climits>
#include <time.h>
#include <map>
#include <stack>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int w,h,n;
        cin >> w >> h >> n;
        vector<vector<int>> maze(h, vector<int>(w,INT_MAX));
        priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
        int xc,yc,wc,hc;
        cin >> xc >> yc >> wc >> hc;
        for (int i=0; i<hc; ++i) {
            for (int j=0; j<wc; ++j) {
                maze[yc-1+i][xc-1+j] = 0;
                if (i == 0 || j == 0 || i == hc-1) {
                    pq.push({0,{yc-1+i,xc-1+j}});
                }
            }
        }
        int shortestPath = min(xc-1,min(yc-1,h-yc-hc+1));
        
        map<pair<int,int>,bool> isImpassable;
        for (int i_n=0; i_n<n; ++i_n) {
            int xi,yi,wi,hi;
            cin >> xi >> yi >> wi >> hi;
            for (int i=0; i<hi; ++i) {
                for (int j=0; j<wi; ++j) {
                    isImpassable[{yi-1+i,xi-1+j}] = true;
                }
            }
        }
        vector<pair<int,int>> neighbors;
        while (!pq.empty()) {
            pair<int,int> next = pq.top().second;
            int currDist = pq.top().first;
            if (currDist >= shortestPath) break;
            pq.pop();
            int x = next.first;
            int y = next.second;
            if (x == 0 || x == h-1 || y == 0) {
                if (maze[x][y] < shortestPath) {
                    shortestPath = maze[x][y];
                }
                break;
            }
            
            if (x<yc-1 && y>=xc-1) {
                neighbors = {{x-1,y},{x-1,y+1},{x-1,y-1},{x,y+1},{x,y-1}};
            }
            else if (x<yc-1 && y<xc-1) {
                neighbors = {{x+1,y},{x+1,y-1},{x-1,y},{x-1,y+1},{x-1,y-1},{x,y+1},{x,y-1}};
            }
            else if (x>=yc-1 && x < yc+hc-1) {
                neighbors = {{x+1,y},{x+1,y-1},{x-1,y},{x-1,y-1},{x,y-1}};
            }
            else if (y<xc-1) {
                neighbors = {{x+1,y},{x+1,y+1},{x+1,y-1},{x-1,y},{x-1,y+1},{x,y+1},{x,y-1}};
            }
            else {
                neighbors = {{x+1,y},{x+1,y+1},{x+1,y-1},{x,y+1},{x,y-1}};
            }
            
            for (auto item : neighbors) {
                int xi = item.first;
                int yi = item.second;
                if (xi<0 or xi>=h or yi<0 or yi>=w) continue;
                if (isImpassable[item]) {
                    if (maze[xi][yi] > maze[x][y]) {
                        maze[xi][yi] = maze[x][y];
                        pq.push({maze[xi][yi],item});
                    }
                }
                else if (maze[xi][yi] > maze[x][y]+1) {
                    maze[xi][yi] = maze[x][y] + 1;
                    pq.push({maze[xi][yi],item});
                }
            }
        }
        
        cout << "Case #" << ti << ": " << shortestPath << endl;
    }
    return 0;
}
