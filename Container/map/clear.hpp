#ifndef MAP_CLEAR_HPP
#define MAP_CLEAR_HPP

#include "../../TestTemplate/TestBase.hpp"

class MapClear : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapClear();
		MapClear(const MapClear& origin);
		MapClear& operator=(const MapClear& origin);
		~MapClear();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapClear::MapClear()
	: TestBase("clear.log"){}


MapClear::MapClear(const MapClear& origin)
	: TestBase(origin) {}


MapClear::~MapClear() {}


MapClear& MapClear::operator=(const MapClear& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapClear::testInstruction(int namespaces)
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
void MapClear::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	// typedef typename value_type::first_type first_type;
	// typedef typename value_type::second_type second_type;

	std::vector<value_type> vector = this->multiple_pair<value_type>();
	container_type map_test(vector.begin(), vector.end());

	this->timer.start();
	map_test.clear();
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string MapClear::show_map_content(U map_type)
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