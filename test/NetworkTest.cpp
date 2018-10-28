#include "catch.hpp"


TEST_CASE("First test", "[multi-file:2]") {
    REQUIRE(true);
}
TEST_CASE("Second test", "[multi-file:2]") {
    REQUIRE(false);
}
