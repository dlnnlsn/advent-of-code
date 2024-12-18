#define PART_2

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#ifdef PART_2

// Returns -1 if target does not end in the same digits as operand
// Also assumes that operand is not 0 since this never occurs in our input
int64_t deconcatenate(int64_t target, int64_t operand) {
    if (target == operand) return -1;
    while (operand > 0) {
        if ((target % 10) != (operand % 10)) {
            return -1;
        }
        target /= 10;
        operand /= 10;
    }
    return target;
}

#endif

int main() {

    int64_t total_test_values = 0;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream sin(line);
        int64_t target; sin >> target;
        char colon; sin >> colon;

        std::vector<int64_t> numbers;
        int64_t number;
        while (sin >> number) {
            numbers.push_back(number);
        }

        std::vector<int64_t> targets{ target };
        for (auto it = numbers.rbegin(); it != numbers.rend() - 1; ++it) {
            std::vector<int64_t> new_targets;
            for (const int64_t previous_target : targets) {
                // In principle, we should handle the possibility that
                // one of the numbers is 0, but this never happens in
                // the input file
                if ((previous_target % *it) == 0) {
                    new_targets.push_back(previous_target / *it);
                }
                if (previous_target >- *it) {
                    new_targets.push_back(previous_target - *it);
                }

                #ifdef PART_2

                int64_t deconcatenated = deconcatenate(previous_target, *it);
                if (deconcatenated != -1) {
                    new_targets.push_back(deconcatenated);
                }

                #endif
            }
            targets = std::move(new_targets);
        }

        if (std::find(targets.begin(), targets.end(), numbers.front()) != targets.end()) {
            total_test_values += target;
        }
    }

    std::cout << total_test_values << std::endl;

    return 0;
}
