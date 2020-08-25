#include "icon.h"

void Icon::push(lua_State *L)
{
    lua_newtable(L);

    lua_pushinteger(L, (int)pfd::icon::info);
    lua_setfield(L, -2, "info");
    lua_pushinteger(L, (int)pfd::icon::warning);
    lua_setfield(L, -2, "warning");
    lua_pushinteger(L, (int)pfd::icon::error);
    lua_setfield(L, -2, "error");
    lua_pushinteger(L, (int)pfd::icon::question);
    lua_setfield(L, -2, "question");

    lua_setfield(L, -2, "icon");
}