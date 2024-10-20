#include <iostream>
#include <lua.hpp>

#include "SpiceComponent.hpp"
#include "SpiceEngine.hpp"

using namespace spice;

#if 1
int main() {
    std::vector<Net> netlist({
        Net({1, 3, 4}),
        Net({0, 2}),
        Net({1, 3, 4}),
        Net({0, 2, 4}),
        Net({0, 2, 3}),
    });

    SpiceEngine engine;
    auto cycles = engine.netlist_cycles(netlist);

    for (auto& x : cycles) {
        for (auto y : x)
            std::cout << y << '-';
        std::cout << x[0];
        std::cout << '\n';
    }

    return 0;
}
#else
int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    const char* s = "a = 9 + 10 + math.cos(45*math.pi/180)";

    int r = luaL_dostring(L, s);

    if (r == LUA_OK) {
        lua_getglobal(L, "a");

        if (lua_isnumber(L, -1)) {
            float float32 = (float)lua_tonumber(L, -1);
            printf("result: %f\n", float32);
        }
    } else {
        const char* error_msg = lua_tostring(L, -1);
        printf("%s\n", error_msg);
    }

    lua_close(L);
    return 0;
}
#endif
