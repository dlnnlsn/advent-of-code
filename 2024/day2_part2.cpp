#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

bool pair_valid(const int first, const int second) {
    if (first == second) return false;
    if (std::abs(first - second) > 3) return false;
    return true;
}

enum class SequenceType {
    Empty,
    Singleton,
    ValidIncreasing,
    ValidDecreasing,
    Invalid
};

bool compatible(SequenceType first, SequenceType second) {
    if (first == SequenceType::Invalid || second == SequenceType::Invalid) return false;
    if (first == SequenceType::ValidIncreasing || first == SequenceType::ValidDecreasing) return first != second;
    return true;
}

template <typename InputIterator, typename OutputIterator>
void safe_prefix(InputIterator levels_begin, InputIterator levels_end, OutputIterator prefix_begin) {
    if (levels_begin == levels_end) return;
    auto first = *(levels_begin++);
    *(prefix_begin++) = SequenceType::Empty;

    if (levels_begin == levels_end) return;
    auto second = *(levels_begin++);
    *prefix_begin = SequenceType::Singleton;

    bool increasing = (first < second);
    
    for (; levels_begin != levels_end;
        first = second,
        second = *levels_begin,
        ++levels_begin
    ) {
        if (*prefix_begin == SequenceType::Invalid) {
            *(++prefix_begin) = SequenceType::Invalid;
            continue;
        }
        if (!pair_valid(first, second)) {
            *(++prefix_begin) = SequenceType::Invalid;
            continue;
        }
        if ((first < second) != increasing) {
            *(++prefix_begin) = SequenceType::Invalid;
            continue;
        }
        *(++prefix_begin) = increasing ? SequenceType::ValidIncreasing : SequenceType::ValidDecreasing;
    }
}

bool safe(std::string& record) {
    std::istringstream sin(record);

    std::vector<int> levels;
    int level;
    while (sin >> level) {
        levels.push_back(level);
    }

    if (levels.size() < 3) return true;

    std::vector<SequenceType> valid_prefix(levels.size());
    safe_prefix(levels.begin(), levels.end(), valid_prefix.begin());
    if (valid_prefix.back() != SequenceType::Invalid) return true;

    std::vector<SequenceType> valid_suffix(levels.size());
    safe_prefix(levels.rbegin(), levels.rend(), valid_suffix.rbegin());
    if (valid_suffix.front() != SequenceType::Invalid) return true;

    for (size_t index = 1; index < levels.size() - 1; ++index) {
        if (!compatible(valid_prefix[index], valid_suffix[index])) continue;
        if (!pair_valid(levels[index - 1], levels[index + 1])) continue;
        if (
            valid_prefix[index] == SequenceType::ValidIncreasing
            || valid_suffix[index] == SequenceType::ValidDecreasing
        ) {
            if (levels[index - 1] < levels[index + 1]) return true;
        }
        else if (
            valid_prefix[index] == SequenceType::ValidDecreasing
            || valid_suffix[index] == SequenceType::ValidIncreasing
        ) {
            if (levels[index - 1] > levels[index + 1]) return true;
        }
    }

    return false;
}

int main() {

    int safe_count = 0;

    std::string record;
    while (std::getline(std::cin, record)) {
        if (safe(record)) ++safe_count;
    }

    std::cout << safe_count << std::endl;

    return 0;
}
