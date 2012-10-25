#include <gtest/gtest.h>
#include <string>
#include "lib/DirectionMap.hxx"
#include "exception/TooCloseToOtherVectorException.h"
#include "test/DummyOsgReferencedClass.h"

typedef DummyOsgReferencedClass DummyClass;

typedef DirectionMap<DummyClass> Map;
typedef Map::Element Element;
typedef Map::Direction Direction;

class DirectionMapTest : public ::testing::Test
{
public:
    DirectionMapTest() {
        _map.set(Direction(   1,   0,  0), new DummyClass(1));
        _map.set(Direction(   0,   1,  0), new DummyClass(2));
        _map.set(Direction(   0,  -1,  0), new DummyClass(3));
        _map.set(Direction(   0,  -1, -1), new DummyClass(4));
        _map.set(Direction(   2,   1, -2), Element(new DummyClass(5)));
        _map.insert(Map::Pair(Direction(-2.1,   1,  0), Element(new DummyClass(6))));
    }

    Map _map;
};

TEST_F(DirectionMapTest, testCount)
{
    EXPECT_EQ( 1, _map.count(Direction(   1,  0,  0)) );
    EXPECT_EQ( 1, _map.count(Direction(   0,  1,  0)) );
    EXPECT_EQ( 1, _map.count(Direction(   0, -1,  0)) );
    EXPECT_EQ( 1, _map.count(Direction(   0, -1, -1)) );
    EXPECT_EQ( 1, _map.count(Direction(   2,  1, -2)) );
    EXPECT_EQ( 1, _map.count(Direction(-2.1,  1,  0)) );
}

TEST_F(DirectionMapTest, testSimpleGet)
{
    EXPECT_EQ( 1, _map.get(Direction(   1,  0,  0))->getI() );
    EXPECT_EQ( 2, _map.get(Direction(   0,  1,  0))->getI() );
    EXPECT_EQ( 3, _map.get(Direction(   0, -1,  0))->getI() );
    EXPECT_EQ( 4, _map.get(Direction(   0, -1, -1))->getI() );
    EXPECT_EQ( 5, _map.get(Direction(   2,  1, -2))->getI() );
    EXPECT_EQ( 6, _map.get(Direction(-2.1,  1,  0))->getI() );
}

TEST_F(DirectionMapTest, testCloseValues)
{
    EXPECT_EQ( 3, _map.get(Direction( 0, -1, -0.2))->getI() );
    EXPECT_EQ( 4, _map.get(Direction( 0, -1, -0.8))->getI() );
}

TEST_F(DirectionMapTest, testNormalize)
{
    EXPECT_EQ( 2, _map.get(Direction( 0, 4, 0))->getI() );
}

TEST_F(DirectionMapTest, testTooClose)
{
    ASSERT_THROW(_map.set(Direction( 0, 1, 0), new DummyClass(3)), TooCloseToOtherVectorException);
}

TEST_F(DirectionMapTest, testOpposite)
{
    Map map;
    map.set(Direction(0,0,1), new DummyClass(1));
    EXPECT_EQ( 1, map.get(Direction(0,0,-1))->getI() );
}
