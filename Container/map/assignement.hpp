#ifndef MAP_ASSIGNEMENT_HPP
#define MAP_ASSIGNEMENT_HPP
#include "../../TestTemplate/TestBase.hpp"

class MapAssignement : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapAssignement();
		MapAssignement(const MapAssignement& origin);
		MapAssignement& operator=(const MapAssignement& origin);
		~MapAssignement();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapAssignement::MapAssignement()
	: TestBase("assignement.log"){}


MapAssignement::MapAssignement(const MapAssignement& origin)
	: TestBase(origin) {}


MapAssignement::~MapAssignement() {}


MapAssignement& MapAssignement::operator=(const MapAssignement& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapAssignement::testInstruction(int namespaces)
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
void MapAssignement::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	// typedef typename value_type::first_type first_type;
	// typedef typename value_type::second_type second_type;

	container_type empty_content;

	std::vector<value_type> vector = this->multiple_pair<value_type>();
	container_type multiple_content(vector.begin(), vector.end());

	
	container_type single_content;
	single_content.insert(single_content.begin(), this->normal_pair<value_type>());

	

	container_type map_test;

	this->timer.start();
	map_test = empty_content;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	map_test = single_content;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	map_test = multiple_content;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;

	this->timer.start();
	map_test = empty_content;
	this->timer.stop();
	result << "content:	" << show_map_content(map_test) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}

template<class U>
std::string MapAssignement::show_map_content(U map_type)
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