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
#include <iostream>
#include "../include/modules/Sequencer.h"

// test member function of delay node
TEST_CASE("Delay Node Test", "DelayNode") {
    DelayNode delayNode = DelayNode();

    SECTION("basic tests") {
        REQUIRE(delayNode.getName() == "Delay");
        REQUIRE(delayNode.getId() == 1);
        REQUIRE(delayNode.getDelayLength() == 0.0f);
        REQUIRE(delayNode.getConnectors().size() == 2);
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
    IdGenerator::resetId();
    EchoNode echoNode{};

    SECTION("basic tests") {
        REQUIRE(echoNode.getName() == "Echo");
        REQUIRE(echoNode.getId() == 1);
        REQUIRE(echoNode.getConnectors().size() == 2);
    }
}

// test member function of Sine Oscillator node
TEST_CASE("SineOscillator Node Test", "SineOscillator") {
    IdGenerator::resetId();
    SineOscillator sineOscillator = SineOscillator();
    // std::cout << sineOscillator.getConnectors().at(1).type << std::endl;
    SECTION("basic tests") {
        REQUIRE(sineOscillator.getName() == "SineOscillator");
        REQUIRE(sineOscillator.getId() == 1);
        REQUIRE(sineOscillator.getConnectors().size() == 1);
        REQUIRE(sineOscillator.getConnectors().at(0).type == ConnectorType::OUTPUT);
    }
}

// test member function of Rect Oscillator node
TEST_CASE("RectOscillator Node Test", "RectOscillator") {
    IdGenerator::resetId();
    RectOscillator rectOscillator = RectOscillator();

    SECTION("basic tests") {
        REQUIRE(rectOscillator.getName() == "RectOscillator");
        REQUIRE(rectOscillator.getId() == 1);
        REQUIRE(rectOscillator.getConnectors().size() == 1);
        REQUIRE(rectOscillator.getConnectors().at(0).type == ConnectorType::OUTPUT);
    }
}

// test member function of Sweep node
TEST_CASE("Sweep Node Test", "Sweep") {
    IdGenerator::resetId();
    Sweep sweep = Sweep();

    SECTION("basic tests") {
        REQUIRE(sweep.getName() == "Sweep");
        REQUIRE(sweep.getId() == 1);
        REQUIRE(sweep.getConnectors().size() == 1);
        REQUIRE(sweep.getConnectors().at(0).type == ConnectorType::OUTPUT);
    }
}

// test member function of Noise Generator node
TEST_CASE("NoiseGenerator Node Test", "NoiseGenerator") {
    IdGenerator::resetId();
    NoiseGenerator noiseGenerator = NoiseGenerator();

    SECTION("basic tests") {
        REQUIRE(noiseGenerator.getName() == "Noise");
        REQUIRE(noiseGenerator.getId() == 1);
        REQUIRE(noiseGenerator.getConnectors().size() == 1);
        REQUIRE(noiseGenerator.getConnectors().at(0).type == ConnectorType::OUTPUT);
    }
}

// test member function of Output node
TEST_CASE("Output Node Test", "Output") {
    IdGenerator::resetId();
    Output output = Output();

    SECTION("basic tests") {
        REQUIRE(output.getName() == "Output");
        REQUIRE(output.getId() == 1);
        REQUIRE(output.getConnectors().size() == 1);
        REQUIRE(output.getConnectors().at(0).type == ConnectorType::INPUT);
    }
}

// test member function of sequencer node
TEST_CASE("Sequencer Node Test", "Sequencer") {
    IdGenerator::resetId();
    Sequencer seqNode = Sequencer();

    SECTION("basic tests") {
        REQUIRE(seqNode.getName() == "Sequencer");
        REQUIRE(seqNode.getId() == 1);
    }
}


TEMPLATE_TEST_CASE( "test module.h functions in modules", "[nodes][template]", 
                    DelayNode, EchoNode, SineOscillator, RectOscillator, SawOscillator, Sweep, NoiseGenerator) {
    // call default constructor for each type
    TestType test_type = TestType();

    SECTION( "test default initialisation") {
        REQUIRE(test_type.getId() > 0);
        REQUIRE(test_type.getConnectors().size() > 0);
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
                    SineOscillator, RectOscillator, SawOscillator, Sweep, NoiseGenerator) {
    // call default constructor for each type
    TestType test_type = TestType();

    SECTION( "test output connector") {
        REQUIRE(test_type.getConnectors().size() == 1);
        REQUIRE(test_type.getConnectors().at(0).type == ConnectorType::OUTPUT);
    }
}

TEMPLATE_TEST_CASE( "test input only nodes", "[input][template]", Output) {
    // call default constructor for each type
    TestType test_type = TestType();

    SECTION( "test output connector") {
        REQUIRE(test_type.getConnectors().size() == 1);
        REQUIRE(test_type.getConnectors().at(0).type == ConnectorType::INPUT);
    }
}

TEMPLATE_TEST_CASE( "test input output nodes", "[in-out][template]", 
                    DelayNode, EchoNode) {
    // call default constructor for each type
    TestType test_type = TestType();
    std::vector<ConnectorType::ConnectorType> ctype = {ConnectorType::OUTPUT, ConnectorType::INPUT};

    SECTION( "test input output connector") {
        REQUIRE(test_type.getConnectors().size() >= 2);
        //REQUIRE(std::find(ctype.begin(), ctype.end(), test_type.getConnectors().at(0).type) != ctype.end());
        //REQUIRE(std::find(ctype.begin(), ctype.end(), test_type.getConnectors().at(1).type) != ctype.end());
    }
}
