#include<iostream>
#include "Static.h";

using namespace std;

static int guess = 2; //if file is imported into another cpp file, this variables name will only work with code within this file, the variable name can be reused 

void cumulative(int N) {
	for (int i = 1; i < N; i++)
	{
		static int sum = 0;  //initialization is only triggered once (at the start) because it is a static variable
		sum += i;
	}
}

//Equivalent without static keyword
void cumulative2(int N) {
	int sum = 0;
	for (int i = 1; i < N; i++)
	{
		sum += i;
	}
}

int main() {
	guess++;
	Static test1("lol");
	Static test2("ok");
	cout << test1 << test2;
	cout << Static::randomAsInstance(); //Static Members of a class (both functions and variables) must be accessed using the scope resolution operator on the class itself.
	//Static::instances		//this is because all static members exists outisde of the class instances. In other words, Only once instance exists and is shared across all instances of the class.
}
