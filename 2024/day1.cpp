#include <iostream>
#include <algorithm>
#include <cmath>
#include <ranges>
#include <vector>

int main() {
    auto values = std::ranges::views::istream<int>(std::cin)
        | std::ranges::to<std::vector>();

    auto extract_list = [](auto& list, int offset, int stride) {
        auto extracted_list = list | std::ranges::views::drop(offset) | std::ranges::views::stride(stride);
        std::ranges::sort(extracted_list);
        return extracted_list;
    };

    auto first_list = extract_list(values, 0, 2);
    auto second_list = extract_list(values, 1, 2);

    auto differences = std::ranges::views::zip_transform(
        [](int first, int second) { return std::abs(first - second); },
        first_list,
        second_list
    );
    auto answer = std::ranges::fold_left(differences, 0, std::plus<int>());

    std::cout << answer << std::endl;

    return 0;
}
