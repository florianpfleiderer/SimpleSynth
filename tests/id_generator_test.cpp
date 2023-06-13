//
// Created by Florian Pfleiderer on 06.06.2023.
//

#include <catch2/catch_test_macros.hpp>
#include "../include/IdGenerator.h"

TEST_CASE("id generator test", "[id]") {

    SECTION("test static method") {
        REQUIRE(IdGenerator::generateId() == 1);
        REQUIRE(IdGenerator::generateId() == 2);
        REQUIRE(IdGenerator::generateId() == 3);
        REQUIRE(IdGenerator::generateId() == 4);
        REQUIRE(IdGenerator::generateId() == 5);
    }

    SECTION("test object method") {
        IdGenerator id_gen = IdGenerator();

        REQUIRE(id_gen.generateId() == 1);
        REQUIRE(id_gen.generateId() == 2);
        REQUIRE(id_gen.generateId() == 3);
        REQUIRE(IdGenerator::generateId() == 4);  
        REQUIRE(id_gen.generateId() == 5);      
    }
}