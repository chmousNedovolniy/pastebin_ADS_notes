#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // consider n > 0
    int n;
    std::cin >> n;
    std::vector<int> houses(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> houses[i];
    }
    // also consider that solution can be found with given d
    int d;
    std::cin >> d;

    // sorting houses
    std::sort(houses.begin(), houses.end());
    std::vector<int> repeaters;
    // first repeater covers [houses[0] + d; houses[0] + d + d]
    // thus, covers houses[0] and maybe sth else
    repeaters.push_back(houses[0] + d);
    int covered_right_border = houses[0] + 2 * d;
    // for every other house it's either
    // 1) covered
    // 2) should be covered in "optimal" way the same as houses[0]
    for (int i = 1; i < n; ++i) {
        if (houses[i] <= covered_right_border) {
            continue;
        }
        repeaters.push_back(houses[i] + d);
        covered_right_border = houses[i] + 2 * d;
    }

    for (auto repeater_pos : repeaters) {
        std::cout << repeater_pos << ' ';
    }
    std::cout << '\n';
}