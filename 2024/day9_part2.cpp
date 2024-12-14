#include <iostream>
#include <map>
#include <string>
#include <vector>

struct FileRecord {
    int file_id;
    int starting_block;
    int number_blocks;
};

int main() {

    std::string line;
    std::cin >> line;

    std::map<int, int> empty_space;
    std::vector<FileRecord> files;

    bool file = true;
    int file_id = 0;
    int starting_block = 0;

    for (char c : line) {
        if (file) {
            files.push_back({ file_id++, starting_block, c - '0' });
        }
        else {
            if (c != '0') {
                empty_space[starting_block] = c - '0';
            }
        }
        starting_block += (c - '0');
        file = !file;
    }

    for (auto file_it = files.rbegin(); file_it != files.rend(); ++file_it) {
        empty_space[file_it->starting_block] = file_it->number_blocks;
        for (auto [empty_start, empty_blocks] : empty_space) {
            if (empty_blocks >= file_it->number_blocks) {
                file_it->starting_block = empty_start;
                empty_space.erase(empty_start);
                if (empty_blocks != file_it->number_blocks) {
                    empty_space[empty_start + file_it->number_blocks] = empty_blocks - file_it->number_blocks;
                }
                break;
            }
        }
    }

    int64_t checksum = 0;
    for (FileRecord file : files) {
        checksum += static_cast<int64_t>(file.number_blocks) *
         (static_cast<int64_t>(file.starting_block) * 2 + file.number_blocks - 1) / 2 *
         file.file_id;
    }

    std::cout << checksum << std::endl;

    return 0;
}
