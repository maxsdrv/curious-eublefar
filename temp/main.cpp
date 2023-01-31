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

std::ostream& operator<<(std::ostream& os, const std::forward_list<int>& list) {
	for (const auto& l : list) {
		os << ' ' << l;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, ListNode* l) {
	while (l != nullptr) {
		os << l->val << "->";
		l = l->next;
	}
	os << '\n';
	return os;
}

ListNode* modern_merge_list(ListNode* a, ListNode* b) {
	std::forward_list<int> list_a;
	std::forward_list<int> list_b;
	LOG_DURATION("modern_merge_list")
	while (a->next) {
		list_a.push_front(a->val);
		a = a->next;
	}
	while (b->next) {
		list_b.push_front(b->val);
		b = b->next;
	}
	std::cout << '\n';
	list_a.sort();
	list_b.sort();
	std::cout << "List1: " << list_a << '\n';
	std::cout << "List2: " << list_b << '\n';
	list_a.splice_after(list_b.begin(), list_a);
	std::cout << "List1: " << list_a << '\n';
	std::cout << "List2: " << list_b << '\n';

}
using F = std::forward_list<ListNode*>;
ListNode* merge_k(ListNode* a, ListNode* b) {

}
ListNode* modern_mergeK_lists(std::vector<ListNode*>& vec) {
	int i {};
	ListNode* r_list = new ListNode;	
	std::forward_list<ListNode*> f_list;
	std::vector<int> arr(1000000);	
	size_t size_list = f_list.max_size();		
	for (int i = 0; i < size_list; ++i) {
		for (int j = 1; j < size_list; ++j) {
			f_list.push_front(merge_k(vec[i], vec[j]));
		}
	}
}

int main(int argc, char* argv[]) {
	std::vector<int> v {-1};
	auto res = binary_search(v, 2);
	std::cout << "Result Binary Search = " << res << '\n';	
	std::vector<int> arr {1 , 2, 4, 6, 7};
	std::cout << "Index array = " << getIndexArray(arr, 1) << '\n';

	auto list_a = new LinkedList;
	auto list_b = new LinkedList;
	auto list_c = new LinkedList;
	auto list_d = new LinkedList;
	LOG_DURATION("main")
	for (int i = 0; i < 10; ++i) {
		list_a->push_front(i);
	}	
	for (int i = 10; i < 20; ++i) {
		list_b->push_front(i);
	}
	for (int i = 0; i < 10; ++i) {
		list_c->push_front(i);
	}	
	for (int i = 10; i < 20; ++i) {
		list_d->push_front(i);
	}

	auto l1 = LinkedList::get_list(list_a);
	auto l2 = LinkedList::get_list(list_b);
	auto l3 = LinkedList::get_list(list_c);
	auto l4 = LinkedList::get_list(list_d);


	std::vector<ListNode*> vec_lists {l1, l2, l3, l4, {}, {}, {}};
	auto result_mK = modern_mergeK_lists(vec_lists);

	return 0;
}




