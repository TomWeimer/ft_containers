#ifndef STACK_PUSH_HPP
#define STACK_PUSH_HPP

#include "../../TestTemplate/TestBase.hpp"
class StackPush : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		StackPush();
		StackPush(const StackPush& origin);
		StackPush& operator=(const StackPush& origin);
		~StackPush();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_stack_content(U stack_type);
};


StackPush::StackPush()
	: TestBase("push.log"){}


StackPush::StackPush(const StackPush& origin)
	: TestBase(origin) {}


StackPush::~StackPush() {}


StackPush& StackPush::operator=(const StackPush& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& StackPush::testInstruction(int namespaces)
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
void StackPush::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	container_type empty_content;

	this->timer.start();
	empty_content.push(get_single<value_type>());
	this->timer.stop();
	result << "content:	" << show_stack_content(empty_content) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

}

template<class U>
std::string StackPush::show_stack_content(U stack_type)
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