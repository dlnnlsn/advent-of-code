#include <iostream>
#include <string>
#include <vector>

int word_search(
    const std::vector<std::string>& grid,
    const std::string& word,
    const int x_stride,
    const int y_stride
) {
    int total = 0;
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            bool found = true;
            size_t cx = x, cy = y;
            for (size_t index = 0; index < word.size(); ++index) {
                if ((cy < 0) || (cy >= grid.size())) {
                    found = false;
                    break;
                }
                if ((cx < 0) || (cx >= grid[cy].size())) {
                    found = false;
                    break;
                }
                if (grid[cy][cx] != word[index]) {
                    found = false;
                    break;
                }
                cy += y_stride; cx += x_stride;
            }
            if (found) ++total;
        }
    }

    return total;
}

int main() {
    int total = 0;
    std::vector<std::string> grid;
    std::string line;
    
    while (std::getline(std::cin, line)) {
        grid.push_back(line);
    }

    total += word_search(grid, "XMAS", 1, 0);
    total += word_search(grid, "XMAS", 1, 1);
    total += word_search(grid, "XMAS", 0, 1);
    total += word_search(grid, "XMAS", -1, 1);
    total += word_search(grid, "XMAS", -1, 0);
    total += word_search(grid, "XMAS", -1, -1);
    total += word_search(grid, "XMAS", 0, -1);
    total += word_search(grid, "XMAS", 1, -1);

    std::cout << total << std::endl;

    return 0;
}
