#include <iostream>
#include <string>
#include <vector>

int main() {

    size_t number_antinodes = 0;

    std::vector<std::string> grid;
    std::vector<std::vector<bool>> antinodes;

    std::string line;
    while (std::getline(std::cin, line)) {
        grid.push_back(line);
        antinodes.push_back(std::vector<bool>(line.size(), false));
    }

    for (size_t y1 = 0; y1 < grid.size(); ++y1) {
        for (size_t x1 = 0; x1 < grid[y1].size(); ++x1) {
            for (size_t y2 = 0; y2 < grid.size(); ++y2) {
                for (size_t x2 = 0; x2 < grid[y2].size(); ++x2) {
                    if ((y1 == y2) && (x1 == x2)) {
                        continue;
                    }
                    if ((grid[y1][x1] == '.') || (grid[y2][x2] == '.')) {
                        continue;
                    }
                    if (grid[y1][x1] != grid[y2][x2]) {
                        continue;
                    }
                    
                    const size_t antinode_y = 2*y1 - y2;
                    const size_t antinode_x = 2*x1 - x2;

                    if ((antinode_y >= 0) && (antinode_y < grid.size())) {
                        if ((antinode_x >= 0) && (antinode_x < grid[antinode_y].size())) {
                            if (!antinodes[antinode_y][antinode_x]) {
                                antinodes[antinode_y][antinode_x] = true;
                                ++number_antinodes;
                            }
                        }
                    }

                }
            }
        }
    }

    std::cout << number_antinodes << std::endl;

    return 0;
}
