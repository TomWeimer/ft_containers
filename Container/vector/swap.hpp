#ifndef VECTOR_SWAP_HPP
#define VECTOR_SWAP_HPP

#include "../../TestTemplate/TestBase.hpp"

class VectorSwap : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		VectorSwap();
		VectorSwap(const VectorSwap& origin);
		VectorSwap& operator=(const VectorSwap& origin);
		~VectorSwap();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_vector_content(U vector_type);
};


VectorSwap::VectorSwap()
	: TestBase("swap.log"){}


VectorSwap::VectorSwap(const VectorSwap& origin)
	: TestBase(origin) {}


VectorSwap::~VectorSwap() {}


VectorSwap& VectorSwap::operator=(const VectorSwap& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& VectorSwap::testInstruction(int namespaces)
{
	result.str("");
	if (namespaces == STD_ARG)
	{
		this->logfile.set_path("./logs/vector/vector_std/");
		this->logfile.clear();
		execute_test<std::vector<int> >();
		execute_test<std::vector<std::string> >();
	}
	else if (namespaces == FT_ARG)
	{
		this->logfile.set_path("./logs/vector/my_vector/");
		this->logfile.clear();
		execute_test<ft::vector<int> >();
		execute_test<ft::vector<std::string> >();
	}
	return (result);
}




template<class U>
void VectorSwap::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type type;

	container_type container1(this->get_multiple<type>(), this->get_multiple<type>() + 10);
	container_type container2;
	result << "before swap:" << std::endl;
	result << "content container1:	" << this->show_vector_content(container1) << std::endl;
	result << "content container2:	" << this->show_vector_content(container2) << std::endl;
	result << "swap: " << std::endl;
	this->timer.start();
	container1.swap(container2);
	this->timer.stop();
	result << "after swap:" << std::endl;
	result << "content container1:	" << this->show_vector_content(container1) << std::endl;
	result << "content container2:	" << this->show_vector_content(container2) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string VectorSwap::show_vector_content(U vector_type)
{
	typedef U container_type;
	typedef typename container_type::iterator iterator;

	std::stringstream out;

	iterator first = vector_type.begin();
	iterator last = vector_type.end();
	for(; first != last; first++)
	{
		out << *first;
		if (first + 1 != last)
			out << ", ";
	}
	return (out.str());
}
#endif