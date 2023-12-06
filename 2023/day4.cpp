#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    int64_t total_points = 0;

    string word;
    int num;
    cin >> word; // Read the Card at the start of the line
    do {
        cin >> num;  // Read the card number
        cin >> word; // And the colon

        unordered_set<int> winning_numbers;
        while (cin >> num) {
            winning_numbers.insert(num);
        }

        cin.clear();
        cin >> word; // Read the | separating winning from card numbers

        int64_t card_value = 0;
        while (cin >> num) {
            if (!winning_numbers.count(num)) {
                continue;
            }
            if (card_value) card_value *= 2;
            else card_value = 1;
        }
        cin.clear();
        total_points += card_value;
    } while (cin >> word); // Read the Card and continue while there is a new one

    cout << total_points << endl;;

    return 0;
}
