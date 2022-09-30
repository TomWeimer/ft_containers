#ifndef STACK_ASSIGNEMENT_HPP
#define STACK_ASSIGNEMENT_HPP

#include "../../TestTemplate/TestBase.hpp"

class StackAssignement : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		StackAssignement();
		StackAssignement(const StackAssignement& origin);
		StackAssignement& operator=(const StackAssignement& origin);
		~StackAssignement();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_stack_content(U map_type);
};


StackAssignement::StackAssignement()
	: TestBase("assignement.log"){}


StackAssignement::StackAssignement(const StackAssignement& origin)
	: TestBase(origin) {}


StackAssignement::~StackAssignement() {}


StackAssignement& StackAssignement::operator=(const StackAssignement& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& StackAssignement::testInstruction(int namespaces)
{
	result.str("");
	if (namespaces == STD_ARG)
	{
		this->logfile.set_path("./logs/stack/stack_std/");
		this->logfile.clear();
		execute_test< std::stack< int, std::vector<int> > > ();
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
void StackAssignement::execute_test()
{
	typedef U container_type;
	typedef typename container_type::container_type sub_container;
	typedef typename container_type::container_type::value_type value_type;
	// typedef typename value_type::first_type first_type;
	// typedef typename value_type::second_type second_type;

	container_type empty_content;

	sub_container vector(this->get_multiple<value_type>(), this->get_multiple<value_type>() + 10);
	container_type multiple_content(vector);

	
	container_type single_content;
	single_content.push(this->get_single<value_type>());


	

	container_type stack_test;

	this->timer.start();
	stack_test = empty_content;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	stack_test = single_content;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	stack_test = multiple_content;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	stack_test = empty_content;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}

template<class U>
std::string StackAssignement::show_stack_content(U stack_type)
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