#include "settings.h"
#include "LuaUtils.h"

int Settings::available(lua_State *L)
{
    bool res = pfd::settings::available();
    lua_pushboolean(L, res);
    return 1;
}

int Settings::verbose(lua_State *L)
{
    checkArgCount(L, 1);
    checkBoolean(L, 1);
    bool value = lua_toboolean(L, 1);
    pfd::settings::verbose(value);
    return 0;
}

int Settings::rescan(lua_State *L)
{
    pfd::settings::rescan();
    return 0;
}

void Settings::push(lua_State *L)
{
    lua_newtable(L);

    lua_pushcfunction(L, available);
    lua_setfield(L, -2, "available");
    lua_pushcfunction(L, verbose);
    lua_setfield(L, -2, "verbose");
    lua_pushcfunction(L, rescan);
    lua_setfield(L, -2, "rescan");

    lua_setfield(L, -2, "settings");
}