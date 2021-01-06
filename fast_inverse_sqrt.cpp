#include <iostream>
#include <cstdint>
#include <bit>

using namespace std;

float quicksqrt(float num) {
	float const x2 = num * 0.5F;
	float const threehalfs = 1.5f;
	auto i = std::_Bit_cast<std::uint32_t>(num); //reinterprets the binary representation of a variable from one type to another. The data itself is not changed.
	i = 0x5f3759df - (i >> 1);
	num = std::_Bit_cast<float>(i);
	num *= threehalfs - (x2 * num * num);
	return num;
}

int main() { //Inspired by Quake III
	float test1 = 123151;
	cout << 1 / sqrt(test1) << " " << quicksqrt(test1);
}
