#include <iostream>
#include <string>

using namespace std;

const vector<string> digits = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

struct DigitMatch {
    bool did_match;
    int value;

    DigitMatch(bool did_match, int value):
        did_match(did_match), value(value) {
    }
};

DigitMatch match(string& line, int index) {
    if (('0' <= line[index]) && (line[index] <= '9')) {
        return DigitMatch(true, line[index] - '0');
    }

    for (int value = 1; value < 10; value++) {
        string candidate = digits[value - 1];
        if (line.size() - index < candidate.size()) {
            continue;
        }
        bool matches = true;
        for (int i = 0; i < candidate.size(); i++) {
            if (line[index + i] != candidate[i]) {
                matches = false;
                break;
            }
        }
        if (matches) {
            return DigitMatch(true, value);
        }
    }

    return DigitMatch(false, -1);
}

int main() {

    string line;
    int64_t total = 0;

    while (cin >> line) {
        int index = 0;
        int left_most = -1;
        int right_most = -1;

        for (int index = 0; index < line.size(); index++) {
            DigitMatch current_match = match(line, index);
            if (current_match.did_match) {
                if (left_most == -1) left_most = current_match.value;
                right_most = current_match.value;
            }
        }

        total += 10 * left_most + right_most;
    }

    cout << total << endl;
    
    return 0;
}
