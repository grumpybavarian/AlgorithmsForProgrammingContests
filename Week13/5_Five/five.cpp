#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

int main() {
    ifstream file;
    string line;
    file.open("pi.txt");
    vector<int> count(10);
    int progress = 0;
    while (getline(file, line)) {
        for(auto i : line) {
            ++count[i - '0'];
        }
        cout << ++progress / 20000.0 << endl;
    }
    for (int i=0; i<10; ++i) {
        cout << i << ": " << count[i] << " " << count[i]-100000 << endl;
    }
    cout << endl;
    int sum = 0;
    for (int i=0; i<10; ++i) {
        sum += (count[i]-100000)*(count[i]-100000);
    }
    cout << "sum: " << sum << endl;
    
    return 0;
}