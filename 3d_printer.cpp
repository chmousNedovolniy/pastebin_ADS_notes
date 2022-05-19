#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> items(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> items[i];
    }
    
    int total_response_time = 0, current_item_response_time = 0;
    // actually we have a function for total response time
    // f = n * p_i1 + (n - 1) * p_i2 + ... + 1 * p_in
    // p_ij is item in some optimal permutation of items
    // from function above it is obvious that items should be positioned in ascending order
    // so... just sort 'em
    std::sort(items.begin(), items.end());
    for (auto item : items) {
        current_item_response_time += item;
        total_response_time += current_item_response_time;
    }
    std::cout << 1.0 * total_response_time / n << '\n';
}
