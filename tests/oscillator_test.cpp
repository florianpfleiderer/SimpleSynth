#include <catch2/catch_test_macros.hpp>
#include "Stk.h"
#include "../include/modules/SineOscillator.h"
#include "../include/modules/Oscillator.h"
#include "../include/modules/RectOscillator.h"

TEST_CASE("Sine Oscillator Test", "[SineOscillator]") {
  SineOscillator sineOscillator = SineOscillator();
  SECTION("Check default frequency") {
    REQUIRE(sineOscillator. == 440.0f);
  }

  REQUIRE(2 == 2);
}