#include <stdlib.h>
#include "BinarySearch.h"


int BinarySearch::binary_search(std::vector<int>& nums, int target) {
    auto left = 0;
    auto right = nums.size() - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    } 
    return -1;
}