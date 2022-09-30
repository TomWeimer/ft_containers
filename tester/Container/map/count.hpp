#ifndef MAP_COUNT
#define MAP_COUNT

#include "../../TestTemplate/TestBase.hpp"

class MapCount : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapCount();
		MapCount(const MapCount& origin);
		MapCount& operator=(const MapCount& origin);
		~MapCount();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapCount::MapCount()
	: TestBase("count.log"){}


MapCount::MapCount(const MapCount& origin)
	: TestBase(origin) {}


MapCount::~MapCount() {}


MapCount& MapCount::operator=(const MapCount& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapCount::testInstruction(int namespaces)
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
void MapCount::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	typedef typename value_type::first_type first_type;
	typedef typename value_type::second_type second_type;
	typedef typename remove_const<first_type>::type key_type;
	typedef typename remove_const<second_type>::type data_type;


	std::vector<value_type> vector = this->multiple_pair<value_type>();
	container_type filled_map(vector.begin(), vector.end());
	filled_map.insert(value_type(get_single<key_type>(), get_single<data_type>()));

	this->timer.start();
	result << "return value: " << filled_map.count(get_single<key_type>()) << std::endl;
	this->timer.stop();
	result << "content:	" << show_map_content(filled_map) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string MapCount::show_map_content(U map_type)
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