#include <iostream>
#include <vector>

int main() {

    std::vector<std::string> map;
    std::string line;

    while (std::getline(std::cin, line)) {
        map.push_back(line);
    }

    std::vector<std::vector<int64_t>> rating(
        map.size(), std::vector<int64_t>(map[0].size(), 0)
    );

    int64_t total_rating = 0;

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == '9') {
                rating[y][x] = 1;
            }
        }
    }

    for (int height = 8; height >= 0; --height) {
        for (int y = 0; y < map.size(); ++y) {
            for (int x = 0; x < map[y].size(); ++x) {
                if (map[y][x] != ('0' + height)) continue;
                if ((x >= 1) && (map[y][x - 1] == ('0' + height + 1))) {
                    rating[y][x] += rating[y][x - 1];
                }
                if ((x < map[y].size() - 1) && (map[y][x + 1] == ('0' + height + 1))) {
                    rating[y][x] += rating[y][x + 1];
                }
                if ((y >= 1) && (map[y - 1][x] == ('0' + height + 1))) {
                    rating[y][x] += rating[y - 1][x];
                }
                if ((y < map.size() - 1) && (map[y + 1][x] == ('0' + height + 1))) {
                    rating[y][x] += rating[y + 1][x];
                }
            }
        }
    }

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == '0') {
                total_rating += rating[y][x];
            }
        }
    }

    std::cout << total_rating << std::endl;
    return 0;
}
