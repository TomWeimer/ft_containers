#ifndef VECTOR_CLEAR_HPP
#define VECTOR_CLEAR_HPP

#include "../../TestTemplate/TestBase.hpp"

class VectorClear : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		VectorClear();
		VectorClear(const VectorClear& origin);
		VectorClear& operator=(const VectorClear& origin);
		~VectorClear();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_vector_content(U vector_type);
};


VectorClear::VectorClear()
	: TestBase("clear.log"){}


VectorClear::VectorClear(const VectorClear& origin)
	: TestBase(origin) {}


VectorClear::~VectorClear() {}


VectorClear& VectorClear::operator=(const VectorClear& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& VectorClear::testInstruction(int namespaces)
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
void VectorClear::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type type;

	container_type container(this->get_multiple<type>(), this->get_multiple<type>() + 10);
	result << "clear: " << std::endl;
	this->timer.start();
	container.clear();
	this->timer.stop();
	result << "content:	" << this->show_vector_content(container) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string VectorClear::show_vector_content(U vector_type)
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