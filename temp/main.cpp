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

void print(const char* array) {
	std::copy(array, array+sizeof(array), std::ostream_iterator<char>(std::cout << " "));
}

class Point {
private:
	int x;
	int y;
	Point(int x_, int y_)
			:x(x_), y(y_) { }

public:
	struct Carthesian;
	struct Polar;
	void Add(int x_, int y_) {
		x += x_;
		y += y_;
	}
	void Print() const {
		std::cout << "X= " << x << " "
				  << "Y= " << y << '\n';
	}
};

struct Point::Carthesian : public Point {
	Carthesian(int x, int y)
			:Point(x, y) { }
};

int main(int argc, char* argv[]) {
	/* Point* point = new Point::Carthesian(1, 2);
	 point->Add(2, 2);
	 point->Print(); */
	/********************************************************************************
	 * ******************************************************************************
	 */
	// std::cout << "Test remove O(1)" << '\n';
	// std::vector<int> vec {1, 50, 100, 200};
	// for (auto&& i : vec) {
	// 	std::cout << i << ' ';
	// }
	// std::cout << '\n';
	// std::vector<int>::iterator it;
	// it = std::lower_bound(std::begin(vec), std::end(vec), 100);
	// *it = std::move(vec.back());
	// vec.pop_back();
	// for (auto&& i : vec) {
	// 	std::cout << i << ' ';
	// }
	// std::cout << '\n';


	std::forward_list<int> f_list;
	auto list = std::make_unique<LinkedList>();
	auto list2 = std::make_unique<LinkedList>();
	auto list3 = std::make_unique<LinkedList>();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 20);

	// {
	// 	list->push_front(4);
	// 	list->push_front(7);
	// 	list->push_front(9);
	// 	list->push_front(12);
	// 	list->push_front(18);
	// }
	// {
	// 	list2->push_front(4);
	// 	list2->push_front(11);
	// 	list2->push_front(12);
	// }
	// {
	// 	list3->push_front(14);
	// 	list3->push_front(19);
	// }
	// for (size_t i = 0; i < 5; ++i) {
	// 	list->push_front(distrib(gen));
	// }
	// for (size_t i = 0; i < 3; ++i) {
	// 	list2->push_front(distrib(gen));
	// }
	// for (size_t i = 0; i < 2; ++i) {
	// 	list3->push_front(distrib(gen));
	// }
	// {
	// 	std::cout << "List1: " << '\n';
	// 	list->print_list();
	// 	list->sort();
	// 	list->print_list();
	// 	std::cout << "List2: " << '\n';
	// 	list2->print_list();
	// 	list2->sort();
	// 	list2->print_list();
	// 	std::cout << "List3: " << '\n';
	// 	list3->print_list();
	// 	list3->sort();
	// 	list3->print_list();
	// }
	{
		// ListNode* first = LinkedList::get_list(list.get());
		// ListNode* second = LinkedList::get_list(list2.get());
		// ListNode* third = LinkedList::get_list(list3.get());
	
		// std::vector<ListNode*> lists{ first, second, third};
		std::vector<ListNode*> lists{{}};

		std::cout << "Merge N sorted lists: " << '\n';
		auto r = std::make_unique<LinkedList>();
		auto res_merge = r->mergeKLists(lists);
		while (res_merge->next) {
			std::cout << res_merge->val << "->";
			res_merge = res_merge->next;
		}
	
		std::cout << res_merge->val << '\n';
	}
	/*std::cout << "test_merge: " << '\n';
	auto result_list = std::make_unique<LinkedList>();
	auto res = result_list->test_merge(first, second);
	while (res->next) {
		std::cout << res->val << "->";
		res = res->next;
	}
	std::cout << res->val << std::endl;*/
//	result_list->print_list();
	/********************************************************************************
	 * ******************************************************************************
	 */
	/*constexpr int SIZE = 10;
	int* array = new int[SIZE];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 20);*/


	return 0;
}




