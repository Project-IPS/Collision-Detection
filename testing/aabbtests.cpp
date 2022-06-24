#include <catch2/catch_test_macros.hpp>
#include "aabb.hpp"

TEST_CASE( "aabbs", "[aabb]" ) {
    vec2 min = vec2(-1.0, -1.0 );
    vec2 max = vec2(1.0, 1.0);
    AABB testaabb = AABB(min, max);

    REQUIRE(testaabb.min.x == min.x + 1);
    REQUIRE(testaabb.min.y == min.y); 
    
}
