#ifndef MAP_FIND_HPP
#define MAP_FIND_HPP
#include "../../TestTemplate/TestBase.hpp"

class MapFind : public TestBase
{
	private:
		std::stringstream	result;
	public:
		std::stringstream& testInstruction(int namespaces);
		MapFind();
		MapFind(const MapFind& origin);
		MapFind& operator=(const MapFind& origin);
		~MapFind();
	private:
		template<class U>
		void execute_test();
		template<class U>
		std::string show_map_content(U map_type);
};


MapFind::MapFind()
	: TestBase("find.log"){}


MapFind::MapFind(const MapFind& origin)
	: TestBase(origin) {}


MapFind::~MapFind() {}


MapFind& MapFind::operator=(const MapFind& origin)
{
	if (this == &origin)
		return (*this);
	TestBase::operator=(origin);
	return (*this);
}


std::stringstream& MapFind::testInstruction(int namespaces)
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
void MapFind::execute_test()
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
	result << "return value: " << (filled_map.find(get_single<key_type>()))->second << std::endl;
	this->timer.stop();
	result << "content:	" << show_map_content(filled_map) << std::endl;
	result << "time: " << this->timer.get_duration() << " ms"<< std::endl << std::endl;
}


template<class U>
std::string MapFind::show_map_content(U map_type)
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