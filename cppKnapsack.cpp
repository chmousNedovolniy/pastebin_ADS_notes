#include <iostream>
#include <set>
#include <string>
#include <vector>

class Item {
public:
    std::string name_{};
    int weight_{};
    int value_{};

    // this thing is required for the set to work properly (it needs to compare elements)
    bool operator < (const Item& other) const {
        // i would compare Items by their names, so their order in sets would be lexicographical
        return name_ < other.name_;
    }
};

// it's for simplifying the code, let's just call std::multiset<Item> a Knapsack
using Knapsack = std::multiset<Item>;

// we get max weight of knapsack w, number of different items n, those items, and empty knapsacks
void UnboundedKnapsack(int w, int n, std::vector<Item> items, std::vector<Knapsack> knapsacks) {
    // For x = 1,...,w, ans[x] is the optimal value for knapsacks[x]
    // optimal value for knapsack with weight W is max sum value of items such as that their sum weight <= W
    std::vector<int> ans(w + 1);
    // 0 capacity knapsack can be filled with items -> ans = 0
    ans[0] = 0;
    // for each possible weight of knapsack (not empty - not starting with 0)
    for (int x = 1; x <= w; ++x) {
        // in the beginning knapsack[x] is empty
        ans[x] = 0;
        // try to put different items in knapsack
        for (int item = 1; item <= n; ++item) {
            // if we can put an item in knapsack (item is not too heavy)
            if (items[item - 1].weight_ <= x) {
                // if we free some weight and put new item and ans will be better, we should put new item in knapsack
                if (ans[x - items[item - 1].weight_] + items[item - 1].value_ > ans[x]) {
                    // increase ans
                    ans[x] = ans[x - items[item - 1].weight_] + items[item - 1].value_;
                    // get all old items
                    knapsacks[x] = knapsacks[x - items[item - 1].weight_];
                    // add new item
                    knapsacks[x].insert(items[item - 1]);
                }
            }
        }
    }

    // for all weights of knapsacks
    for (int x = 0; x <= w; ++x) {
        // let's print weight of knapsack
        std::cout << "weight is " << x << ' ';
        // and answer(max value) for this weight of knapsack
        std::cout << "value is " << ans[x] << '\n';
        // printing all items in x-th knapsack
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
    // max weight
    int w = 3;
    // number of different items
    int n = 3;

    // initializing items
    Item heart = {"heart", 1, 1};
    Item diamond = {"diamond", 2, 4};
    Item cross = {"cross", 3, 6};
    std::vector<Item> items = {heart, diamond, cross};

    //  For x = 0,1,...w, knapsacks[x] is a knapsack with capacity x
    std::vector<Knapsack> knapsacks(w + 1);
    UnboundedKnapsack(w, n, items, knapsacks);

    return 0;
}