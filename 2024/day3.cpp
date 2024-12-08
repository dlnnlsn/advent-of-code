#include <iostream>
#include <regex>
#include <string>

long long int total_of_multiplications(std::string& line) {
    long long int total = 0;
    std::regex multiplication_regex("mul\\((\\d+),(\\d+)\\)");
    auto multiplications_begin = std::sregex_iterator(line.begin(), line.end(), multiplication_regex);
    auto multiplications_end = std::sregex_iterator();

    for (auto match_it = multiplications_begin; match_it != multiplications_end; ++match_it) {
        auto match = *match_it;
        long long int first = std::stoll(match[1]);
        long long int second = std::stoll(match[2]);
        total += (first * second);
    }
    return total;
}

int main() {
    
    long long int total = 0;

    std::string line;
    while (std::getline(std::cin, line)) {
        total += total_of_multiplications(line);
    }
    std::cout << total << std::endl;

    return 0;
}
