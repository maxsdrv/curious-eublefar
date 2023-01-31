#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>
#include <memory>
#include <forward_list>
#include <list>
#include <cassert>
#include <random>

#include "LinkedList.h"
#include "MyArray.h"
#include "BinarySearch.h"
#include "profile.h"

void print(const char* array) {
	std::copy(array, array+sizeof(array), std::ostream_iterator<char>(std::cout << " "));
}

int binary_search(std::vector<int>& vec, int target) {
	auto b = std::binary_search(std::begin(vec), std::end(vec), target);	
	if (b > 0)
	{
		auto res = std::lower_bound(std::begin(vec), std::end(vec), target);
		return (res - std::begin(vec));
	}
	return -1;
}
int getIndexArray(std::vector<int>& v, int target) {
	static int arr[10] {};
	int j = 0;
	int* it {};
	for (const auto& i : v) {
		arr[j] = i;
		++j;
	}
	for (int i = 0; i < sizeof(arr); ++i) {
		if (target == arr[i]) {
			return (&arr[i] - &arr[0]);
		}	
	}	
	return -1;
}

ListNode* modern_merge_list(ListNode* a, ListNode* b) {
	std::forward_list<int> list;
	LOG_DURATION("modern_merge_list")
	while (a->next) {
		list.push_front(a->val);
		a = a->next;
	}
	for(const auto& l : list) {
		std::cout << l << "->";
	}	
	std::cout << '\n';
}

int main(int argc, char* argv[]) {
	std::vector<int> v {-1};
	auto res = binary_search(v, 2);
	std::cout << "Result Binary Search = " << res << '\n';	
	std::vector<int> arr {1 , 2, 4, 6, 7};
	std::cout << "Index array = " << getIndexArray(arr, 1) << '\n';

	auto list_a = new LinkedList;
	auto list_b = new LinkedList;
	LOG_DURATION("main")
	for (int i = 0; i < 100000; ++i) {
		list_a->push_front(i);
	}	
	for (int i = 10; i < 20; ++i) {
		list_b->push_front(i);
	}
	auto list1 = LinkedList::get_list(list_a);
	auto list2 = LinkedList::get_list(list_b);

	auto list_result = modern_merge_list(list1, list2);


	return 0;
}




