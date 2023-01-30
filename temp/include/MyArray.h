#pragma once

#include <iostream>

template <class I>
class MyArray {
public:
	explicit MyArray(I* array, size_t size) : m_array(array), m_size(size) {}
	~MyArray()  {
		std::cout << "~MyArray()";
	}
	[[nodiscard]] int get_size() const { return m_size; }
//	void merge(I* array_2, size_t size);
	int* get_itr(int index);
	void merge_sort(I* arr, int l , int r);
	void merge(I* arr, int l , int m, int r);
private:
	I* m_array;
	size_t m_size;
};
template<class I>
void MyArray<I>::merge(I* arr, int left, int m, int right) {
	/*int i {};
	int j {};
	auto aux = new int[r];
	for (i = m + l; i > l; --i) {
		aux[i - l] = arr[i - l];
	}
	for (j = m; j < r; ++j) {
		aux[r + m - j] = arr[j + l];
	}
	for (int k = l; k <= r; ++k) {
		if (aux[j] < aux[i]) {
			arr[k] = aux[j--];
		}
		else {
			arr[k] = aux[i++];
		}
	}
	std::cout << "Array after sort: " << std::endl;
	for (int v = 0; v < sizeof(aux); ++v) {
		std::cout << arr[v] << ' ';
	}
	std::cout << std::endl;
	delete [] aux;*/
	int l = left;
	int r = m + 1;
	int* tmp_arr = new int[right];
	int step {0};
	while (l <= m && r <= right) {
		if (arr[l]<arr[r]) {
			tmp_arr[step++] = arr[l++];
		}
		else {
			tmp_arr[step++] = arr[r++];
		}
	}
	while (r<=right) {
		tmp_arr[step++] = arr[r++];
	}
	while (l<=m) {
		tmp_arr[step++] = arr[l++];
	}
	for (int k = 0; k<right-left+1; ++k) {
		arr[left+k] = tmp_arr[k];
		std::cout << arr[k] << ' ';
	}
	std::cout << '\n';
	delete [] tmp_arr;
}
template<class I>
void MyArray<I>::merge_sort(I* arr, int left, int right) {
	if (right <= left) {
		return;
	}
	int mid = (right + left) / 2;
	test_recursion(arr, left, mid);
	test_recursion(arr, mid + 1, right);
	test_merge(arr, left, mid, right);
}

template<class I>
int* MyArray<I>::get_itr(int index) {
	return &m_array[index];
}

template<typename T>
std::ostream& operator<<(std::ostream& os, MyArray<T>* my_array) {
	auto size = my_array->get_size();
	for (int i = 0; i < size; ++i) {
		os << *my_array->get_itr(i)  << ' ';
	}
	os << '\n';
	return os;
}

/*template<class I>
void MyArray<I>::merge(I* array_2, size_t size) {
	int* new_arr = new int(static_cast<int>(size));
	for (int i = 0, j = 0, k = 0; k < m_size + size; ++k) {
		if (i == m_size) {
			new_arr[k] == array_2[j++];
			continue;
		}
		if (j == size) {
			new_arr[k] = m_array[i++];
			continue;
		}
//		new_arr[k] = (m_array[i] < array_2[j]) ? m_array[i++] : array_2[j++];
		if (m_array[i] < array_2[j]) {
			new_arr[k] = m_array[i++];
		}
		else {
			new_arr[k] = array_2[j++];
		}
	}
	for (int i = 0; i < size + m_size; ++i) {
		std::cout << new_arr[i] << ' ';
	}
	std::cout << std::endl;

	delete new_arr;
}*/











