#include "GameManager.h"

#if defined TEST
#include <gmock/gmock.h>
#endif

int main(int argc, char* argv[])
{
#if defined TEST

    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

#else

    (void) argc;
    (void) argv;
    srand(time(NULL));

    GameManager manager;

#endif
}
