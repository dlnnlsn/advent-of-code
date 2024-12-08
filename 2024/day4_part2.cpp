#include <iostream>
#include <string>
#include <vector>

bool is_xmas(std::vector<std::string>& grid, size_t y, size_t x) {
    if (grid[y][x] != 'A') return false;

    bool down_left_valid = false;
    if (grid[y - 1][x - 1] == 'M') down_left_valid = grid[y + 1][x + 1] == 'S';
    else if (grid[y - 1][x - 1] == 'S') down_left_valid = grid[y + 1][x + 1] == 'M';
    if (!down_left_valid) return false;

    if (grid[y - 1][x + 1] == 'M') {
        if (grid[y + 1][x - 1] == 'S') return true;
    }

    if (grid[y - 1][x + 1] == 'S') {
        if (grid[y + 1][x - 1] == 'M') return true;
    }

    return false;
}

int xmas_search(std::vector<std::string>& grid) {
    int total = 0;

    for (size_t y = 1; y < grid.size() - 1; ++y) {
        for (size_t x = 1; x < grid[y].size() - 1; ++x) {
            if (is_xmas(grid, y, x)) ++total;
        }
    }

    return total;
}

int main() {
    std::vector<std::string> grid;
    std::string line;

    while (std::getline(std::cin, line)) {
        grid.push_back(line);
    }

    std::cout << xmas_search(grid) << std::endl;

    return 0;
}
