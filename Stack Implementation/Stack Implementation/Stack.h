#pragma once

#include <iostream>
#include <vector>

/*You have to have your template definitions available at the calling site. That means no .cpp files.
The reason is templates cannot be compiled. Think of functions as cookies, and the compiler is an oven.
*/

/*
Unlike Java, in C++ you cannot use the dot operator on classes, you need use the scope resolution operator (i.e. ::)
to get things from within the class scope (for example the size static variable),
so replace return K.size with return K::size
*/
template <class T>
class Stack {
private:
	std::vector<T> arr;

public:
	void push(T const&);
};

template <class T>
void Stack<T>::push(T const&)
{
	arr.push_back(T);
}