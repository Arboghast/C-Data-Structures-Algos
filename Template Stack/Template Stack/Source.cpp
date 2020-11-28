#include "stack.h"
#include <iostream>

using namespace std;

//Template Functions - same core funcionality as template classes
template<class T>
bool mysteryFunction(T first, T second) {
	return first == second;
}


int main() {
	/*
	* https://docs.microsoft.com/en-us/cpp/cpp/explicit-instantiation?view=vs-2019
	* 
	  Explicit Instantiation: (an extern template) skips the implicit instantiation step, basically a pointer
	  to a defined intstance of a template class from other files in the program.

	  This can be used to reduce compilation times by explicitly declaring a template 
	  instantiation in all but one of the source files using it, and implicitly defining 
	  it in the remaining file, assuming they all use the same wrapper combination. Only one instance of each
	  wrapper combination needs to be implicitly instantiated, the rest can refer to that instantiation using extern.
	*/
	/*
	  Implicit Instantiation: The compiler does not generate definitions for:
	  functions, nonvirtual member functions, class or member class that does 
	  not require instantiation.
	*/
	Stack<int,10> one; //generates class Stack<class,int> with constructors and destructors only.
	one.print();  //additional member functions are generated AS NEEDED. Stack<class,int>::print() is now defined.

	extern Stack<int,5> stack;
	stack.push(2);

	int x = 1;
	int y = 2;
	cout << mysteryFunction(x, y) << endl;
	return 0;
}