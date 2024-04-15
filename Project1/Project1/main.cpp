#include <iostream>
#include <thread>
#include <future>


int find_min (int* a, int n, int t) {
	int num = t;
	int tmp = a[t];
	for (int i = t; i < n; ++i) {
		if (a[i] <= tmp) {
			tmp = a[i];
			num = i;
		}
	}
	return num;
}

int main() {
	const int n = 50;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) {
		arr[i] = std::rand()%100;
	}
	for (int i = 0; i < n; ++i) {
		int tmp = 0;
		std::future<int> ft = std::async(find_min, arr, n, i);
		tmp = arr[i];
		int t = ft.get();
		arr[i] = arr[t];
		arr[t] = tmp;
	}
	for (int i = 0; i < n; ++i) {
		std::cout << arr[i] << ' ';
	}

	return 0;
}