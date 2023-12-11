#include <iostream>
#include <algorithm>

using namespace std;

int64_t process_coordinates(vector<int>& coords) {
    sort(coords.begin(), coords.end());

    int64_t total = 0;
    for (int i = 0; i < coords.size();) {
        int j = i + 1;
        while ((j < coords.size()) && (coords[j] == coords[i])) {
            j++;
        }

        total += 2 * (j - i) * i * coords[i]; 
        total -= 2 * (j - i) * (coords.size() - j) * coords[i];
        total -= j * (coords.size() - j);

        i = j;
    }

    return total;
}

int main() {
    vector<int> x_coords;
    vector<int> y_coords;

    int y = 0;
    string line;
    while (cin >> line) {
        for (int x = 0; x < line.size(); x++) {
            if (line[x] == '#') {
                x_coords.push_back(x);
                y_coords.push_back(y);
            }
        }
        y++;
    }

    int64_t total_distance = process_coordinates(x_coords);
    total_distance += process_coordinates(y_coords);

    cout << total_distance << endl;

    return 0;
}
