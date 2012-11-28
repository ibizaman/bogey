#include <gtest/gtest.h>
#include "exception/BaseException.h"
#include <string>

class TestBaseException : public BaseException
{
public:
    TestBaseException(const std::string& elem = "") : BaseException(elem) {}
    const char* message() const {return "message";}
};

TEST(BaseExceptionTest, OutputWithParameter)
{
    std::string message = "ERROR message (30)";
    TestBaseException exception("30");
    EXPECT_EQ(message, exception.what());
}

TEST(BaseExceptionTest, OutputWithoutParameter)
{
    std::string message = "ERROR message";
    TestBaseException exception;
    EXPECT_EQ(message, exception.what());
}
