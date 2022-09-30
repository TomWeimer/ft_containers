#ifndef STACK_EMPTY_HPP
#define STACK_EMPTY_HPP

#include "../../TestTemplate/TestBase.hpp"
class StackEmpty : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		StackEmpty();
		StackEmpty(const StackEmpty& origin);
		StackEmpty& operator=(const StackEmpty& origin);
		~StackEmpty();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_stack_content(U stack_type);
};


StackEmpty::StackEmpty()
	: TestBase("empty.log"){}


StackEmpty::StackEmpty(const StackEmpty& origin)
	: TestBase(origin) {}


StackEmpty::~StackEmpty() {}


StackEmpty& StackEmpty::operator=(const StackEmpty& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& StackEmpty::testInstruction(int namespaces)
{
	result.str("");
	if (namespaces == STD_ARG)
	{
		this->logfile.set_path("./logs/stack/stack_std/");
		this->logfile.clear();
		execute_test<std::stack<int, std::vector<int> > >();
	}
	else if (namespaces == FT_ARG)
	{
		this->logfile.set_path("./logs/stack/my_stack/");
		this->logfile.clear();
		execute_test<ft::stack<int, ft::vector<int> > >();
	}
	return (result);
}




template<class U>
void StackEmpty::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::container_type sub_container;

	sub_container vector(this->get_multiple<value_type>(), this->get_multiple<value_type>() + 10);

	container_type empty_content;
	container_type multiple_content(vector);

	this->timer.start();
	result << "return value: " << empty_content.empty();
	this->timer.stop();
	result << "content:	" << show_stack_content(empty_content) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << multiple_content.empty();
	this->timer.stop();
	result << "content:	" << show_stack_content(multiple_content) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}

template<class U>
std::string StackEmpty::show_stack_content(U stack_type)
{
	std::stringstream	out;
	
	while(stack_type.empty() == false)
	{
		out << (stack_type.top()) << " ";
		stack_type.pop();
	}
	out << std::endl;
	return (out.str());
}

#endif