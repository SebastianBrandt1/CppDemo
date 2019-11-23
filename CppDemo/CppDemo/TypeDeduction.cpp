#include "TypeDeduction.h"
#include <iostream>

struct MyInt {
	MyInt(int i) :i(i) {}
	MyInt() :i(0) {}
	int i;
};

class Object {
public:
	Object() = default;
};
int TypeDeduction::Run() {
	MyInt myInt(2011);
	MyInt myInt2();

	std::cout << myInt.i << std::endl;
	//std::cout << myInt2.i << std::endl;

	auto a = 1;
	auto b = { 2 };
	auto c{ 3 };
	//auto d{ 1,2 };
	auto e = { 6, 7};
	auto d = int{ 1 };
	auto x(12);
	int z(12);
	int y(z);
	Object t();
	return 0;
};
