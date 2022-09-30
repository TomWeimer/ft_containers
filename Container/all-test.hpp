#ifndef ALL_TEST_HPP
#define ALL_TEST_HPP
#include "map_test.hpp"
#include "vector_test.hpp"
#include "stack_test.hpp"
template<class T>
void launchTest(int mode)
{
	typedef T TestType;
	{
		TestType	Test;
		if (mode == STD_ARG)
			Test.launch_std_tests();
		else if (mode == FT_ARG)
			Test.launch_ft_tests();
	}
}


template<class T>
void compareTest(std::string name)
{
	typedef T TestType;
	{
		TestType	Test;
		
		Test.compareTest();
		std::cout << " " << name << std::endl;
	}
}

#endif