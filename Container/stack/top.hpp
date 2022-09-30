#ifndef STACK_TOP_HPP
#define STACK_TOP_HPP
#include "../../TestTemplate/TestBase.hpp"
class StackTop : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		StackTop();
		StackTop(const StackTop& origin);
		StackTop& operator=(const StackTop& origin);
		~StackTop();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_stack_content(U stack_type);
};


StackTop::StackTop()
	: TestBase("top.log"){}


StackTop::StackTop(const StackTop& origin)
	: TestBase(origin) {}


StackTop::~StackTop() {}


StackTop& StackTop::operator=(const StackTop& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& StackTop::testInstruction(int namespaces)
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
void StackTop::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::container_type sub_container;

	sub_container vector(this->get_multiple<value_type>(), this->get_multiple<value_type>() + 10);

	container_type container1(vector);

	this->timer.start();
	result << "return value: " << container1.top() << std::endl;
	this->timer.stop();
	result << "content:	" << show_stack_content(container1) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}

template<class U>
std::string StackTop::show_stack_content(U stack_type)
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