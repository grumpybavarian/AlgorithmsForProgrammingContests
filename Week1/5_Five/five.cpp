#include <iostream>
#include <string>

int main(int argc, const char * argv[]) {
    int t;
    cin >> t;
    for (int ti=1;ti<t;++ti) {
        string s;
        cin >> s;
        cout << "Case #" << ti << ": " << s << "!\n";
    }
    return 0;
}
