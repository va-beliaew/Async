#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>


void twin(std::vector<int>::iterator itb, std::vector<int>::iterator ite, std::vector<int>& v) {
	if ((ite - itb) <= 200) {
		std::for_each(itb, ite, [&v](int& i) -> void {
			i *= 2;
			});
	}
	else {
		std::vector<int>::iterator ith = itb + ((ite-itb)/2);
		std::future<void> ft1 = std::async (twin, itb, ith, std::ref(v));
		std::future<void> ft2 = std::async (twin, ith, ite, std::ref(v));
		ft1.get();
		ft2.get();
		}
	return;
	}


int main() {
	int n = 1000;
	std::vector<int> v;
	for (int i = 0; i < n; ++i) {
		v.push_back(std::rand()%100);
	}
	for (int& b : v) {
		std::cout << b << ' ';
	}
	std::cout << std::endl;
	twin(v.begin(), v.end(), v);
	for (int& b : v) {
		std::cout << b << ' ';
	}


	return 0;
}