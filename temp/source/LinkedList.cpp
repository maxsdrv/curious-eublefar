#include "LinkedList.h"

#include <list>
#include <memory>
#include <algorithm>

void LinkedList::push_front(int value) {
	auto new_node = new ListNode(value);
	if (head==nullptr) {
		head = new_node;
		return;
	}
	ListNode* temp = head;
	while (temp->next) {
		temp = temp->next;
	}
	temp->next = new_node;
}
void LinkedList::pop() {
	assert(head!=nullptr);
	ListNode* end = head;
	ListNode* prev{ nullptr };
	while (end->next) {
		prev = end;
		end = end->next;
	}
	prev->next = nullptr;
	delete end;
}
void LinkedList::delete_front() {
	assert(head!=nullptr);
	ListNode* temp = head;
	head = head->next;
	delete temp;
}
void LinkedList::push_back(int value) {
	assert(head!=nullptr);
	auto new_head = new ListNode(value);
	new_head->next = head;
	head = new_head;
}
void LinkedList::print_list() const {
	assert(head!=nullptr);
	ListNode* temp = head;
	while (temp->next) {
		std::cout << temp->val << " -> ";
		temp = temp->next;
	}
	std::cout << temp->val << '\n';
}
void LinkedList::merge_sort(ListNode** ref) {
	if ((*ref)==nullptr || (*ref)->next==nullptr) {
		return;
	}
	ListNode* h = *ref;
	ListNode* slow = *ref;
	ListNode* fast = *ref;
	ListNode* temp = *ref;
	//    front_back_split(&begin, &end);
	//    std::cout << "After split begin and end = " << slow->val << ' ' << fast->val << '\n';
	while (fast!=nullptr && fast->next!=nullptr) {
		temp = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	temp->next = nullptr;
	merge_sort(&h);
	merge_sort(&slow);

	*ref = sorted_merge(h, slow);
}
ListNode* LinkedList::sorted_merge(ListNode* left, ListNode* right) {
	ListNode* result = nullptr;
	if (left==nullptr)
		return right;
	if (right==nullptr)
		return left;

	if (right->val<=left->val) {
		result = right;
		result->next = sorted_merge(right->next, left);
	}
	else {
		result = left;
		result->next = sorted_merge(right, left->next);
	}

	return result;
}
void LinkedList::sort() {
	assert(head || head->next!=nullptr);
	merge_sort(&head);
}
void LinkedList::front_back_split(ListNode** front, ListNode** back) {
	assert(head!=nullptr);

	ListNode* temp = head;
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast!=nullptr && fast->next!=nullptr) {
		temp = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	std::cout << "Slow = " << slow->val << std::endl;
	temp->next = nullptr;
	*front = head;
	*back = slow;
}

int LinkedList::length() {
	int count{};
	while (head!=nullptr) {
		head = head->next;
		++count;
	}
	return count;
}
ListNode* LinkedList::mergeKLists(std::vector<ListNode*>& lists) {
	// auto* new_head = new ListNode;
	auto new_head = std::make_unique<ListNode>();
	auto n = new_head.get();
	int a = 0;
	int b = 1;
	if (lists.empty()) {
		return new_head.get();
	}
	while (true) {
		if (lists[a] == nullptr) {
			while (lists[b] != nullptr) {
				n->next = lists[b];
				n = lists[b];
				lists[b] = lists[b]->next;
			}
			n->next = nullptr;
			n = nullptr;
			lists.push_back(new_head->next);
			lists[a] = std::move(lists.back());
			lists.pop_back();
			if (static_cast<int>(lists.size()) > 2) {
				lists[b] = std::move(lists.back());
				lists.pop_back();
			}
			else {
				lists.pop_back();
			}
			n = new_head.get();
		}

		if (static_cast<int>(lists.size()) == 1) {
			return new_head->next;
		}		

		if(lists[b] == nullptr) {
			while (lists[a] != nullptr) {
				n->next = lists[a];
				n = lists[a];
				lists[a] = lists[a]->next;
			}
			n->next = nullptr;
			n = nullptr;
			lists.push_back(new_head->next);
			lists[a] = std::move(lists.back());
			lists.pop_back();
			if (static_cast<int>(lists.size()) > 2) {
				lists[b] = std::move(lists.back());
				lists.pop_back();
			}
			else {
				lists.pop_back();
			}
			n = new_head.get();
		}
		if (static_cast<int>(lists.size()) == 1) {
			return new_head->next;
		}
		if (lists[a]->val < lists[b]->val) {
			n->next = lists[a];
			n = lists[a];
			lists[a] = lists[a]->next;
		}
		else {
			n->next = lists[b];
			n = lists[b];
			lists[b] = lists[b]->next;		
		}
	}
	return new_head->next;
}
ListNode* LinkedList::test_merge(ListNode* a, ListNode* b) {
	auto* new_head = new ListNode;
	auto* n = new_head;
	while (true) {
		if (a==nullptr && b==nullptr) {
			return new_head->next;
		}
		else if (a==nullptr) {
			n->next = b;
			return new_head->next;
		}
		else if (b==nullptr) {
			n->next = a;
			return new_head->next;
		}
		else {
			if (a->val<b->val) {
				n->next = a;
				n = a;
				a = a->next;
			}
			else {
				n->next = b;
				n = b;
				b = b->next;
			}
		}
	}
}