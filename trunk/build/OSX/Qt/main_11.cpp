#include <iostream>
#include <cstdlib>
#include <vector>

#define UNUSED(X)  ((void)X)

template<typename T>
T adder(T v)
{
	return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args)
{
	return first + adder(args...);
}

template<>
float adder<float, float, float>(float f1, float f2, float f3)
{
	std::cout << "adding " << f1 << ", " << f1 << ", " << f3 << std::endl;
	return f1 + f2 + f3;
}

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	std::cout << "nullptr: " << (long)nullptr << std::endl;
	
	std::vector<int> vec;
	vec.push_back(3);
	vec.push_back(42);
	for (auto it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << std::endl;
	
	long sum = adder(1, 2, 3, 8, 7);
	std::string s1 = "x", s2 = "aa", s3 = "bb", s4 = "yy";
	std::string ssum = adder(s1, s2, s3, s4);
	
	std::cout << "sum: " << sum << std::endl;
	std::cout << "string sum: " << ssum << std::endl;
	float res = adder(1.f, 2.f, 3.5f);
	std::cout << "float sum: " << res << std::endl;
	
	std::cout << "Hello world !" << std::endl;
	
	return EXIT_SUCCESS;
}
