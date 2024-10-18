#include <iostream>
#include <lua.hpp>

lua_State* L = luaL_newstate();

int main() {
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
