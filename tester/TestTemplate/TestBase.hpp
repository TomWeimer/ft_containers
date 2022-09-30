#ifndef TESTBASE_HPP
#define TESTBASE_HPP
#include "./Timer/Timer.hpp"
#include "./Logfile/Logfile.hpp"
#include "../ft_container-tester.hpp"
#define COLOR_RED "\e[0;31m"
#define COLOR_GREEN "\e[0;33m"
#define COLOR_RESET "\e[0;0m"
#include <cstdlib>
struct content_data
{
	std::string emptyString;
	std::string	normalString;
	std::string multipleString[10];
	int			emptyInt;
	int			normalInt;
	int			multipleInt[10];
	content_data()
	{
		this->normalString = "Hello 42";
		multipleString[0] = "Lausanne";
		multipleString[1] = "Paris";
		multipleString[2] = "Lyon";
		multipleString[3] = "Adelaide";
		multipleString[4] = "Malaga";
		multipleString[5] = "Luxembourg";
		multipleString[6] = "Seoul";
		multipleString[7] = "Tokyo";
		multipleString[8] = "Rio";
		multipleString[9] = "Montreal";
		this->normalInt = 42;
		multipleInt[0] = 1;
		multipleInt[1] = 2;
		multipleInt[2] = 3;
		multipleInt[3] = 4;
		multipleInt[4] = 5;
		multipleInt[5] = 6;
		multipleInt[6] = 7;
		multipleInt[7] = 8;
		multipleInt[8] = 9;
		multipleInt[9] = 10;

	}
	~content_data() {}
};

class TestBase
{
protected:
	std::string		testName;
	Logfile			logfile;
	Timer			timer;
	content_data	ressources;


public:
	TestBase(std::string name = "default-TestBase");
	TestBase(const TestBase &origin);
	TestBase &operator=(const TestBase &origin);
	virtual ~TestBase();

public:
	void launch_std_tests();
	void launch_ft_tests();
	void clear();
	void compareTest();
	//std::string	compareTestBase(const std::string &logfileName);

protected:
	void				writeToLog(const std::stringstream& content);
	virtual std::stringstream&	testInstruction(int namespaces) = 0;
	template<class T>
	T get_empty();
	template<class T>
	T get_single();
	template<class T>
	T *get_multiple();

	template<class T>
	T empty_pair();
	template<class T>
	T normal_pair();
	template<class T>
	std::vector<T> multiple_pair();

};


TestBase::TestBase(std::string name)
	: testName(name), logfile(testName),
	  timer() {}


TestBase::TestBase(const TestBase &origin)
	: testName(origin.testName), logfile(origin.logfile),
	  timer(origin.timer) {}


TestBase &TestBase::operator=(const TestBase &origin)
{
	if (this == &origin)
		return (*this);
	this->testName = origin.testName;
	this->logfile = origin.logfile;
	this->timer = origin.timer;
	return (*this);
}


TestBase::~TestBase() {}


void TestBase::launch_std_tests()
{
	writeToLog(testInstruction(STD_ARG));
}


void TestBase::launch_ft_tests()
{
	writeToLog(testInstruction(FT_ARG));	
}

void TestBase::compareTest()
{
	std::string filename[2];
	launch_std_tests();
	filename[0] = logfile.get_fullname();
	launch_ft_tests();
	filename[1] = logfile.get_fullname();
	if (compare_file(filename[0], filename[1]) == false)
		std::cerr << COLOR_RED << " [X]" << COLOR_RESET;
	else
		std::cerr <<COLOR_GREEN << " [✓]" << COLOR_RESET;
}

void TestBase::clear()
{
	logfile.clear();	
}


void TestBase::writeToLog(const std::stringstream& content)
{
	logfile << content;
}

template<>
int TestBase::get_empty<int>() {
	return (ressources.emptyInt);
}

template<>
int TestBase::get_single<int>() {
	return (ressources.normalInt);
}

template<>
int *TestBase::get_multiple<int>() {
	return (ressources.multipleInt);
}


template<>
std::string TestBase::get_empty<std::string>() {
	return (ressources.emptyString);
}

template<>
std::string TestBase::get_single<std::string>() {
	return (ressources.normalString);
}

template<>
std::string* TestBase::get_multiple<std::string>() {
	return (ressources.multipleString);
}

template<class T>
T TestBase::empty_pair() {
	typedef typename T::first_type first_type;
	typedef typename T::second_type second_type;

	return (T(this->get_empty<first_type>(), this->get_empty<second_type>() ));
}

template<class T>
T TestBase::normal_pair() {
	typedef typename T::first_type first_type;
	typedef typename T::second_type second_type;
	typedef typename remove_const<first_type>::type key_type;
	typedef typename remove_const<second_type>::type data_type;

	return (T(this->get_single<key_type>(), this->get_single<data_type>() ));
}

template<class T, class key_type, class data_type>
T create_pair(key_type *array_key, data_type *array_data, int i)
{
	return (T(array_key[i], array_data[i]));
}

template<class T>
std::vector<T> TestBase::multiple_pair()
{
	typedef typename T::first_type first_type;
	typedef typename T::second_type second_type;
	typedef typename remove_const<first_type>::type key_type;
	typedef typename remove_const<second_type>::type data_type;
	std::vector<T> vector;
	key_type* array_key = get_multiple<key_type>();
	data_type* array_data = get_multiple<data_type>();
	for (int i = 0; i < 10; i++)
		vector.push_back(create_pair<T, key_type, data_type>(array_key, array_data, i));

	return (std::vector<T>(vector.begin(), vector.end()));
}

#endif