#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <osg/PositionAttitudeTransform>
#include <osg/Vec3d>
#include "terrain/ShapeTransform.h"
#include <iostream>

class ShapeTransformTest : public ::testing::Test
{
public:
    ShapeTransformTest()
    {
        _faces = new ShapeTransform::Faces();
        _faces->set(osg::Vec3d( 1, 0,0), new osg::PositionAttitudeTransform());
        _faces->set(osg::Vec3d(-1, 0,0), new osg::PositionAttitudeTransform());
        _faces->set(osg::Vec3d( 0, 1,0), new osg::PositionAttitudeTransform());
        _faces->set(osg::Vec3d( 0,-1,0), new osg::PositionAttitudeTransform());

        _left = new ShapeTransform(_faces);
        _left->setPosition(osg::Vec3d(0,0,0));
        _right = new ShapeTransform(_faces);
        _right->setPosition(osg::Vec3d(1,0,0));
        _front = new ShapeTransform(_faces);
        _front->setPosition(osg::Vec3d(0,1,0));
    }

    osg::ref_ptr<ShapeTransform::Faces> _faces;
    osg::ref_ptr<ShapeTransform> _left;
    osg::ref_ptr<ShapeTransform> _right;
    osg::ref_ptr<ShapeTransform> _front;
};

TEST_F(ShapeTransformTest, testDefault)
{
    for (ShapeTransform::Faces::iterator it = _faces->begin(); it != _faces->end(); ++it) {
        EXPECT_EQ( false, _left->getNeighbour(it->first).valid() );
        EXPECT_EQ( false, _left->isFaceHidden(it->first) );
        EXPECT_EQ( false, _right->getNeighbour(it->first).valid() );
        EXPECT_EQ( false, _right->isFaceHidden(it->first) );
        EXPECT_EQ( false, _front->getNeighbour(it->first).valid() );
        EXPECT_EQ( false, _front->isFaceHidden(it->first) );
    }
    EXPECT_EQ( false, _left->isTransparent() );
    EXPECT_EQ( false, _right->isTransparent() );
    EXPECT_EQ( false, _front->isTransparent() );
}

TEST_F(ShapeTransformTest, testUnsuccesfulBindNeighbour)
{
    osg::ref_ptr<ShapeTransform> nullright;

    _left->bindNeighbour(nullright);

    EXPECT_EQ( false, _left->getNeighbour(osg::Vec3d( 1,0,0)).valid() );
    EXPECT_EQ( false, _left->isFaceHidden(osg::Vec3d( 1,0,0)) );
}

TEST_F(ShapeTransformTest, testUnsuccesfulBindNeighbourSelf)
{
    _left->bindNeighbour(_left);

    EXPECT_EQ( false, _left->getNeighbour(osg::Vec3d( 1,0,0)).valid() );
    EXPECT_EQ( false, _left->isFaceHidden(osg::Vec3d( 1,0,0)) );
}

TEST_F(ShapeTransformTest, testBindNeighbour)
{
    ASSERT_NE( _left.get(), _right.get() );

    _left->bindNeighbour(_right);

    EXPECT_EQ( _right.get(), _left->getNeighbour(osg::Vec3d( 1,0,0)).get() );
    EXPECT_EQ( _left.get(), _right->getNeighbour(osg::Vec3d(-1,0,0)).get() );
    EXPECT_EQ( true, _left->isFaceHidden(osg::Vec3d( 1,0,0)) );
    EXPECT_EQ( true, _right->isFaceHidden(osg::Vec3d(-1,0,0)) );
}

TEST_F(ShapeTransformTest, testBindMultipleNeighbour)
{
    ASSERT_NE( _left.get(), _right.get() );
    ASSERT_NE( _left.get(), _front.get() );

    _right->bindNeighbour(_left);
    _front->bindNeighbour(_left);

    EXPECT_EQ( _right.get(), _left->getNeighbour(osg::Vec3d( 1, 0,0)).get() );
    EXPECT_EQ( _left.get(), _right->getNeighbour(osg::Vec3d(-1, 0,0)).get() );
    EXPECT_EQ( _front.get(), _left->getNeighbour(osg::Vec3d( 0, 1,0)).get() );
    EXPECT_EQ( _left.get(), _front->getNeighbour(osg::Vec3d( 0,-1,0)).get() );
}

