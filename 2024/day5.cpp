#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef std::pair<int, int> Rule;

bool page_order_valid(const std::vector<int>& pages_to_print, const std::vector<Rule>& rules) {
    for (size_t i = 0; i < pages_to_print.size() - 1; ++i) {
        for (size_t j = i + 1; j < pages_to_print.size(); ++j) {
            for (const auto& [earlier, later] : rules) {
                if ((earlier == pages_to_print[j]) && (later == pages_to_print[i])) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    std::vector<Rule> rules;

    std::string line;
    while (std::getline(std::cin, line), line != "") {
        size_t pipe_index = line.find('|');
        int earlier = std::stoi(line.substr(0, pipe_index));
        int later = std::stoi(line.substr(pipe_index + 1));
        rules.push_back({earlier, later});
    }

    int64_t middle_total = 0;
    std::vector<int> pages_to_print;

    while (std::getline(std::cin, line)) {
        std::istringstream sin(line);
        pages_to_print.clear();

        int page; char comma;
        while (sin >> page) {
            pages_to_print.push_back(page);
            sin >> comma;
        }

        if (page_order_valid(pages_to_print, rules)) {
            middle_total += pages_to_print[pages_to_print.size() / 2];
        }
    }

    std::cout << middle_total << std::endl;

    return 0;
}
