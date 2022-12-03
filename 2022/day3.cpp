#include <iostream>

using namespace std;

int main() {

    string rucksack;
    bool left_compartment[52];
    bool right_compartment[52];
    int priority;
    long long int total = 0;

    while (getline(cin, rucksack)) {

        for (int i = 0; i < 52; ++i) {
            left_compartment[i] = false;
            right_compartment[i] = false;
        }

        for (int i = 0; i < rucksack.size()/2; ++i) {
            const char c = rucksack[i];
            if (('a' <= c) && (c <= 'z')) priority = c - 'a' + 1;
            else priority = c - 'A' + 27;
            left_compartment[priority - 1] = true;
        }

        for (int i = rucksack.size()/2; i < rucksack.size(); ++i) {
            const char c = rucksack[i];
            if (('a' <= c) && (c <= 'z')) priority = c - 'a' + 1;
            else priority = c - 'A' + 27;
            if (left_compartment[priority - 1]) {
                if (!right_compartment[priority - 1]) total += priority;
            }
            right_compartment[priority - 1] = true;
        }
    }

    cout << total << endl;

    return 0;
}
