#ifndef MAP_EQUAL_RANGE_HPP
#define MAP_EQUAL_RANGE_HPP
#include "../../TestTemplate/TestBase.hpp"

class MapEqualRange : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapEqualRange();
		MapEqualRange(const MapEqualRange& origin);
		MapEqualRange& operator=(const MapEqualRange& origin);
		~MapEqualRange();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
		template<class T, class U>
		struct equal_range_test;
};

template<class T, class U>
struct MapEqualRange::equal_range_test
{
	std::string test(U& filled_map)
	{
		T str = "Adelaide";
		std::stringstream stream;
		stream << "lower_range: " << ((filled_map.equal_range(str)).first)->first << ", " <<  ((filled_map.equal_range(str)).first)->second << std::endl;
		stream << "upper_range: " << ((filled_map.equal_range(str)).second)->first <<  ", " << ((filled_map.equal_range(str)).second)->second << std::endl;
		return (stream.str());
	}
};

template<class U>
struct MapEqualRange::equal_range_test<int, U>
{
	std::string test(U& filled_map)
	{
		std::stringstream stream;
		stream << "lower_range: " << ((filled_map.equal_range(5)).first)->first << ", " <<  ((filled_map.equal_range(5)).first)->second << std::endl;
		stream << "upper_range: " << ((filled_map.equal_range(5)).second)->first <<  ", " << ((filled_map.equal_range(5)).second)->second << std::endl;
		return (stream.str());
	}
};


MapEqualRange::MapEqualRange()
	: TestBase("equal_range.log"){}


MapEqualRange::MapEqualRange(const MapEqualRange& origin)
	: TestBase(origin) {}


MapEqualRange::~MapEqualRange() {}


MapEqualRange& MapEqualRange::operator=(const MapEqualRange& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapEqualRange::testInstruction(int namespaces)
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
void MapEqualRange::execute_test()
{
	typedef U container_type;
	typedef typename container_type::value_type value_type;
	typedef typename value_type::first_type first_type;
	typedef typename remove_const<first_type>::type key_type;
	
	std::vector<value_type> vector = this->multiple_pair<value_type>();
	container_type filled_map(vector.begin(), vector.end());
	equal_range_test<key_type, U> function;

	this->timer.start();
	result << function.test(filled_map);
	this->timer.stop();
	result << "content:	" << show_map_content(filled_map) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}

template<class U>
std::string MapEqualRange::show_map_content(U map_type)
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