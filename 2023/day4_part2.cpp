#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    vector<int> scratchcard_counts;
    vector<int> number_winning_numbers;

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

        int num_winning = 0;
        while (cin >> num) {
            num_winning += winning_numbers.count(num);
        }
        cin.clear();

        scratchcard_counts.push_back(1);
        number_winning_numbers.push_back(num_winning);
    } while (cin >> word); // Read the Card and continue while there is a new one
    
    int64_t total_scratchcards = 0;

    for (int i = 0; i < scratchcard_counts.size(); i++) {
        for (int j = 1; j <= number_winning_numbers[i]; j++) {
            scratchcard_counts[i + j] += scratchcard_counts[i];
        }
        total_scratchcards += scratchcard_counts[i];
    }

    cout << total_scratchcards << endl;

    return 0;
}
