#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> garden;
vector<vector<bool>> visited;
vector<pair<int,int>> plants;
vector<pair<int,int>> question;
pair<int,int> source;
int w,h;

void flow(pair<int,int> s) {
    int x = s.first;
    int y = s.second;
    
    visited[x][y] = true;
    vector<pair<int,int>> neighbors = {{x+1,y},{x-1,y},{x,y+1},{x,y-1}};
    
    for (auto n : neighbors) {
        int xn = n.first;
        int yn = n.second;
        if (xn<0 or xn>3 or yn<0 or yn>3 or garden[xn][yn]==-1 or visited[xn][yn]) continue;
        if (garden[xn][yn] <= garden[x][y]) {
            flow(n);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        cin >> h >> w;
        garden = vector<vector<int>>(4, vector<int>(4,0));
        visited = vector<vector<bool>>(4, vector<bool>(4,0));
        plants = vector<pair<int,int>>();
        question = vector<pair<int,int>>();
        for (int i=0; i<4; ++i) {
            for (int j=0; j<4; ++j) {
                char c;
                cin >> c;
                if (c == '_') {
                    garden[i][j] = -1;
                }
                else if (c == '*') {
                    garden[i][j] = w;
                    source = {i,j};
                }
                else if (c == '?') {
                    question.push_back({i,j});
                }
                else {
                    garden[i][j] = c - '0';
                    plants.push_back({i,j});
                }
            }
        }
        
        if (question.empty()) {
            flow(source);
            bool valid = true;
            for (auto item : plants) {
                if (!visited[item.first][item.second]) {
                    valid = false;
                    break;
                }
            }
            if (valid)
                cout << "Case #" << ti << ": 1\n";
            else
                cout << "Case #" << ti << ": 0\n";
            
            continue;
        }
        
        pair<int,int> p = question.back();
        
        int sum = 0;
        bool flag = true;
        while (garden[p.first][p.second] != 0 || flag) {
            
            flow(source);
            
            bool valid = true;
            for (auto item : plants) {
                if (!visited[item.first][item.second]) {
                    valid = false;
                    break;
                }
            }
            sum += valid;
            
            for (int i=0; i<question.size(); ++i) {
                if (flag && i == question.size()-1) flag = false;
                pair<int,int> f = question[i];
                if (++garden[f.first][f.second] > h) {
                    garden[f.first][f.second] = 0;
                }
                else {
                    break;
                }
            }
            for (int i=0; i<4; ++i) {
                for (int j=0; j<4; ++j) {
                    visited[i][j] = false;
                }
            }
        }
        
        cout << "Case #" << ti << ": " << sum << "\n";
    }
    return 0;
}
