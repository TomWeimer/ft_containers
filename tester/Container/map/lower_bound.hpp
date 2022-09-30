#ifndef MAP_LOWER_BOUND_HPP
#define MAP_LOWER_BOUND_HPP
#include "../../TestTemplate/TestBase.hpp"

class MapLowerBound : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapLowerBound();
		MapLowerBound(const MapLowerBound& origin);
		MapLowerBound& operator=(const MapLowerBound& origin);
		~MapLowerBound();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapLowerBound::MapLowerBound()
	: TestBase("lower_bound.log"){}


MapLowerBound::MapLowerBound(const MapLowerBound& origin)
	: TestBase(origin) {}


MapLowerBound::~MapLowerBound() {}


MapLowerBound& MapLowerBound::operator=(const MapLowerBound& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapLowerBound::testInstruction(int namespaces)
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
void MapLowerBound::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::iterator iterator;
	typedef typename value_type::first_type first_type;
	typedef typename value_type::second_type second_type;
	typedef typename remove_const<first_type>::type key_type;
	typedef typename remove_const<second_type>::type data_type;


	std::vector<value_type> vector = this->multiple_pair<value_type>();
	container_type filled_map(vector.begin(), vector.end());
	filled_map.insert(value_type(get_single<key_type>(), get_single<data_type>()));

	this->timer.start();
	iterator tmp = filled_map.lower_bound(get_single<key_type>());
	this->timer.stop();
	result << "return value: " << tmp->first << ", " << tmp->second << std::endl;
	result << "content:	" << show_map_content(filled_map) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string MapLowerBound::show_map_content(U map_type)
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