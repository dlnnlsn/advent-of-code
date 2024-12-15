#include <iostream>
#include <stack>
#include <utility>
#include <vector>

int dfs(const std::vector<std::string>& map, int x, int y) {
    std::vector<std::vector<bool>> visited(
        map.size(),
        std::vector<bool>(map[0].size(), false)
    );

    int nines = 0;

    std::stack<std::pair<int, int>> to_visit;
    to_visit.push({ x, y });

    while (!to_visit.empty()) {
        auto [cx, cy] = to_visit.top();
        to_visit.pop();

        visited[cy][cx] = true;
        if (map[cy][cx] == '9') {
            ++nines;
            continue;
        }

        const char current_height = map[cy][cx];
        auto push = [current_height, &to_visit, &map, &visited](int x, int y) -> void {
            if (y < 0) return;
            if (y >= map.size()) return;
            if (x < 0) return;
            if (x >= map[y].size()) return;
            if (visited[y][x]) return;
            if (map[y][x] == (current_height + 1)) {
                to_visit.push({ x, y });
            }
        };

        push(cx - 1, cy);
        push(cx + 1, cy);
        push(cx, cy - 1);
        push(cx, cy + 1);
    }

    return nines;
}

int main() {

    std::vector<std::string> map;
    std::string line;

    while (std::getline(std::cin, line)) {
        map.push_back(line);
    }

    int score = 0;

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == '0') {
                score += dfs(map, x, y);
            }
        }
    }

    std::cout << score << std::endl;
    return 0;
}
