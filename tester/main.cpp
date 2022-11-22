
#include "./Container/all-test.hpp"
#include <cstdlib>

int main(int argc, char *argv[])
{
	int mode;

	if (argc != 2)
		return (0);
	mode = std::atoi(argv[1]);
	if (mode == STD_ARG || mode == FT_ARG)
	{
		launchVectorTest(mode);
		launchMapTest(mode);
		launchStackTest(mode);

	}
	else if (mode == BOTH_ARG)
	{
		// compareVectorTest();
		// compareMapTest();
		compareStackTest();
	}
}

void launchVectorTest(int mode)
{
	launchTest<VectorAssignement> (mode);
	launchTest<VectorAt> (mode);
	launchTest<VectorBack> (mode);
	launchTest<VectorBegin> (mode);
	launchTest<VectorCapacity> (mode);
	launchTest<VectorClear> (mode);
	launchTest<VectorConstructor> (mode);
	launchTest<VectorEmpty> (mode);
	launchTest<VectorEnd> (mode);
	launchTest<VectorErase> (mode);
	launchTest<VectorFront> (mode);
	launchTest<VectorInsert> (mode);
	launchTest<VectorMaxSize> (mode);
	launchTest<VectorOperator> (mode);
	launchTest<VectorPopBack> (mode);
	launchTest<VectorPushBack> (mode);
	launchTest<VectorReserve> (mode);
	launchTest<VectorResize> (mode);
	launchTest<VectorSize> (mode);
	launchTest<VectorSwap> (mode);
	launchTest<VectorComparator>(mode);
}

void compareVectorTest()
{
	std::cout << "	VECTOR:" <<std::endl;
	std::cout << "	‾‾‾‾‾‾" <<std::endl;
	compareTest<VectorConstructor>("constructor");
	compareTest<VectorAssignement>("assignement");
	compareTest<VectorAt>("at");
	compareTest<VectorOperator>("operator[]");
	compareTest<VectorEmpty>("empty");
	compareTest<VectorFront>("front");
	compareTest<VectorBack>("back");
	compareTest<VectorSize>("size");
	compareTest<VectorMaxSize>("max_size");
	compareTest<VectorCapacity>("capacity");
	compareTest<VectorReserve>("reserve");
	compareTest<VectorResize>("resize");
	compareTest<VectorBegin>("begin");
	compareTest<VectorEnd>("end");
	compareTest<VectorInsert>("insert");
	compareTest<VectorPushBack>("push_back");
	compareTest<VectorPopBack>("pop_back");
	compareTest<VectorErase>("erase");
	compareTest<VectorClear>("clear");
	compareTest<VectorSwap>("swap");
	compareTest<VectorComparator>("comparator");
}


void launchMapTest(int mode)
{
	launchTest<MapConstructor> (mode);
	launchTest<MapAssignement> (mode);
	launchTest<MapAt> (mode);
	launchTest<MapBegin> (mode);
	launchTest<MapClear> (mode);
	launchTest<MapEmpty> (mode);
	launchTest<MapEnd> (mode);
	launchTest<MapErase> (mode);
	launchTest<MapInsert> (mode);
	launchTest<MapOperator> (mode);
	launchTest<MapSize> (mode);
	launchTest<MapSwap> (mode);
	launchTest<MapCount>(mode);
	launchTest<MapEqualRange>(mode);
	launchTest<MapLowerBound>(mode);
	launchTest<MapUpperBound>(mode);
	launchTest<MapFind>(mode);
	launchTest<MapComparator>(mode);
}

void compareMapTest()
{
	std::cout << "\n	MAP:" <<std::endl;
	std::cout << "	‾‾‾" <<std::endl;
	compareTest<MapConstructor> ("constructor");
	compareTest<MapAssignement> ("assignement");
	compareTest<MapAt> ("at");
	compareTest<MapBegin> ("begin");
	compareTest<MapClear> ("clear") ;
	compareTest<MapEmpty> ("empty");
	compareTest<MapEnd> ("end");
	compareTest<MapErase> ("erase");
	compareTest<MapInsert> ("insert");
	compareTest<MapOperator> ("operator[]");
	compareTest<MapSize> ("size");
	compareTest<MapSwap> ("swap");
	compareTest<MapCount> ("count");
	compareTest<MapEqualRange> ("equal_range");
	compareTest<MapLowerBound> ("lower_bound");
	compareTest<MapUpperBound> ("upper_bound");
	compareTest<MapFind> ("find");
	compareTest<MapComparator>("comparator");
}
void launchStackTest(int mode)
{
	launchTest<StackAssignement> (mode);
	launchTest<StackConstructor> (mode);
	launchTest<StackEmpty> (mode);
	launchTest<StackPop> (mode);
	launchTest<StackPush> (mode);
	launchTest<StackSize> (mode);
	launchTest<StackTop> (mode);
	launchTest<StackComparator>(mode);
}

void compareStackTest()
{
	std::cout << "\n	STACK:" <<std::endl;
	std::cout << "	‾‾‾‾‾" <<std::endl;
	compareTest<StackAssignement> ("assignement");
	compareTest<StackConstructor> ("constructor");
	compareTest<StackEmpty> ("empty");
	compareTest<StackPop> ("pop");
	compareTest<StackPush> ("push");
	compareTest<StackSize> ("size");
	compareTest<StackTop> ("top");
	compareTest<StackComparator>("comparator");
}