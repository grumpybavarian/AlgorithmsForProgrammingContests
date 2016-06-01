#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << 40 << endl;
    srand(time(0));
    for (int i=0; i<40; ++i) {
        int a = rand() % 4+3;
        int b = rand() % 4+3;
        cout << a << " " << b << endl;
        
        cout << '*';
        for (int j=1; j<16; ++j) {
            if (j % 4 == 0) cout << endl;
            char c;
            int r = rand() % 6;
            if (r<2) {
                c = '_';
            }
            else if (r<5) {
                c = '0' + r;
            }
            else {
                c = '?';
            }
            cout << c;
        }
        cout << endl << endl;
    }
}
