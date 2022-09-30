#ifndef VECTOR_CONSTRUCTOR_HPP
#define VECTOR_CONSTRUCTOR_HPP
#include "../../TestTemplate/TestBase.hpp"
#include <list>

class VectorConstructor : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		VectorConstructor();
		VectorConstructor(const VectorConstructor& origin);
		VectorConstructor& operator=(const VectorConstructor& origin);
		~VectorConstructor();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_vector_content(U vector_type);
};


VectorConstructor::VectorConstructor()
	: TestBase("constructor.log"){}


VectorConstructor::VectorConstructor(const VectorConstructor& origin)
	: TestBase(origin) {}


VectorConstructor::~VectorConstructor() {}


VectorConstructor& VectorConstructor::operator=(const VectorConstructor& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& VectorConstructor::testInstruction(int namespaces)
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
void VectorConstructor::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type type;
	
	this->timer.start();
	container_type	default_constructor;
	this->timer.stop();
	result << "default constructor:" << std::endl;
	result << "content: " << show_vector_content(default_constructor) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;
	

	this->timer.start();
	container_type	length_constructor(100);
	this->timer.stop();
	result << "length constructor:" << std::endl;
	result << "content: " << show_vector_content(length_constructor) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;

	this->timer.start();
	container_type	value_constructor(100, this->get_single<type>());
	this->timer.stop();
	result << "value constructor:" << std::endl;
	result << "content: " << show_vector_content(value_constructor) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;
	

	std::list<type> range(this->get_multiple<type>(),  this->get_multiple<type>() + 10);
	this->timer.start();
	container_type	range_constructor(range.begin(), range.end());
	this->timer.stop();
	
	result << "range constructor:" << std::endl;
	result << "content: " << show_vector_content(range_constructor) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;

	this->timer.start();
	container_type	copy_constructor(range_constructor);
	this->timer.stop();
	
	result << "copy constructor:" << std::endl;
	result << "content: " << show_vector_content(copy_constructor) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms" << std::endl;
}


template<class U>
std::string VectorConstructor::show_vector_content(U vector_type)
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