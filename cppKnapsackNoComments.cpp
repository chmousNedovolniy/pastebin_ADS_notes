#include <iostream>
#include <set>
#include <string>
#include <vector>

class Item {
public:
    std::string name_{};
    int weight_{};
    int value_{};
    
    bool operator < (const Item& other) const {
        return name_ < other.name_;
    }
};

using Knapsack = std::multiset<Item>;

void UnboundedKnapsack(int w, int n, std::vector<Item> items, std::vector<Knapsack> knapsacks) {
    std::vector<int> ans(w + 1);
    ans[0] = 0;
    for (int x = 1; x <= w; ++x) {
        ans[x] = 0;
        for (int item = 1; item <= n; ++item) {
            if (items[item - 1].weight_ <= x) {
                if (ans[x - items[item - 1].weight_] + items[item - 1].value_ > ans[x]) {
                    ans[x] = ans[x - items[item - 1].weight_] + items[item - 1].value_;
                    knapsacks[x] = knapsacks[x - items[item - 1].weight_];
                    knapsacks[x].insert(items[item - 1]);
                }
            }
        }
    }
    for (int x = 0; x <= w; ++x) {
        std::cout << "weight is " << x << ' ';
        std::cout << "value is " << ans[x] << '\n';
        std::cout << "items: ";
        if (knapsacks[x].empty()) {
            std::cout << "empty";
        }
        for (const Item& item : knapsacks[x]) {
            std::cout << item.name_ << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    int w = 3;
    int n = 3;
    Item heart = {"heart", 1, 1};
    Item diamond = {"diamond", 2, 4};
    Item cross = {"cross", 3, 6};
    std::vector<Item> items = {heart, diamond, cross};
    std::vector<Knapsack> knapsacks(w + 1);
    UnboundedKnapsack(w, n, items, knapsacks);
    return 0;
}