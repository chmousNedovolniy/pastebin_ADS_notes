#include <iostream>
#include <vector>

using namespace std;

int HoarePartition(vector<int>& nums, int left, int right) {
    int pivot = nums[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (nums[i] < pivot) {
            ++i;
        }
        while (nums[j] > pivot) {
            --j;
        }
        if (i >= j) {
            break;
        }
        swap(nums[i++], nums[j--]);
    }
    return j;
}

int LomutoPartition(vector<int>& nums, int left, int right) {
    int pivot = nums[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (nums[j] <= pivot) {
            ++i;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i + 1], nums[right]);
    return i + 1;
}

void Quicksort(vector<int>& nums, int left, int right) {
    if (left < right) {
        // Lomuto option.
        int partition_pos = LomutoPartition(nums, left, right);
        Quicksort(nums, left, partition_pos - 1);
        
        // Hoare option.
        // int partition_pos = HoarePartition(nums, left, right);
        // Quicksort(nums, left, partition_pos);

        Quicksort(nums, partition_pos + 1, right);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto& elem: nums) {
        cin >> elem;
    }
    Quicksort(nums, 0, nums.size() - 1);
    for (auto& elem: nums) {
        cout << elem << ' ';
    }
    cout << '\n';
}