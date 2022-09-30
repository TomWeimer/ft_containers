#ifndef VECTOR_FRONT_HPP
#define VECTOR_FRONT_HPP
#include "../../TestTemplate/TestBase.hpp"

class VectorFront : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		VectorFront();
		VectorFront(const VectorFront& origin);
		VectorFront& operator=(const VectorFront& origin);
		~VectorFront();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_vector_content(U vector_type);
};


VectorFront::VectorFront()
	: TestBase("front.log"){}


VectorFront::VectorFront(const VectorFront& origin)
	: TestBase(origin) {}


VectorFront::~VectorFront() {}


VectorFront& VectorFront::operator=(const VectorFront& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& VectorFront::testInstruction(int namespaces)
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
void VectorFront::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type type;

	container_type container(this->get_multiple<type>(), this->get_multiple<type>() + 10);

	this->timer.start();
	result << "front: " << container.front() << std::endl;
	this->timer.stop();
	result << "content:	" << this->show_vector_content(container) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string VectorFront::show_vector_content(U vector_type)
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