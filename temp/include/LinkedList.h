#pragma once

#include <iostream>
#include <vector>
#include <cassert>
/* Merge Sorted Lists */

class ListNode {
public:
    int val;
    ListNode* next{ nullptr };
    ListNode()
            :val(0) { }
    explicit ListNode(int x)
            :val(x) { }
    ListNode(int x, ListNode* next_)
            :val(x), next(next_) { }
};
class LinkedList {
public:
    LinkedList() = default;
    ~LinkedList() {
        delete head;
        std::cout << "~LinkedList()" << '\n';
    }
	ListNode* mergeKLists(std::vector<ListNode*>& lists);
    void push_front(int value);
    void pop();
    void delete_front();
    void push_back(int value);
    void merge_sort(ListNode** ref);
    ListNode* sorted_merge(ListNode* left, ListNode* right);
	ListNode* test_merge(ListNode* a, ListNode* b);
	[[nodiscard]] static ListNode* get_list(const LinkedList* l) {
		return l->head;
	}
    void sort();
    int length();
    void print_list() const;

private:
    ListNode* head;

    void front_back_split(ListNode** front, ListNode** back);

};