TEST_F(ShapeTransformTest, testRebindBindNeighbour)
{
    osg::ref_ptr<ShapeTransform> right2(_right.get());
    ASSERT_NE( _left.get(), _right.get() );
    ASSERT_NE( _left.get(), right2.get() );

    _left->bindNeighbour(right2);
    _left->bindNeighbour(_right);

    EXPECT_EQ( false, right2->getNeighbour(osg::Vec3d( 1,0,0)).valid() );
    EXPECT_EQ( _right.get(), _left->getNeighbour(osg::Vec3d( 1,0,0)).get() );
    EXPECT_EQ( _left.get(), _right->getNeighbour(osg::Vec3d(-1,0,0)).get() );
}

TEST_F(ShapeTransformTest, testUnbind)
{
    ASSERT_NE( _left.get(), _right.get() );

    _left->bindNeighbour(_right);
    _right->unbindNeighbour(osg::Vec3d(-1,0,0));

    EXPECT_EQ( false, _left->getNeighbour(osg::Vec3d( 1,0,0)).valid() );
    EXPECT_EQ( false, _right->getNeighbour(osg::Vec3d(-1,0,0)).valid() );
}

TEST_F(ShapeTransformTest, testUnbindEmpty)
{
    osg::ref_ptr<ShapeTransform> empty(new ShapeTransform(osg::ref_ptr<ShapeTransform::Faces>(new ShapeTransform::Faces)));
    empty->unbindNeighbour(osg::Vec3d(1,0,0));  // should not throw an exception
}

TEST_F(ShapeTransformTest, testBindNeighbourAllTransparent)
{
    _left->setTransparence(true);
    _right->setTransparence(true);
    _front->setTransparence(true);
    _left->bindNeighbour(_right);
    _left->bindNeighbour(_front);

    EXPECT_EQ( false, _left->isFaceHidden(osg::Vec3d( 1,0,0)) );
    EXPECT_EQ( false, _right->isFaceHidden(osg::Vec3d(-1,0,0)) );
    EXPECT_EQ( false, _left->isFaceHidden(osg::Vec3d(0, 1,0)) );
    EXPECT_EQ( false, _front->isFaceHidden(osg::Vec3d(0,-1,0)) );
}

TEST_F(ShapeTransformTest, testBindNeighbourOneTransparent)
{
    _left->setTransparence(true);
    _right->setTransparence(false);
    _front->setTransparence(false);
    _left->bindNeighbour(_right);
    _left->bindNeighbour(_front);

    EXPECT_EQ( false, _left->isFaceHidden(osg::Vec3d( 1,0,0)) );
    EXPECT_EQ( false, _right->isFaceHidden(osg::Vec3d(-1,0,0)) );
    EXPECT_EQ( false, _left->isFaceHidden(osg::Vec3d(0, 1,0)) );
    EXPECT_EQ( false, _front->isFaceHidden(osg::Vec3d(0,-1,0)) );
}

TEST_F(ShapeTransformTest, testBindNeighbourTransparentAfter)
{
    _left->bindNeighbour(_right);
    _left->bindNeighbour(_front);
    _left->setTransparence(true);

    EXPECT_EQ( false, _left->isFaceHidden(osg::Vec3d( 1,0,0)) );
    EXPECT_EQ( false, _right->isFaceHidden(osg::Vec3d(-1,0,0)) );
    EXPECT_EQ( false, _left->isFaceHidden(osg::Vec3d(0, 1,0)) );
    EXPECT_EQ( false, _front->isFaceHidden(osg::Vec3d(0,-1,0)) );
}

TEST_F(ShapeTransformTest, testBindNeighbourTransparentAfterReverse)
{
    _left->setTransparence(true);
    _left->bindNeighbour(_right);
    _left->bindNeighbour(_front);
    _left->setTransparence(false);

    EXPECT_EQ( true, _left->isFaceHidden(osg::Vec3d( 1,0,0)) );
    EXPECT_EQ( true, _right->isFaceHidden(osg::Vec3d(-1,0,0)) );
    EXPECT_EQ( true, _left->isFaceHidden(osg::Vec3d(0, 1,0)) );
    EXPECT_EQ( true, _front->isFaceHidden(osg::Vec3d(0,-1,0)) );
}

TEST_F(ShapeTransformTest, testBindNeighbourOneTransparentAfterReverse)
{
    _left->setTransparence(true);
    _right->setTransparence(true);
    _left->bindNeighbour(_right);
    _left->setTransparence(false);

    EXPECT_EQ( false, _left->isFaceHidden(osg::Vec3d( 1,0,0)) );
    EXPECT_EQ( false, _right->isFaceHidden(osg::Vec3d(-1,0,0)) );
}
