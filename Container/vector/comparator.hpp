#ifndef VECTOR_COMPARATOR_HPP
#define VECTOR_COMPARATOR_HPP
#include "../../TestTemplate/TestBase.hpp"

class VectorComparator : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		VectorComparator();
		VectorComparator(const VectorComparator& origin);
		VectorComparator& operator=(const VectorComparator& origin);
		~VectorComparator();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_vector_content(U vector_type);
};


VectorComparator::VectorComparator()
	: TestBase("comparator.log"){}


VectorComparator::VectorComparator(const VectorComparator& origin)
	: TestBase(origin) {}


VectorComparator::~VectorComparator() {}


VectorComparator& VectorComparator::operator=(const VectorComparator& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& VectorComparator::testInstruction(int namespaces)
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
void VectorComparator::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type type;

	container_type container_test;
	container_type empty_container;
	container_type normal_container(1, this->get_single<type>());
	container_type multiple_container(this->get_multiple<type>(), this->get_multiple<type>() + 10);

	this->timer.start();
	result << "return value: " << (container_test == empty_container) << std::endl;
	this->timer.stop();
	result << "empty assignement:" << std::endl;
	result << "content: " << show_vector_content(container_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;

	this->timer.start();
	result << "return value: " << (container_test != empty_container) << std::endl;
	this->timer.stop();
	result << "empty assignement:" << std::endl;
	result << "content: " << show_vector_content(container_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;
	

	this->timer.start();
	result << "return value: " << (container_test > normal_container) << std::endl;
	this->timer.stop();
	result << "normal assignement:" << std::endl;
	result << "content: " << show_vector_content(container_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;

	this->timer.start();
	result << "return value: " << (container_test >= multiple_container) << std::endl;
	this->timer.stop();
	result << "multiple assignement:" << std::endl;
	result << "content: " << show_vector_content(container_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;


	this->timer.start();
	result << "return value: " << (container_test < multiple_container) << std::endl;
	this->timer.stop();
	result << "multiple assignement:" << std::endl;
	result << "content: " << show_vector_content(container_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;

	this->timer.start();
	result << "return value: " << (container_test <= normal_container) << std::endl;
	this->timer.stop();
	result << "normal assignement:" << std::endl;
	result << "content: " << show_vector_content(container_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;
}


template<class U>
std::string VectorComparator::show_vector_content(U vector_type)
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