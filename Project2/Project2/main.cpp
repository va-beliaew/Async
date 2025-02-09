#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>


struct func {
	std::vector<int> v;
	void operator() (int& i) {
	 i *= 2;
	}
};

void twin(std::vector<int>::iterator itb, std::vector<int>::iterator ite, func& f) {
	if ((ite - itb) <= 200) {
		std::for_each(itb, ite, f);
	}
	else {
		std::vector<int>::iterator ith = itb + ((ite-itb)/2);
		std::future<void> ft1 = std::async (twin, itb, ith, std::ref(f));
		std::future<void> ft2 = std::async (twin, ith, ite, std::ref(f));
		ft1.get();
		ft2.get();
		}
	return;
	}


int main() {
	func f;
	int n = 1000;
	for (int i = 0; i < n; ++i) {
		f.v.push_back(std::rand()%100);
	}
	for (int& b : f.v) {
		std::cout << b << ' ';
	}
	std::cout << std::endl;
	twin(f.v.begin(), f.v.end(), f);
	for (int& b : f.v) {
		std::cout << b << ' ';
	}


	return 0;
}