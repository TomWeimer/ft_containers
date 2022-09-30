#ifndef MAP_CONSTRUCTOR_HPP
#define MAP_CONSTRUCTOR_HPP
#include "../../TestTemplate/TestBase.hpp"
#include <functional>

class MapConstructor : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapConstructor();
		MapConstructor(const MapConstructor& origin);
		MapConstructor& operator=(const MapConstructor& origin);
		~MapConstructor();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapConstructor::MapConstructor()
	: TestBase("constructor.log"){}


MapConstructor::MapConstructor(const MapConstructor& origin)
	: TestBase(origin) {}


MapConstructor::~MapConstructor() {}


MapConstructor& MapConstructor::operator=(const MapConstructor& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapConstructor::testInstruction(int namespaces)
{
	result.str("");
	if (namespaces == STD_ARG)
	{
		this->logfile.set_path("./logs/map/map_std/");
		this->logfile.clear();
		execute_test<std::map<std::string, int> >();
		execute_test<std::map<int, std::string > >();
	}
	else if (namespaces == FT_ARG)
	{
		this->logfile.set_path("./logs/map/my_map/");
		this->logfile.clear();
		execute_test<ft::map<std::string, int> >();
		execute_test<ft::map<int, std::string > >();
	}
	return (result);
}


template<class U>
void MapConstructor::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;

	this->timer.start();
	container_type default_constructor;
	this->timer.stop();
	result << "content:	" << show_map_content(default_constructor);
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	std::vector<value_type> vector = this->multiple_pair<value_type>();
	this->timer.start();
	container_type range_constructor(vector.begin(), vector.end());
	this->timer.stop();

	result << "content:	" << show_map_content(range_constructor);
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}

template<class U>
std::string MapConstructor::show_map_content(U map_type)
{
	typedef U container_type;
	typedef typename container_type::iterator iterator;
	std::stringstream	out;
	iterator			first;
	iterator			last;
	
	first = map_type.begin();
	last = map_type.end();
	for(; first != last; first++)
	{
		out << "{" << (*first).first << ", " << (*first).second << "} ";
	}
	return (out.str());
}
#endif