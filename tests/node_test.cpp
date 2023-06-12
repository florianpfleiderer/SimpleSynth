//
// Created by Florian Pfleiderer on 06.06.2023.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "Stk.h"
#include "../include/modules/EchoNode.h"
#include "../include/modules/DelayNode.h"
#include "../include/modules/SineOscillator.h"
#include "../include/modules/RectOscillator.h"
#include "../include/modules/SawOscillator.h"
#include "../include/modules/NoiseGenerator.h"
#include "../include/modules/Sweep.h"
#include "../include/modules/Output.h"
#include "../include/IdGenerator.h"
#include <iostream>

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
        REQUIRE(echoNode.getId() == 13);
        REQUIRE(echoNode.getConnections().size() == 2);
    }
}

IdGenerator::resetId();

// test member function of Sine Oscillator node
TEST_CASE("SineOscillator Node Test", "SineOscillator") {
    SineOscillator sineOscillator = SineOscillator();
    // std::cout << sineOscillator.getConnections().at(1).type << std::endl;
    SECTION("basic tests") {
        REQUIRE(sineOscillator.getName() == "SineOscillator");
        REQUIRE(sineOscillator.getId() == 1);
        REQUIRE(sineOscillator.getConnections().size() == 1);
        REQUIRE(sineOscillator.getConnections().at(0).type == OUTPUT);
    }
}

IdGenerator::resetId();

// test member function of Rect Oscillator node
TEST_CASE("RectOscillator Node Test", "RectOscillator") {
    RectOscillator rectOscillator = RectOscillator();

    SECTION("basic tests") {
        REQUIRE(rectOscillator.getName() == "RectOscillator");
        REQUIRE(rectOscillator.getId() == 1);
        REQUIRE(rectOscillator.getConnections().size() == 1);
        REQUIRE(rectOscillator.getConnections().at(0).type == OUTPUT);
    }
}

IdGenerator::resetId();

// test member function of Sweep node
TEST_CASE("Sweep Node Test", "Sweep") {
    Sweep sweep = Sweep();

    SECTION("basic tests") {
        REQUIRE(sweep.getName() == "Sweep");
        REQUIRE(sweep.getId() == 1);
        REQUIRE(sweep.getConnections().size() == 1);
        REQUIRE(sweep.getConnections().at(0).type == OUTPUT);
    }
}

IdGenerator::resetId();

// test member function of Noise Generator node
TEST_CASE("NoiseGenerator Node Test", "NoiseGenerator") {
    NoiseGenerator noiseGenerator = NoiseGenerator();

    SECTION("basic tests") {
        REQUIRE(noiseGenerator.getName() == "Noise");
        REQUIRE(noiseGenerator.getId() == 1);
        REQUIRE(noiseGenerator.getConnections().size() == 1);
        REQUIRE(noiseGenerator.getConnections().at(0).type == OUTPUT);
    }
}

IdGenerator::resetId();

// test member function of Output node
TEST_CASE("Output Node Test", "Output") {
    Output output = Output();

    SECTION("basic tests") {
        REQUIRE(output.getName() == "Output");
        REQUIRE(output.getId() == 1);
        REQUIRE(output.getConnections().size() == 1);
        REQUIRE(output.getConnections().at(0).type == INPUT);
    }
}


TEMPLATE_TEST_CASE( "test module.h functions in modules", "[nodes][template]", 
                    DelayNode, EchoNode, SineOscillator, RectOscillator, SawOscillator, NoiseGenerator, Output) {
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

TEMPLATE_TEST_CASE( "test output only nodes", "[output][template]", 
                    SineOscillator, RectOscillator, SawOscillator, NoiseGenerator) {
    // call default constructor for each type
    TestType test_type = TestType();

    SECTION( "test output connector") {
        REQUIRE(test_type.getConnections().size() == 1);
        REQUIRE(test_type.getConnections().at(0).type == ConnectorType::OUTPUT);
    }
}

TEMPLATE_TEST_CASE( "test input only nodes", "[input][template]", Output) {
    // call default constructor for each type
    TestType test_type = TestType();

    SECTION( "test output connector") {
        REQUIRE(test_type.getConnections().size() == 1);
        REQUIRE(test_type.getConnections().at(0).type == ConnectorType::INPUT);
    }
}

TEMPLATE_TEST_CASE( "test input output nodes", "[in-out][template]", 
                    DelayNode, EchoNode) {
    // call default constructor for each type
    TestType test_type = TestType();
    std::vector<ConnectorType> ctype = {ConnectorType::OUTPUT, ConnectorType::INPUT};

    SECTION( "test input output connector") {
        REQUIRE(test_type.getConnections().size() >= 2);
        REQUIRE(std::find(ctype.begin(), ctype.end(), test_type.getConnections().at(0).type) != ctype.end());
        REQUIRE(std::find(ctype.begin(), ctype.end(), test_type.getConnections().at(1).type) != ctype.end());
    }
}
