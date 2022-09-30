#ifndef VECTOR_END_HPP
#define VECTOR_END_HPP

#include "../../TestTemplate/TestBase.hpp"

class VectorEnd : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		VectorEnd();
		VectorEnd(const VectorEnd& origin);
		VectorEnd& operator=(const VectorEnd& origin);
		~VectorEnd();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_vector_content(U vector_type);
};


VectorEnd::VectorEnd()
	: TestBase("end.log"){}


VectorEnd::VectorEnd(const VectorEnd& origin)
	: TestBase(origin) {}


VectorEnd::~VectorEnd() {}


VectorEnd& VectorEnd::operator=(const VectorEnd& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& VectorEnd::testInstruction(int namespaces)
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
void VectorEnd::execute_test()
{
	typedef U container_type;
	typedef typename container_type::iterator iterator;
	typedef typename container_type::value_type type;
	iterator it;

	container_type container(this->get_multiple<type>(), this->get_multiple<type>() + 10);
	
	this->timer.start();
	it = container.end();
	this->timer.stop();
	result << "end: " << std::endl;
	result << "one before end: " <<  *(it - 1) << std::endl;
	result << "content:	" << this->show_vector_content(container) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string VectorEnd::show_vector_content(U vector_type)
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