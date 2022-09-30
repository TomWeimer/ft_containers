#ifndef MAP_END_HPP
#define MAP_END_HPP

#include "../../TestTemplate/TestBase.hpp"

class MapEnd : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapEnd();
		MapEnd(const MapEnd& origin);
		MapEnd& operator=(const MapEnd& origin);
		~MapEnd();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapEnd::MapEnd()
	: TestBase("end.log"){}


MapEnd::MapEnd(const MapEnd& origin)
	: TestBase(origin) {}


MapEnd::~MapEnd() {}


MapEnd& MapEnd::operator=(const MapEnd& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapEnd::testInstruction(int namespaces)
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
void MapEnd::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::iterator iterator;
	// typedef typename value_type::first_type first_type;
	// typedef typename value_type::second_type second_type;

	iterator tmp;
	std::vector<value_type> vector = this->multiple_pair<value_type>();
	container_type map_test(vector.begin(), vector.end());

	this->timer.start();
	tmp = map_test.end();
	tmp--;
	result << "end - 1: " << (*tmp).first << ", " <<  (*tmp).second << std::endl;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string MapEnd::show_map_content(U map_type)
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