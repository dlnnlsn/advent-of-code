#include <iostream>
#include <string>
#include <vector>

int main() {

    std::vector<std::string> grid;
    std::vector<std::vector<bool>> cell_visited;

    std::string line;
    while (std::getline(std::cin, line)) {
        grid.push_back(line);
        cell_visited.push_back(std::vector<bool>(line.size(), false));
    }

    size_t guard_x = 0, guard_y = 0;
    size_t guard_dx = 0, guard_dy = 0;

    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == '^') {
                guard_y = y;
                guard_x = x;
                guard_dy = -1;
                guard_dx = 0;
                goto guard_found;
            }
            // In priciple we should check for a guard facing
            // some other direction, but the guard in the input
            // is facing up
        }
    }
guard_found:

    size_t total_cells_visited = 0;

    while ((guard_y >= 0) && (guard_y < grid.size()) && (guard_x >= 0) && (guard_x < grid[guard_y].size())) {

        if (grid[guard_y][guard_x] == '#') {
            guard_y -= guard_dy;
            guard_x -= guard_dx;
            size_t tmp = guard_dy;
            guard_dy = guard_dx;
            guard_dx = -tmp;
        }

        if (!cell_visited[guard_y][guard_x]) {
            ++total_cells_visited;
            cell_visited[guard_y][guard_x] = true;
        }

        guard_y += guard_dy;
        guard_x += guard_dx;
    }

    std::cout << total_cells_visited << std::endl;

    return 0;
}
