#include <cmath>
#include <iostream>

int number_of_digits(int64_t number) {
    int digits = 0;
    while (number > 0) {
        ++digits; number /= 10;
    }
    return digits;
}

int64_t number_of_stones(int64_t starting_stone, int times_blinked) {
    if (times_blinked == 0) return 1;
    if (starting_stone == 0) {
        return number_of_stones(1, times_blinked - 1);
    }

    const int digits = number_of_digits(starting_stone);
    if (digits % 2 == 1) {
        return number_of_stones(starting_stone * 2024, times_blinked - 1);
    }

    const int64_t power_of_ten = std::pow(10, digits / 2);
    return number_of_stones(starting_stone / power_of_ten, times_blinked - 1)
        + number_of_stones(starting_stone % power_of_ten, times_blinked - 1);
}

int main() {

    int64_t stones = 0;
    int64_t starting_stone;
    while (std::cin >> starting_stone) {
        stones += number_of_stones(starting_stone, 25);
    }

    std::cout << stones << std::endl;

    return 0;
}
