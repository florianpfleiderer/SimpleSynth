#include <catch2/catch_test_macros.hpp>
#include "Stk.h"
#include "../include/modules/EchoNode.h"
#include "../include/modules/DelayNode.h"

// test member function of delay node
TEST_CASE("Set Delay Length", "DelayNode") {
    DelayNode delayNode = DelayNode();
    REQUIRE(delayNode.getDelayLength() == 0.0f);

    SECTION("change delay length") {
        delayNode.setDelayLength(100.0f);
        REQUIRE(delayNode.getDelayLength() == 100.0f);
    }

    SECTION("change delay length to negative value") {
        delayNode.setDelayLength(-1.0f);
        REQUIRE(delayNode.getDelayLength() == 0.0f);
    }
}


