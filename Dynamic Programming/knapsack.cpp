#include <array>
#include <cassert>
#include <iostream>
#include <vector>

namespace knapsack{
    /**
    * @brief Picking up all those items whose combined weight is below
    * given capacity and calculating value of those picked items.Trying all
    * possible combinations will yield the maximum knapsack value.
    * @tparam n size of the weight and value array
    * @param capacity capacity of the carrying bag
    * @param weight array representing weight of items
    * @param value array representing value of items
    * @return maximum value obtainable with given capacity.
    */
    template <size_t n>
    int maxKnapsackValue(const int capacity,
                        const std::array<int, n> &weight,
                        const std::array<int, n> &value) {
        std::vector<std::vector<int> > maxValue(n+1, std::vector<int>(capacity+1,0));
        int items = sizeof(weight) / sizeof(weight[0]);
        for (size_t i = 0; i < items+1; i++){
            for (size_t j = 0; j < capacity+1; i++){
                if (i == 0 || j == 0){
                    maxValue[i][j] = 0;
                }
                else if (weight[i-1] <= j){
                    int profit1 = value[i-1] + maxValue[i-1][j-weight[i-1]];
                    int profit2 = maxValue[i-1][j];
                    maxValue[i][j] = std::max(profit1, profit2);
                }
                else {
                    maxValue[i][j] = maxValue[i-1][j];
                }
            }
        }
        return maxValue[items][capacity];
    }
}

static void test() {
    const int n1 = 3;
    std::array<int, n1> weight1 = {10, 20, 30};   // weight of each item
    std::array<int, n1> value1 = {60, 100, 120};  // value of each item
    const int capacity1 = 50;                     // capacity of carrying bag
    const int max_value1 = knapsack::maxKnapsackValue(
        capacity1, weight1, value1);
    const int expected_max_value1 = 220;
    assert(max_value1 == expected_max_value1);
    std::cout << "Maximum Knapsack value with " << n1 << " items is "
              << max_value1 << std::endl;

    // Test 2
    const int n2 = 4;                               // number of items
    std::array<int, n2> weight2 = {24, 10, 10, 7};  // weight of each item
    std::array<int, n2> value2 = {24, 18, 18, 10};  // value of each item
    const int capacity2 = 25;                       // capacity of carrying bag
    const int max_value2 = knapsack::maxKnapsackValue(
        capacity2, weight2, value2);
    const int expected_max_value2 = 36;
    assert(max_value2 == expected_max_value2);
    std::cout << "Maximum Knapsack value with " << n2 << " items is "
              << max_value2 << std::endl;
}

int main() {
    // Testing
    test();
    return 0;
}