#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

int main() {
	int n = 100;
	vector<bool> isprime = vector<bool>(n);

	#pragma omp parallel for
	for (int i = 1; i < n; i++)
		isprime[i] = true;

	for (int i = 2; i < sqrt(n); i++) {
		if (isprime[i]) {
			#pragma omp parallel for
			for (int j = 2; j < n / i; j++) //original termination condition: j*i < n, the local variable in the for loop must be isolated and the right hand side of the expression has to be constant
				isprime[i * j] = false;
		}
	}

	cout << "starting print" << endl;
	std::cout << std::boolalpha;
	for (int l = 0; l < n; l++)
		cout << isprime[l]<< " " << l <<endl;
}