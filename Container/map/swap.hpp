#ifndef MAP_SWAP_HPP
#define MAP_SWAP_HPP

#include "../../TestTemplate/TestBase.hpp"

class MapSwap : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapSwap();
		MapSwap(const MapSwap& origin);
		MapSwap& operator=(const MapSwap& origin);
		~MapSwap();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapSwap::MapSwap()
	: TestBase("swap.log"){}


MapSwap::MapSwap(const MapSwap& origin)
	: TestBase(origin) {}


MapSwap::~MapSwap() {}


MapSwap& MapSwap::operator=(const MapSwap& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapSwap::testInstruction(int namespaces)
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
void MapSwap::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	// typedef typename value_type::first_type first_type;
	// typedef typename value_type::second_type second_type;

	std::vector<value_type> vector = this->multiple_pair<value_type>();
	container_type container1(vector.begin(), vector.end());
	container_type container2;

	result << "content before swap: " << std::endl;
	result << "container1: " << show_map_content(container1) << std::endl;
	result << "container2: " << show_map_content(container2) << std::endl;
	
	this->timer.start();
	container1.swap(container2);
	this->timer.stop();
	result << "content after swap: " << std::endl;
	result << "container1: " << show_map_content(container1) << std::endl;
	result << "container2: " << show_map_content(container2) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string MapSwap::show_map_content(U map_type)
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
		out << "{" << (*first).first << ", " << (*first).second << "}" << std::endl;
	}
	return (out.str());
}

#endif