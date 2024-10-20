#include <iostream>
#include <lua.hpp>

int main(int argc, char** argv) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    std::cout << argv[0] << '\n';
    std::cout << argv[1] << '\n';

    int r = luaL_dofile(L, argv[1]);

    if (r == LUA_OK) {
        // ...
    } else {
        const char* error_msg = lua_tostring(L, -1);
        printf("%s\n", error_msg);
    }

    lua_close(L);
    return 0;
}