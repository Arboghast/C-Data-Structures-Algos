#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

void hammingDecode(bitset<16> mat) {
	int sum = 0;
	for (int i = 3; i < 16; i++) {
		if (ceil(log2(i)) != floor(log2(i))) //check if index is a power of two
		{
			sum = mat[i];
		}
	}

	if (sum % 2 == mat[0]) {
		cout << "parity bit check is good" << endl;
	}
	else {
		cout << "bit error in message" << endl;
	}

	bitset<4> error; // bot even right odd - ex: 0110, unique location on matrix

	sum = 0;
	for (int i = 1; i < 16; i += 2) {
		sum += mat[i];
	}

	if (sum % 2 == 0) {
		cout << "odd column parity check is good" << endl;
	}
	else {
		cout << "error bit is in odd column" << endl;
		error[0] = 1;
	}

	sum = 0;
	for (int i = 2; i < 16; i += 4) {
		sum += mat[i] + mat[i + 1];
	}

	if (sum % 2 == 0) {
		cout << "right column parity check is good" << endl;
	}
	else {
		cout << "error bit is in right column" << endl;
		error[1] = 1;
	}

	sum = 0;
	for (int i = 4; i < 16; i += 8) {
		sum += mat[i] + mat[i + 1] + mat[i + 2] + mat[i + 3];
	}

	if (sum % 2 == 0) {
		cout << "even row parity check is good" << endl;
	}
	else {
		cout << "error bit is in even row" << endl;
		error[2] = 1;
	}

	sum = 0;
	for (int i = 8; i < 16; i += 16) {
		sum += mat[i] + mat[i + 1] + mat[i + 2] + mat[i + 3]
			+ mat[i + 4] + mat[i + 5] + mat[i + 6] + mat[i + 7];
	}

	if (sum % 2 == 0) {
		cout << "bottom row parity check is good" << endl;
	}
	else {
		cout << "error bit is in bottom row" << endl;
		error[3] = 1;
	}

	cout << endl << "error is in matrix bit " << error.to_ulong() << " which is a " << mat[error.to_ulong()] << endl;
	mat.flip(error.to_ulong());

	bitset<11> ans;
	int c = 10;
	for (int i = 3; i < 16; i++) {
		if (ceil(log2(i)) != floor(log2(i))) //check if index is a power of two
		{
			ans[c--] =  mat[i];
		}
	}

	cout << endl << "Your original data was " << ans.to_ulong() << endl;
}

//template <size_t len>
void hammingEncode(bitset<11>& bin) {
	bitset<16> matrix;
	matrix[0] = bin.count() % 2; //parity bit

	int w = bin.size()-1; //bitset reads the bits from right to left, we want left to right
	for (int i = 3; i < 16; i++) {
		if( ceil(log2(i)) != floor(log2(i)) ) //check if index is a power of two
		{
			matrix[i] = bin[w--];
		}
	}

	int x = 0;
	for (int i = 1; i < 16; i += 2){
		x += matrix[i];
	}
	matrix[1] = x%2;   // odd column parity check

	int y = 0;
	for (int i = 2; i < 16; i += 4) {
		y += matrix[i] + matrix[i + 1];
	}
	matrix[2] = y%2;  //right column parity check

	int z = 0;
	for (int i = 4; i < 16; i += 8) {
		z += matrix[i] + matrix[i + 1] + matrix[i + 2] + matrix[i + 3];
	}
	matrix[4] = z % 2;  //even row parity check

	int p = 0;
	for (int i = 8; i < 16; i += 16) {
		p += matrix[i] + matrix[i + 1] + matrix[i + 2] + matrix[i + 3]
			+ matrix[i + 4] + matrix[i + 5] + matrix[i + 6] + matrix[i + 7];
	}
	matrix[8] = p % 2;  //bottom row parity check


	//add error
	matrix[11] = 1;

	for (int i = 0; i < 16; i++) {
		if (i != 0 && i % 4 == 0) {
			cout << endl;
		}
		cout << matrix[i];
	}
	cout << endl << endl;

	hammingDecode(matrix);
}



int main() {
	bitset<11> binary(13);
	//cout << binary.to_string()<< endl << binary[0] << endl; 
	hammingEncode(binary);
}

