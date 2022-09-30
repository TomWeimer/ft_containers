#include "../Logfile.hpp"

int main()
{
	Logfile test("testfile.log");
	test.clear();
	test << "Bonjour";
}