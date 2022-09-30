#ifndef STACK_CONSTRUCTOR_HPP
#define STACK_CONSTRUCTOR_HPP

#include "../../TestTemplate/TestBase.hpp"
class StackConstructor : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		StackConstructor();
		StackConstructor(const StackConstructor& origin);
		StackConstructor& operator=(const StackConstructor& origin);
		~StackConstructor();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_stack_content(U stack_type);
};


StackConstructor::StackConstructor()
	: TestBase("constructor.log"){}


StackConstructor::StackConstructor(const StackConstructor& origin)
	: TestBase(origin) {}


StackConstructor::~StackConstructor() {}


StackConstructor& StackConstructor::operator=(const StackConstructor& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& StackConstructor::testInstruction(int namespaces)
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
void StackConstructor::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::container_type sub_container;
	// typedef typename value_type::first_type first_type;
	// typedef typename value_type::second_type second_type;

	sub_container vector(this->get_multiple<value_type>(), this->get_multiple<value_type>() + 10);

	this->timer.start();
	container_type default_constructor;
	this->timer.stop();
	result << "content:	" << show_stack_content(default_constructor) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	container_type container_constructor(vector);
	this->timer.stop();
	result << "content:	" << show_stack_content(container_constructor) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}

template<class U>
std::string StackConstructor::show_stack_content(U stack_type)
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