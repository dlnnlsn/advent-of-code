#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

bool pair_valid(const int first, const int second) {
    if (first == second) return false;
    if (std::abs(first - second) > 3) return false;
    return true;
}

bool safe(std::string& record) {
    std::istringstream sin(record);

    int first, second;
    sin >> first >> second;

    if (!pair_valid(first, second)) return false;

    bool increasing = first < second;

    first = second;
    while (sin >> second) {
        if (!pair_valid(first, second)) return false;
        if ((first < second) != increasing) return false;
        first = second;
    }

    return true;
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
