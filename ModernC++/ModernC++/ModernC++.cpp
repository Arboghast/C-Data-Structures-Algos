#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

//Lambda Functions === Anonymous Functions == Functional Objects
//Lambda functions are most useful in things like callback functions, that is, functions that take other functions 
//as their arguments. Also temporary functions

//It turns out that the way lambdas are implemented is by creating a small class; this class overloads the 
//operator(), so that it acts just like a function.A lambda function is an instance of this class; when the 
//class is constructed, any variables in the surrounding enviroment are passed into the constructor of the 
//lambda function classand saved as member variables.

//They are also good for condensing code, making it less verbose, while at the same time improving readability
//depending on how you write the lambda function

//improve code organization, logic that is relevant to certain parts of the code are kept together, instead
//of being defined in a function a few hundred lines above or below where it is used
int main()
{
    //Lambdas enhance the capabilities of various standard library algorithms
    std::vector<int> sequence{ 2,3,4,5,6,7,8,9,1 };
    int counter = 0;

    //overriding the default comparision operator and adding some additional code
    std::sort(sequence.begin(), sequence.end(), [&counter](int left, int right) {
        counter++;
        return left > right;
    });

    std::cout << "number of comparisons: " << counter << std::endl << std::endl;

    //Components of a Lambda Funtion:
    // [capture list] (function paramters) { function body }
    //function parameters and function body are the same as normal functions

    std::set<int> set {7, 4, 2};
    std::vector<int> nums { 1,2,3,4,5,6,7,8,9 };


    //erase( iterator first, iterator last ); === Removes the elements in the range [first, last).

    //remove_if( iterator first, iterator last, booleanFunction p ) === Removes all elements for which the 
    //boolean function or predicate p returns true. Returns an iterator to the element that follows the 
    //last element not removed.

    //Strategy: Removing is done by shifting (by means of move assignment) the elements in the range in 
    //such a way that the elements that are not to be removed appear in the beginning of the range. 
    //Then we call the erase operator to truncate the vector to its new size in constant time.
    nums.erase(std::remove_if(nums.begin(), nums.end(), [&set](int num) {
                return set.find(num) != set.end();
    }), nums.end());

    //you can also set lambda functions as variables for easy organization (instead of inlining like the 
    //previous example) and use auto to bypass need for messy functional pointer type referencing.

    //type deduced by compiler.
    //(#include <functional> )
    //Original method: std::function<double(int, bool)> f = [](int a, bool b) -> double { ... }; 
    auto print = [](auto& thing) {
        std::cout << thing << std::endl;
    };

    //for_each( iterator first, iterator last, UnaryFunction f) === applies the function over the range of elements 
    //[first,last]
    std::for_each(nums.begin(), nums.end(), print);

    std::cout << std::endl << std::endl;


    //If a variable is captured by value (as opposed to captured by ref), 
    //then the captured value is the value at the point the lambda is defined, not the point it is used.


    //If a lambda is marked mutable (e.g. []() mutable { ... }) it is allowed 
    //to mutate the values that have been captured by value.

    // it is possible to execute a lambda immediately upon definition:
    [&]() {  }(); // immediately executed lambda expression (this lambda does nothing)

    //Lambda expressions also let you create named nested functions, 
    //which can be a convenient way of avoiding duplicate logic.

    auto algorithm = [&](double x, double m, double b) -> double
    {
        return m * x + b;
    };

    int a = algorithm(1, 2, 3), b = algorithm(4, 5, 6);

    //Capture Syntax:
    //Comma Separated List, used to import variables used wihtin functioon that are not passed as parameters
    // captured variables === member variables (in the functional object analogy)

    //    []	Capture nothing
    //    [&]	Capture any referenced variable by reference (lvalues of vars will be copied to the function object)
    //    [=]	Capture any referenced variable by making a copy (variables will be copied to the function object)
    //    [=, &foo]	Capture any referenced variable by making a copy, but capture variable foo by reference
    //    [bar]	Capture bar by making a copy; don't copy anything else
    //    [this]	Capture the this pointer of the enclosing class (lambdas === funcional object classes)

    // note: this pointer can also be captured using [this], [=], and [&]

    //excersie using std::transform, a powerful function

    std::vector<int> red{ 9,2,8,3,7,4,6,5,1 };
    std::vector<int> blue;
    int offset = 4;

    blue.resize(red.size());

    std::transform(red.begin(), red.end(), blue.begin(), [=](int x) {
        return x + offset;
    });

    std::transform(red.begin(), red.end(), blue.begin(), red.begin(), [](int x, int y) {
        return (x > y) ? x : y;
    });

    std::for_each(red.begin(), red.end(), [](int x) {
        std::cout << x << std::endl;
    });
}
