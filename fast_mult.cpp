#include <cmath>

// Fast multiplication algorithm - recursive implementation. Optimal for big integers, suboptimal for small to mid range integers.
int karatsuba(int x, int y) {
	if (x <= 10) {
		return x * y;
	}

	int n = (x == 0) ? 0: log10(x)+1; //returns the size of the number

	int p = pow(10, n / 2);

	int x1 = x / p;
	int y1 = y / p;

	int x2 = x % p;
	int y2 = y % p;
	
	int one = karatsuba(x1, y1);
	int three = karatsuba(x2, y2);
	int two = (karatsuba(x1 + x2, y1 + y2) - one - three);

	return one * pow(10 , n) +  two * p + three;

}