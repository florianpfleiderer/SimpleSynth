//
// Created by Florian Pfleiderer on 06.06.2023.
//

#include <catch2/catch_test_macros.hpp>
#include "imnodes.h"
#include "../include/ModuleEditor.h"

TEST_CASE("Save and load test", "[save_load_test]") {
    ModuleEditor editor;
    
    SECTION("test load function") {
        editor.load("save_test");

        REQUIRE(editor.get_modules().size() == 4);
        REQUIRE(editor.get_connections().size() == 3);
    }
}