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
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int w,m,a,s;
        cin >> w >> m >> a >> s;
        
        int n = 2 + a + m + s + 2*w;
        PushRelabel p(n);
        
        for (int i=0; i<w; ++i) {
            int b,c;
            cin >> b >> c;
            p.AddEdge(a+m+s+1+i, a+m+s+1+w+i, b);
            for (int j=0; j<c; ++j) {
                int sc;
                cin >> sc;
                p.AddEdge(a+m+sc, a+m+s+1+i, INT_MAX);
                p.AddEdge(a+m+s+w+1+i, n-1, INT_MAX);
            }
        }
        for (int i=0; i<m; ++i) {
            int d;
            cin >> d;
            for (int j=0; j<d; ++j) {
                int td;
                cin >> td;
                p.AddEdge(a+i+1, a+m+td, INT_MAX);
            }
        }
        vector<int> artifactWeight(a);
        for (int i=0; i<a; ++i) {
            int e;
            cin >> e;
            string s;
            cin >> s;
            if (s=="normal")
                p.AddEdge(0,i+1,e/3);
            else
                p.AddEdge(0,i+1,e);
        }
        
        for (int i=0; i<m; ++i) {
            int f;
            cin >> f;
            for (int j=0; j<f; ++j) {
                int af;
                cin >> af;
                p.AddEdge(af, a+1+i, INT_MAX);
            }
        }
        cout << "Case #" << ti << ": " << p.GetMaxFlow(0, n-1) << endl;
    }
    return 0;
}
