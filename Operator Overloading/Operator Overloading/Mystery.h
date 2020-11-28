#pragma once
#include <string>

// Class to show off features and uses of operator overloading
class Mystery
{
	public:
		Mystery() = default;

		//Copy constructor
		Mystery(const Mystery& m);

		//Move constructor
		Mystery(Mystery&& m) noexcept;

		//Operator Overload main use cases:

			// Copy assignment:
			// Take a const-reference to the right-hand side of the assignment, we dont want to modify it.
			// Check for self - assignment, by comparing the pointers(this to & rhs).
			// Return a non-const reference to the left-hand side, to enable operator chaining: return *this;
			// a = b = c = d => a = (b = (c = d)) 
	    //non-const ref        const reference
			Mystery& operator=(const Mystery& m);

			//Move assignment:
			Mystery& operator=(Mystery&& m) noexcept;


			//By overloading standard operators on a class, you can exploit the intuition of the users 
			//of that class. This lets users program in the language of the problem domain rather than 
			//in the language of the machine.


			//3 main Methods to overload Operators:

			//METHOD 1: Friend Member Function, access to all members of the class
			// Left operand is 'os'; right is 'm'.
			friend std::ostream& operator<<(std::ostream& os, const Mystery& m);


			//'this' keyword is an implit parameter in all member functions of a class (non-static), so all member 
			//functions have access to the 'this' keyword. (Constructors utilize this feature heavily).
			//if a member function does not use any member variables or the 'this' keyword, it should be marked
			//as static for compiler efficiency (to prevent implicit 'this' parameter passing)

			//METHOD 2: Member Function, all access to members + implicit 'this' parameter 
			// Left operand is 'this'; right is 'm'.
			double operator+(const Mystery& m) const;

			//Stream extraction:  std::cin >> Mystery
			friend std::istream& operator>>(std::istream& is, Mystery& m);

			//can use istringstream to pipe data from text files or variables into the operator;
			// std::istringstream ss(randomstring); ss >> Mystery

			//Functional object operator: 
			// Used for stateful functions & Passable as arguments and Template instances because it is a class
			
			//Mystery Obj;
			//int ans = Obj(2, 4, 5);
			int operator()(int x, int y, int z);

			//show std::move usecases: efficient swap and memory allocation in data structures
			void swap(Mystery& x, Mystery& y);

			void efficientSwap(Mystery& x, Mystery& y);

			void dataManagement();

			//using static-cast, which is the main logic that std::move uses.
			Mystery&& stdMoveImplementation(Mystery & x);


	private:
		double* offset;
};

//Every function that is not a member function of ANY class is a free function.

//METHOD 3: Free Function, access to only public members of the class
//Stream insertion:
std::ostream& operator<<(std::ostream& os, const Mystery& m);

