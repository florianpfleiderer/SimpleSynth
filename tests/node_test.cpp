#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "Stk.h"
#include "../include/modules/EchoNode.h"
#include "../include/modules/DelayNode.h"
#include "../include/modules/SineOscillator.h"
#include "../include/modules/RectOscillator.h"

TEMPLATE_TEST_CASE( "test module.h functions in modules", "[nodes][template]", 
                    DelayNode, EchoNode, SineOscillator, RectOscillator) {
    // call default constructor for each type
    TestType test_type = TestType();

    SECTION( "test default initialisation") {
        REQUIRE(test_type.getId() > 0);
        REQUIRE(test_type.getConnections().size() > 0);
    }

    SECTION("test tick") {
        stk::StkFrames frames;
        frames.resize(10, 1);
        double streamTime = 0.0;
        int output_id = 2;
        REQUIRE(test_type.tick(frames, streamTime, output_id) == true);
    }
}

// test member function of delay node
TEST_CASE("Delay Node Test", "DelayNode") {
    DelayNode delayNode = DelayNode();

    SECTION("basic tests") {
        REQUIRE(delayNode.getName() == "Delay");
        REQUIRE(delayNode.getId() == 1);
        REQUIRE(delayNode.getDelayLength() == 0.0f);
        REQUIRE(delayNode.getConnections().size() == 2);
    }
    SECTION("change delay length") {
        delayNode.setDelayLength(100.0f);
        REQUIRE(delayNode.getDelayLength() == 100.0f);
    }

    SECTION("change delay length to negative value") {
        delayNode.setDelayLength(-1.0f);
        REQUIRE(delayNode.getDelayLength() == 0.0f);
    }
}

// test member function of echo node
TEST_CASE("Echo Node Test", "EchoNode") {
    EchoNode echoNode = EchoNode();

    SECTION("basic tests") {
        REQUIRE(echoNode.getName() == "Echo");
        REQUIRE(echoNode.getId() == 1);
        REQUIRE(echoNode.getConnections().size() == 2);
    }
}

// test member function of Sine Oscillator node
TEST_CASE("SineOscillator Node Test", "SineOscillator") {
    SineOscillator sineOscillator = SineOscillator();

    SECTION("basic tests") {
        REQUIRE(sineOscillator.getName() == "SineOscillator");
        REQUIRE(sineOscillator.getId() == 1);
        REQUIRE(sineOscillator.getConnections().size() == 1);
    }
}