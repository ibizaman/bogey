#include <gtest/gtest.h>
#include "lib/Factory.hxx"
#include "test/DummyOsgReferencedClass.h"
#include "exception/ElementDoNotExist.h"
#include "exception/ElementAlreadyExists.h"

class FactoryTest : public ::testing::Test
{
public:
    FactoryTest()
        : _factory(false)
    {
        _factory.insert("1", new DummyOsgReferencedClass(1));
        _factory.insert("2", new DummyOsgReferencedClass(2));
    }

    Factory<DummyOsgReferencedClass> _factory;
};

TEST_F(FactoryTest, testDefault)
{
    ASSERT_EQ( true, _factory.isElement("1") );
    EXPECT_EQ( 1, _factory.getOriginal("1")->getI() );
    ASSERT_EQ( true, _factory.isElement("2") );
    EXPECT_EQ( 2, _factory.getOriginal("2")->getI() );
}

TEST_F(FactoryTest, testAdd)
{
    ASSERT_THROW( _factory.getOriginal("3"), ElementDoNotExist );
    _factory.insert("3", new DummyOsgReferencedClass(3));
    EXPECT_EQ( 3, _factory.getOriginal("3")->getI() );
}

TEST_F(FactoryTest, testReplace)
{
    _factory.insert("1", new DummyOsgReferencedClass(3) );
    EXPECT_EQ( 3, _factory.getOriginal("1")->getI() );
}

TEST_F(FactoryTest, testExists)
{
    Factory<DummyOsgReferencedClass> factory(true);
    factory.insert("1", new DummyOsgReferencedClass(1));
    ASSERT_THROW( factory.insert("1", new DummyOsgReferencedClass(2)), ElementAlreadyExists );
}

TEST_F(FactoryTest, testCopy)
{
    _factory.getCopy("2")->setI(1);
    EXPECT_EQ( 2, _factory.getOriginal("2")->getI() );
    EXPECT_EQ( 2, _factory.getCopy("2")->getI() );

    _factory.getOriginal("2")->setI(1);
    EXPECT_EQ( 1, _factory.getOriginal("2")->getI() );
}
