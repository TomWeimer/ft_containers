#ifndef MAP_INSERT_HPP
#define MAP_INSERT_HPP

#include "../../TestTemplate/TestBase.hpp"

class MapInsert : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapInsert();
		MapInsert(const MapInsert& origin);
		MapInsert& operator=(const MapInsert& origin);
		~MapInsert();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapInsert::MapInsert()
	: TestBase("insert.log"){}


MapInsert::MapInsert(const MapInsert& origin)
	: TestBase(origin) {}


MapInsert::~MapInsert() {}


MapInsert& MapInsert::operator=(const MapInsert& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapInsert::testInstruction(int namespaces)
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
void MapInsert::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	// typedef typename value_type::first_type first_type;
	// typedef typename value_type::second_type second_type;

	std::vector<value_type> vector = this->multiple_pair<value_type>();
	container_type map_filled(vector.begin(), vector.end());

	container_type map_empty;
	container_type map_test;

	this->timer.start();
	map_empty.insert(vector.begin(), vector.end());
	this->timer.stop();
	result << "content:	" << show_map_content(map_empty) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	map_test.insert(normal_pair<value_type>());
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string MapInsert::show_map_content(U map_type)
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