#ifndef VECTOR_POP_BACK_HPP
#define VECTOR_POP_BACK_HPP

#include "../../TestTemplate/TestBase.hpp"

class VectorPopBack : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		VectorPopBack();
		VectorPopBack(const VectorPopBack& origin);
		VectorPopBack& operator=(const VectorPopBack& origin);
		~VectorPopBack();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_vector_content(U vector_type);
};


VectorPopBack::VectorPopBack()
	: TestBase("pop_back.log"){}


VectorPopBack::VectorPopBack(const VectorPopBack& origin)
	: TestBase(origin) {}


VectorPopBack::~VectorPopBack() {}


VectorPopBack& VectorPopBack::operator=(const VectorPopBack& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& VectorPopBack::testInstruction(int namespaces)
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
void VectorPopBack::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type type;

	container_type container(this->get_multiple<type>(), this->get_multiple<type>() + 10);
	result << "pop_back: " << std::endl;
	this->timer.start();
	container.pop_back();
	this->timer.stop();
	result << "content:	" << this->show_vector_content(container) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string VectorPopBack::show_vector_content(U vector_type)
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