#ifndef MAP_COMPARATOR_HPP
#define MAP_COMPARATOR_HPP
#include "../../TestTemplate/TestBase.hpp"

class MapComparator : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapComparator();
		MapComparator(const MapComparator& origin);
		MapComparator& operator=(const MapComparator& origin);
		~MapComparator();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapComparator::MapComparator()
	: TestBase("comparator.log"){}


MapComparator::MapComparator(const MapComparator& origin)
	: TestBase(origin) {}


MapComparator::~MapComparator() {}


MapComparator& MapComparator::operator=(const MapComparator& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapComparator::testInstruction(int namespaces)
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
void MapComparator::execute_test()
{
	
	typedef U container_type;
	typedef typename container_type::value_type value_type;

	container_type empty_content;

	std::vector<value_type> vector = this->multiple_pair<value_type>();
	container_type multiple_content(vector.begin(), vector.end());

	
	container_type single_content;
	single_content.insert(single_content.begin(), this->normal_pair<value_type>());

	

	container_type map_test;

	this->timer.start();
	result << "return value: " << (map_test == empty_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " <<  this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (map_test != empty_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (map_test < single_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (map_test <= empty_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (map_test > multiple_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	result << "return value: " << (map_test >= empty_content) << std::endl;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}

template<class U>
std::string MapComparator::show_map_content(U map_type)
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