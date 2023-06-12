//
// Created by Florian Pfleiderer on 06.06.2023.
//

#include <catch2/catch_test_macros.hpp>
#include "../include/modules/Output.h"
#include "../include/modules/EchoNode.h"
#include "../include/modules/DelayNode.h"
#include "../include/modules/SineOscillator.h"
#include "../include/ModuleEditor.h"


TEST_CASE("Save and load test", "[save_load_test]") {
    Output out = Output(1, 2);
    EchoNode echo = EchoNode(3, 4, 5, 6, 0);
    DelayNode delay = DelayNode(7, 8, 9, 10, 0);
    SineOscillator sine = SineOscillator(11, 12, 440);

    std::vector<Connection> _connections;
    Connection c1 = Connection(std::make_shared<Module>(sine), 14, 12, 8);
    Connection c2 = Connection(std::make_shared<Module>(delay), 16, 9, 4);
    Connection c3 = Connection(std::make_shared<Module>(echo), 18, 5, 2);

    _connections.push_back(c1);
    _connections.push_back(c2);
    _connections.push_back(c3);

    ModuleEditor editor;
    editor.load("save_test.txt");
}