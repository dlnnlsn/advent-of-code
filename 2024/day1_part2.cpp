#include <iostream>
#include <map>

int main() {
    long long int total = 0;
    std::map<int, int> first_list_counts;
    std::map<int, int> second_list_counts;

    int first, second;
    while (std::cin >> first >> second) {
        ++first_list_counts[first];
        ++second_list_counts[second];
    }

    for (const auto& [value, count] : first_list_counts) {
        total += static_cast<long long int>(count) * value * second_list_counts[value];
    }

    std::cout << total << std::endl;

    return 0;
}
