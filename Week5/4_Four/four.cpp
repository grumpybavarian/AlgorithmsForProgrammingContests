//Code used from https://web.stanford.edu/~liszt90/acm/notebook.html#file3
#include <cmath>
#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <climits>
using namespace std;

typedef long long LL;

struct Edge {
    int from, to, cap, flow, index;
    Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
    int N;
    vector<vector<Edge> > G;
    vector<LL> excess;
    vector<int> dist, active, count;
    queue<int> Q;
    
    PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}
    
    void AddEdge(int from, int to, int cap) {
        G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
        if (from == to) G[from].back().index++;
        G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
    }
    
    void Enqueue(int v) {
        if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
    }
    
    void Push(Edge &e) {
        int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
        if (dist[e.from] <= dist[e.to] || amt == 0) return;
        e.flow += amt;
        G[e.to][e.index].flow -= amt;
        excess[e.to] += amt;
        excess[e.from] -= amt;
        Enqueue(e.to);
    }
    
    void Gap(int k) {
        for (int v = 0; v < N; v++) {
            if (dist[v] < k) continue;
            count[dist[v]]--;
            dist[v] = max(dist[v], N+1);
            count[dist[v]]++;
            Enqueue(v);
        }
    }
    
    void Relabel(int v) {
        count[dist[v]]--;
        dist[v] = 2*N;
        for (int i = 0; i < G[v].size(); i++)
            if (G[v][i].cap - G[v][i].flow > 0)
                dist[v] = min(dist[v], dist[G[v][i].to] + 1);
        count[dist[v]]++;
        Enqueue(v);
    }
    
    void Discharge(int v) {
        for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
        if (excess[v] > 0) {
            if (count[dist[v]] == 1)
                Gap(dist[v]);
            else
                Relabel(v);
        }
    }
    
    LL GetMaxFlow(int s, int t) {
        count[0] = N-1;
        count[N] = 1;
        dist[s] = N;
        active[s] = active[t] = true;
        for (int i = 0; i < G[s].size(); i++) {
            excess[s] += G[s][i].cap;
            Push(G[s][i]);
        }
        
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            active[v] = false;
            Discharge(v);
        }
        
        LL totflow = 0;
        for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
        return totflow;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        cout << "Case #" << ti << ": ";
        int n,m;
        cin >> n >> m;
        vector<int> wins(n);
        int maxWins = 0;
        int anzNodes = 2+n+m;
        int maxPosWins = 0;
        PushRelabel p(anzNodes);
        for (int i=0; i<n; ++i) {
            cin >> wins[i];
            if (wins[i] > maxWins) maxWins = wins[i];
            if (wins[i] > maxPosWins) maxPosWins = wins[i];
        }
        vector<int> posWins(n,0);
        vector<pair<int,int>> matches(m);
        for (int i=0; i<m; ++i) {
            int x,y;
            cin >> x >> y;
            ++posWins[x-1];
            ++posWins[y-1];
            if (wins[x-1]+posWins[x-1] > maxPosWins) maxPosWins = wins[x-1] + posWins[x-1];
            if (wins[y-1]+posWins[y-1] > maxPosWins) maxPosWins = wins[y-1] + posWins[y-1];
            matches[i] = {x-1,y-1};
        }
        for (int i=0; i<n; ++i) {
            if (wins[i]+posWins[i] < maxWins) {
                cout << " no";
                continue;
            }
            if (wins[i] == maxPosWins) {
                cout << " yes";
                continue;
            }
            PushRelabel pr = p;
            int input = 0;
            for (int j=0; j<m; ++j) {
                if (matches[j].first != i && matches[j].second != i) {
                    pr.AddEdge(0, j+1, 1);
                    pr.AddEdge(j+1, m+matches[j].first+1, INT_MAX);
                    pr.AddEdge(j+1, m+matches[j].second+1, INT_MAX);
                    ++input;
                }
            }
            
            for (int j=0; j<n; ++j) {
                if (i==j) continue;
                pr.AddEdge(m+1+j, anzNodes-1, wins[i]+posWins[i]-wins[j]);
            }
            
            int flow = pr.GetMaxFlow(0, anzNodes-1);
            if (flow == input)
                cout << " yes";
            else
                cout << " no";
        }
        
        
        
        cout << endl;
    }
    return 0;
}
