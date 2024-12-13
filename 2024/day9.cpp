#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {

    std::string disk_map;
    std::cin >> disk_map;

    const int disk_size = std::accumulate(disk_map.begin(), disk_map.end(), 0)
        - disk_map.size() * '0';

    std::vector<int> disk;
    disk.reserve(disk_size);

    int file_id = 0;
    bool file = true;

    for (const char c : disk_map) {
        for (int i = 0; i < (c - '0'); ++i) {
            disk.push_back(file ? file_id : -1);
        }
        if (file) ++file_id;
        file = !file;
    }

    int empty_space = 0;
    int to_move = disk.size() - 1;

    int64_t check_sum = 0;

    while (empty_space < to_move) {
        while ((empty_space < to_move) && (disk[empty_space] != -1)) {
            check_sum += static_cast<int64_t>(empty_space) * disk[empty_space];
            ++empty_space;
        }
        while ((to_move > empty_space) && (disk[to_move] == -1)) {
            --to_move;
        }
        if (empty_space != to_move) {
            disk[empty_space] = disk[to_move];
            disk[to_move] = -1;
        }
    }
    if ((empty_space == to_move) && (disk[empty_space] != -1)) {
        check_sum += static_cast<int64_t>(empty_space) * disk[empty_space];
    }

    std::cout << check_sum << std::endl;

    return 0;
}
