#ifndef MAP_TEST_HPP
#define MAP_TEST_HPP
template< typename T >
struct remove_const
{
    typedef T type;
};

template< typename T >
struct remove_const< const T >
{
    typedef T type;
};






#include "./map/constructor.hpp"
#include "./map/comparator.hpp"
#include "./map/assignement.hpp"
#include "./map/at.hpp"
#include "./map/begin.hpp"
#include "./map/clear.hpp"
#include "./map/empty.hpp"
#include "./map/end.hpp"
#include "./map/erase.hpp"
#include "./map/insert.hpp"
#include "./map/operator[].hpp"
#include "./map/size.hpp"
#include "./map/swap.hpp"
#include "./map/upper_bound.hpp"
#include "./map/lower_bound.hpp"
#include "./map/equal_range.hpp"
#include "./map/count.hpp"
#include "./map/find.hpp"
void launchMapTest(int mode);
void compareMapTest();
#endif