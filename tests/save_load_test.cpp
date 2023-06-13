//
// Created by Florian Pfleiderer on 06.06.2023.
//

#include <catch2/catch_test_macros.hpp>
#include "imgui.h"
#include "../include/modules/Module.h"
#include "../include/modules/Output.h"
#include "../include/modules/EchoNode.h"
#include "../include/modules/DelayNode.h"
#include "../include/modules/SineOscillator.h"
#include "../include/ModuleEditor.h"


TEST_CASE("Save and load test", "[save_load_test]") {
    auto out_ptr = std::make_shared<Output>(1, 2);
    auto echo_ptr = std::make_shared<EchoNode>(3, 4, 5, 6, 0);
    auto delay_ptr = std::make_shared<DelayNode>(7, 8, 9, 10, 0);
    auto sine_ptr = std::make_shared<SineOscillator>(11, 12, 440);

    std::vector<Connection> _connections;
    Connection c1(sine_ptr, 14, 12, 8);
    Connection c2(delay_ptr, 16, 9, 4);
    Connection c3(echo_ptr, 18, 5, 2);

    _connections.emplace_back(c1);
    _connections.emplace_back(c2);
    _connections.emplace_back(c3);

}