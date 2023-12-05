#include <iostream>
#include <string>

using namespace std;

int main() {

    string line;
    int64_t total = 0;

    while (cin >> line) {
        int digit = 0;
        for (int i = 0; i < line.size(); i++) {
            const char c = line[i];
            if (('0' <= c) && (c <= '9')) {
                digit = c - '0';
                break;
            }
        }
        total += 10 * digit;

        for (int i = line.size() - 1; i >= 0; i--) {
            const char c = line[i];
            if (('0' <= c) && (c <= '9')) {
                digit = c - '0';
                break;
            }
        }
        total += digit;
    }

    cout << total << endl;
    
    return 0;
}
