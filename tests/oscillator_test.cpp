#include <catch2/catch_test_macros.hpp>

// Demonstrate some basic assertions.
TEST_CASE("OsziTest", "[BasicAssertions]") {
  // Expect two strings not to be equal.
  REQUIRE(2 == 2);
}