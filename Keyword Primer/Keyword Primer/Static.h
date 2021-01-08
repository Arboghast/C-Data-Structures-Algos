#pragma once
#include<string>
#include<ostream>
#include<vector>

class Static  //const keyword is useful for minor compiler optimizations => minor performance improvements. It is mostly used to limit human error and enforce documentation/strict governing rules	
{			  //static keyword enables unique behavior for classes & functions and helps with variable organization.
	private:
		static int instances;
		const int id;
		mutable float timestamp;  //Data members declared as mutable can be modified even, despite being a part of an object which has been declared as const. 
								  //Implies that const objects also have access to mutable members variables and functions, and those can be altered.
		std::string name;
	public:
		explicit Static(std::string name) :id(instances++), name(name) { } //explicit used for single argument constructors to optimize performance
		
		static int randomAsInstance() {
			return rand() - instances;
		}
		
		/*	 a class instance === an object
			 If you have a const object, you don't want to call member methods that can change the object, so you need a way of letting the compiler know which methods can be safely called. 
			 These methods are called "const functions", and are the only functions that can be called on a const object. Note, by the way, that only member methods make sense as const methods. 
			 Remember that in C++, every method of an object receives an implicit this pointer to the object; const methods effectively receive a const this pointer.

			 You can also infer by this that only non-const member functions can only be called by non-const objects
		*/
		int mystery() const {
			return (int)name[0];
		}

		friend std::ostream& operator<<(std::ostream& os, Static inst) {
			os << inst.id << " " << std::endl;
			return os;
		}
};
int Static::instances = 0; //initialize static variable outside of the class

/*
	static member variables are not associated with each object of the class. It is shared by all objects. 
	When you initialize it in a constructor (or anywhere within the class), it implies that you are trying to associate the static variable with a particular instance of a class. 
	Since this is contradictory to what we hope to achieve, it is not allowed.
*/

/*
	const means read-only, not constant. If you have a pointer-to-const then other parts of the program may change the value while you're not looking.
	In most context, const applies to a view of the variable and not the variable itself, someone else can have a non-const view of the same variable, 
	and the compiler will be quite silent when they modify it.
*/

//function signature deciphering: http://c-faq.com/decl/spiral.anderson.html - Essentially parse the signature from right to left - it helps tremendously
const int* const mystery2(const int* const&);  // a function- mystery2, which takes a reference to a const pointer which points to a const int, and returns a const pointer to a const int.

//https://www.cprogramming.com/tutorial/const_correctness.html#:~:text=The%20const%20keyword%20allows%20you,pointed%20to%20(or%20referenced). For const correctness
int const x = 5; //is equivalent to:
const int y = 5;


//A static const is set during startup initialization and remains unchanged for the rest of the program
static const int w = 0;

const int* pointer_x; //pointer to a const int, unchangable integer value
int* const pointer_y; //constant pointer to an integer, the pointer itself is unchangable
const int* const pointer_z; //constant pointer to a const int, unchangable pointer to an unchangable integer

const char* strx = "abc";

char* stry = const_cast<char*>(strx); //casting a const variable to a non-const variable - can also cast from non-const to const

/*
	Since iterators can also be used to modify the underlying collection, when an STL collection is declared const, then any iterators used over the collection must be const iterators. 
	They're just like normal iterators, except that they cannot be used to modify the underlying data.
*/
void mystery3() {
	std::vector<int> vec{ 1,2,3 };
	for (std::vector<int>::const_iterator itr = vec.begin(), end = vec.end(); itr != end; ++itr) {
		static int sum = 0;
		sum += *itr;
	}
}

/*
	Don't look at const as a means of gaining efficiency so much as a way to document your code and ensure that some things cannot change. 
	Remember that const-ness propagates throughout your program, so you must use const functions, const references, and const iterators 
	to ensure that it would never be possible to modify data that was declared const.
*/

//For a function to be fit for use in constant expressions, it must be explicitly declared constexpr
constexpr float sqr(int arg) {  //forces evaluation of this function to be done during compile time. Helpful for performance improvements but is often overused and is used in a vague context. 
	return arg * arg;
}

/* The keyword indicates that the function is a constant expression
	A constant expression is an expression that contains only constants. A constant expression can be evaluated during compilation rather than at run time, and can be used in any place 
	that a constant can occur. This implies that the function can be simplified down to constants as a function of its parameters. It then does this work during compilation instead of at runtime.
*/