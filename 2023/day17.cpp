#include <iostream>
#include <bitset>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

enum Direction {
    LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3
};

constexpr int x_offset(const Direction direction) {
    switch (direction) {
        case LEFT: return -1;
        case RIGHT: return 1;
        default: return 0;
    }
}

constexpr int y_offset(const Direction direction) {
    switch (direction) {
        case UP: return -1;
        case DOWN: return 1;
        default: return 0;
    }
}

struct Cell {
    int x = 0; int y = 0;
    Direction direction;
    int64_t cost;

    bool operator>(const Cell& other) const {
        return cost > other.cost;
    }

    Cell(int x, int y, Direction direction, int64_t cost):
        x(x), y(y), direction(direction), cost(cost) {}
};

int main() {

    vector<string> grid;

    string line;
    while (cin >> line) {
        grid.push_back(line);
    }

    int height = grid.size();
    int width = grid[0].size();

    vector<vector<bitset<4>>> visited(height, vector<bitset<4>>(width, bitset<4>()));

    priority_queue<Cell, vector<Cell>, greater<Cell>> to_visit;
    to_visit.push(Cell(0, 0, RIGHT, 0));
    to_visit.push(Cell(0, 0, DOWN, 0));

    int64_t lowest_cost = numeric_limits<int64_t>::max();

    while (!to_visit.empty()) {
        const Cell curr_cell = to_visit.top();
        to_visit.pop();
        if (visited[curr_cell.y][curr_cell.x][curr_cell.direction]) {
            continue;
        }
        visited[curr_cell.y][curr_cell.x][curr_cell.direction] = true;

        if ((curr_cell.x == width - 1) && (curr_cell.y == height - 1)) {
            lowest_cost = min(lowest_cost, curr_cell.cost);
            continue;
        }

        int64_t cost = curr_cell.cost;
        int x = curr_cell.x; int y = curr_cell.y;
        for (int i = 0; i < 3; i++) {
            x += x_offset(curr_cell.direction);
            y += y_offset(curr_cell.direction);

            if (x < 0) break;
            if (x >= width) break;
            if (y < 0) break;
            if (y >= height) break;

            cost += grid[y][x] - '0';

            switch (curr_cell.direction) {
                case UP:
                case DOWN:
                    to_visit.push(Cell(x, y, LEFT, cost));
                    to_visit.push(Cell(x, y, RIGHT, cost));
                    break;
                case LEFT:
                case RIGHT:
                    to_visit.push(Cell(x, y, UP, cost));
                    to_visit.push(Cell(x, y, DOWN, cost));
                    break;
            }
        }
    }

    cout << lowest_cost << endl;

    return 0;
}
