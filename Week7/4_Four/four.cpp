#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

bool comp(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b) {
    if (a.second == b.second) {
        return (a.first.first == a.first.second && b.first.first != b.first.second);
    }
    return a.second > b.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n,m;
        cin >> n >> m;
        vector<string> human(n);
        for (int i=0; i<n; ++i) {
            cin >> human[i];
            
        }
        vector<string> mice(m);
        for (int i=0; i<m; ++i) {
            cin >> mice[i];
        }
        vector<vector<int>> pairCount(4,vector<int>(4));
        for (int i=0; i<n; ++i) {
            for (int j=0; j<m; ++j) {
                for (int k=0; k<human[0].length(); ++k) {
                    int a,b;
                    switch (human[i].at(k)) {
                        case 'A':
                            a=0;
                            break;
                        case 'C':
                            a=1;
                            break;
                        case 'T':
                            a=2;
                            break;
                        case 'G':
                            a=3;
                            break;
                        default:
                            break;
                    }
                    switch (mice[j].at(k)) {
                        case 'A':
                            b=0;
                            break;
                        case 'C':
                            b=1;
                            break;
                        case 'T':
                            b=2;
                            break;
                        case 'G':
                            b=3;
                            break;
                        default:
                            break;
                    }
                    ++pairCount[a][b];
                    pairCount[b][a] = pairCount[a][b];
                }
            }
        }
        vector<pair<pair<int,int>,int>> counts;
        counts.reserve(10);
        for (int i=0; i<4; ++i) {
            for (int j=i; j<4; ++j) {
                if (i != j)
                    counts.push_back({{i,j},pairCount[i][j]});
                else
                    counts.push_back({{i,j},2*pairCount[i][j]});
            }
        }
        sort(counts.begin(), counts.end(), comp);
        
        int sum = 0;
        int score = 0;
        int index = 0;
        int sumNeg = 120;
        while (sum <= sumNeg) {
            auto item = counts[index];
            if (item.first.first == item.first.second) {
                if (sum + 10 <= sumNeg) {
                    sum += 10;
                    score += item.second * 5;
                }
            }
            else {
                if (sum + 20 <= sumNeg) {
                    sum += 20;
                    sumNeg -= 20;
                    score += item.second * 10;
                }
                else if (sum + 10 <= sumNeg) {
                    sum += 10;
                    sumNeg -= 10;
                    score += item.second * 5;
                }
                else {
                    break;
                }
            }
            ++index;
        }
        
        index = 9;
        while (sum > 0) {
            auto item = counts[index--];
            if (item.first.first == item.first.second) continue;
            if (sum >= 20) {
                score -= item.second * 10;
                sum -= 20;
            }
            else if (sum >= 10) {
                score -= item.second * 5;
                sum -= 10;
            }
            else {
                score -= item.second * sum / 2;
                sum -= sum;
            }
        }
       
        cout << "Case #" << ti << ": " << score << endl;
    }
    
    return 0;
}