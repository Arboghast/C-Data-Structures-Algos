#pragma once

//Class Templates
#include<iostream>

//Multi-input Wrapper
//Template parameters can have default values and be reused within itself: template<class T, T* pT> class X1
template <class T, int N>
class Stack {
	private:
		//Each template class generated has its own copies of any static members.
		//static int x = 0;
		T arr[N];
		int index = 0;

	public:
		void push(const T& item);
		void print();
};

/* Each template function or member function of a template class generated has it's own copy of its static variable.
template <class T>
void f(T t)
{
	static T s  = 0;
	s = t ;
	cout << "s = " << s << endl ;
}
*/



//(Partial) Template Specialization
template <int N>
class Stack<char,N> { //specifically for chars
	private:
		char arr[26];
		int index = 0;
	public:
		void increment();
};

/*
Choose T x when you want to work with copies.
Choose T &x when you want to work with original items and may modify them.
Choose T const &x when you want to work with original items and will not modify them.
Choose T &&x when you don't want to make a needless copy, and don't care if you modify it or not,.
*/

template <int N>
void Stack<char, N>::increment() {
	for (char &c : arr) {
		c++;
	}
}

template <class T, int N>
void Stack<T, N>::print() {
	for (T const &x : arr)
	{
		std::cout << x << std::endl;
	}
}

template <class T, int N>
void Stack<T, N>::push(const T& item)
{
	if (index < N) {
		arr[index++] = item;
	}
}

//Explicit Template Instantiation
template Stack<int, 10>;