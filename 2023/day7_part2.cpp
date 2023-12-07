#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

int card_value(char card) {
    switch (card) {
        case 'T': return 10;
        case 'J': return 1;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 14;
        default: return card - '0';
    }
}

enum HandCategory {
    FIVE_OF_A_KIND = 7,
    FOUR_OF_A_KIND = 6,
    FULL_HOUSE = 5,
    THREE_OF_A_KIND = 4,
    TWO_PAIR = 3,
    ONE_PAIR = 2,
    HIGH_CARD = 1,
    EMPTY_HAND = 0
};

class Hand {
private:
    string _cards;
    HandCategory _category;
public:
    int bid;

    Hand(): _cards(""), _category(EMPTY_HAND) {} 

    Hand(string cards, int bid): bid(bid) {
        set_cards(cards);
    }

    bool operator<(const Hand& other) const {
        if (_category < other._category) return true;
        if (_category > other._category) return false;
        for (int i = 0; i < _cards.size(); i++) {
            if (i >= other._cards.size()) return false;
            if (card_value(_cards[i]) < card_value(other._cards[i])) return true;
            if (card_value(_cards[i]) > card_value(other._cards[i])) return false;
        }
        return false;
    }

    void set_cards(string cards) {
        _cards = cards;

        if (_cards.size() == 0) {
            _category = EMPTY_HAND;
            return;
        }

        unordered_map<char, int> counts;
        for (const char c : _cards) {
            counts[c]++;
        }

        bool has_triple = false;
        int num_pairs = 0;

        if (counts['J'] >= 4) {
            _category = FIVE_OF_A_KIND;
            return;
        }

        for (const auto& [card, count] : counts) {
            if (card == 'J') continue;
            if (count + counts['J'] == 5) {
                _category = FIVE_OF_A_KIND;;
                return;
            }
            if (count + counts['J'] == 4) {
                _category = FOUR_OF_A_KIND;
                return;
            }
            if (count == 3) has_triple = true;
            if (count == 2) ++num_pairs;
        }

        if (num_pairs == 2 && counts['J'] >= 1) {
            _category = FULL_HOUSE;
            return;
        }

        if (num_pairs == 1 && counts['J'] >= 1) {
            _category = THREE_OF_A_KIND;
            return;
        }

        if (counts['J'] == 2) {
            _category = THREE_OF_A_KIND;
            return;
        }

        if (counts['J'] == 1) {
            _category = ONE_PAIR;
            return;
        }

        if (has_triple) {
            if (num_pairs > 0) _category = FULL_HOUSE;
            else _category = THREE_OF_A_KIND;
        }
        else if (num_pairs > 0) {
            if (num_pairs == 2) _category = TWO_PAIR;
            else _category = ONE_PAIR;
        }
        else {
            _category = HIGH_CARD;
        }
    }

    string cards() const {
        return _cards;
    }
};

istream& operator>>(istream& input, Hand& value) {
    string cards; int bid;
    if (input >> cards >> bid) {
        value.set_cards(cards);
        value.bid = bid;
    }
    return input;
}

ostream& operator<<(ostream& output, const Hand& value) {
    return output << value.cards() << " " << value.bid;
}

int main() {

    vector<Hand> hands;
    Hand hand;
    while (cin >> hand) {
        hands.push_back(hand);
    }

    sort(hands.begin(), hands.end());

    int64_t total_winnings = 0;
    for (int i = 0; i < hands.size(); i++) {
        #ifdef DEBUG
            cout << hands[i] << endl;
        #endif
        total_winnings += (i + 1) * hands[i].bid;
    }

    cout << total_winnings << endl;

    return 0;
}
