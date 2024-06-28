#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// Function declarations for the tasks
void merge_and_modify(std::vector<int>& v1, const std::vector<int>& v2, int addend){
    std::vector<int> merged = std::vector<int>(v1.size()+v2.size());

    auto it = std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), merged.begin());
    std::transform(merged.begin(), merged.end(), merged.begin(),
                   [addend](int x){ return x + addend; });
    v1 = merged;
}

std::vector<int> remove_and_collect(std::vector<int>& v, const std::set<int>& to_remove){
    std::vector<int> removed_elements = std::vector<int>(to_remove.size());
    auto it = std::copy_if(v.begin(), v.end(), removed_elements.begin(),[to_remove](int x) { return to_remove.count(x); });
    auto it2 = std::remove_if(v.begin(), v.end(), [to_remove](int x) { return to_remove.count(x); });
    return removed_elements;
}

// Main function to run the tests
int main() {
    // Test for merge_and_modify
    std::vector<int> vector1 {1, 3, 5};
    std::vector<int> vector2 {2, 4, 6};
    merge_and_modify(vector1, vector2, 10);
    std::cout << "After merging and modifying: ";
    for (int num : vector1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Test for remove_and_collect
    std::vector<int> vector3 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::set<int> to_remove {1, 3, 5, 7};
    std::vector<int> removed = remove_and_collect(vector3, to_remove);
    std::cout << "Remaining elements: ";
    for (int num : vector3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Removed elements: ";
    for (int num : removed) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
