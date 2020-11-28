#include <chrono>
#include <iostream>

int main() {
	int test = 1234;
	int test2 = 6789;

	auto t1 = std::chrono::high_resolution_clock::now();
	int res = test * test2;
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << res << " is " << duration << std::endl;

	auto t3 = std::chrono::high_resolution_clock::now();
	int res2 = karatsuba(test, test2);
	auto t4 = std::chrono::high_resolution_clock::now();

	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

	std::cout << res2 << " is " << duration2 << std::endl;
}