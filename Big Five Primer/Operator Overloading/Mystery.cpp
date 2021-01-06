#include "Mystery.h"
#include <iomanip>
#include <string>
#include <vector>
#include <iostream>

//Same logic as assignment except no returning
Mystery::Mystery(const Mystery& m)
{
    //self-assignment check is unnecessary because its impossible to occur! the object hasn't been created yet.

    offset = m.offset;   //shallow copy because I'm lazy. Should be a deep copy
}

Mystery::Mystery(Mystery&& m) noexcept
{
    //Deallocation is not necessary because the object is being instantiated for the first time!

    offset = std::move(m.offset);
    m.offset = nullptr;
}

Mystery& Mystery::operator=(const Mystery& m)
{
    // Check for self-assignment!
    if (this != &m) //'&m' returns the memory address, even if the variable is a synonym of another object
    {
        // Deallocate old values, allocate new space, deep-copy values...
        delete offset;
        offset = m.offset; //shallow copy of pointers
    }
    
    return *this; // 'this' is a pointer to the object so '*this' is the object itself. 
    //if the ampersand is left out of the return signature, 'Mystery' instead of 'Mystery&', the compiler will
    //try to make a copy of the object being returned, which is inefficient. The '&' will automatically return 
    //a ref to the object itself
}

Mystery& Mystery::operator=(Mystery&& m) noexcept
{
    //Instead of deep copying the source object(m) into the implicit object, we simply move(steal) 
    //the source object’s resources.
    if (this != &m) {
        // Deallocate old values, relocate values, clean up loose ends/dangling pointers
        delete offset;
        offset = std::move(m.offset); //the compiler treats m as an object reference.In order to relocate it, 
        //you need to tell the compiler to convert it back to a rhs value

        //when used inside the function body, lvalue references or 
        //rvalue references are treated as l-value references because the nature of being a parameter
        //with a named refeerence implies that it is an l-value

        m.offset = nullptr;
    }

    return *this;
}

//std::cout
std::ostream& operator<<(std::ostream& os, const Mystery& m)
{
    //std setprecision to specify the number of decimal places to print out in the console.
    os << std::setprecision(17) << *m.offset << " is the offset!" << '\n';
    return os;
}

//std::cin
std::istream& operator>>(std::istream& is, Mystery& m)
{
    //use 'is.getline(m.somestring, char delim)' to extract text from input stream and store it into a variable;
    std::cout << "please enter the offset value: " << std::endl;
    is >> *(m.offset);

    return is;

}

double Mystery::operator+(const Mystery& m) const
{
    return *(this->offset) + *(m.offset);
}

int Mystery::operator()(int x, int y, int z)
{
    return x + y - z;
}

void Mystery::swap(Mystery& x, Mystery& y)
{
    Mystery temp = x; //copy-constructor
    x = y;   //copy assignment
    y = temp;   //copy assignment
}

void Mystery::efficientSwap(Mystery& x, Mystery& y)
{
    Mystery temp = std::move(x);   //move constructor
    x = std::move(y);    //move assignment
    y = std::move(temp);   //move assignment
}

void Mystery::dataManagement()
{
    std::vector<std::string> vec;
    std::string s = "Hello!";
    vec.push_back(s);   //L-value variation of push_back function invoked, string value is copied

    vec.push_back("hi!");    //R-value variation of push_back function invoked
    vec.push_back( std::move(s) );   //R-value version called, data in string is relocated
    s.empty() == true;
}

Mystery&& Mystery::stdMoveImplementation(Mystery& x)
{
    //static cast used to convert between types, implicitly used behind the scenes in c++ standard library.
    // static_cast<new_type>(input)

    //std::move can be implemented in one line using a static cast 
    // (the std::move function is implemented as a template function for generalization)
    return static_cast<Mystery&&>(x);
}



