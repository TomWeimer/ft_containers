#ifndef STACK_COMPARATOR_HPP
#define STACK_COMPARATOR_HPP

#include "../../TestTemplate/TestBase.hpp"

class StackComparator : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		StackComparator();
		StackComparator(const StackComparator& origin);
		StackComparator& operator=(const StackComparator& origin);
		~StackComparator();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_stack_content(U map_type);
};


StackComparator::StackComparator()
	: TestBase("comparator.log"){}


StackComparator::StackComparator(const StackComparator& origin)
	: TestBase(origin) {}


StackComparator::~StackComparator() {}


StackComparator& StackComparator::operator=(const StackComparator& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& StackComparator::testInstruction(int namespaces)
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
void StackComparator::execute_test()
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
	result << "return value: " << (stack_test == empty_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (stack_test != empty_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (stack_test > single_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (stack_test >= multiple_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (stack_test < multiple_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (stack_test <= empty_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_stack_content(stack_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}

template<class U>
std::string StackComparator::show_stack_content(U stack_type)
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