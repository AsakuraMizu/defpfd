#include "notify.h"
#include "LuaUtils.h"

Notify::Notify(pfd::notify *notify) : notify(notify) {}

Notify *Notify::create(lua_State *L)
{
    checkArgCount(L, 2, 3);
    int count = lua_gettop(L);

    checkString(L, 1);
    checkString(L, 2);
    if (count >= 3) checkNumber(L, 3);

    const char *title = lua_tostring(L, 1);
    const char *text = lua_tostring(L, 2);
    int icon = 0;
    if (count >= 3) icon = lua_tointeger(L, 3);
    if (icon < 0 || icon > 3) icon = 0;

    pfd::notify *notify = new pfd::notify(title, text, (pfd::icon)icon);
    return new Notify(notify);
}

int Notify::ready(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Notify *notify = (Notify *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    int count = lua_gettop(L);
    int timeout = 20;
    if (count >= 2)
    {
        checkNumber(L, 2);
        int timeout = lua_tointeger(L, 2);
    }
    bool res = notify->notify->ready(timeout);
    lua_pushboolean(L, res);
    return 1;
}

int Notify::kill(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Notify *notify = (Notify *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    bool res = notify->notify->kill();
    lua_pushboolean(L, res);
    return 1;
}

void Notify::push(lua_State *L)
{
    lua_newtable(L);

    lua_pushlightuserdata(L, this);
    lua_setfield(L, -2, "__userdata");
    lua_pushcfunction(L, ready);
    lua_setfield(L, -2, "ready");
    lua_pushcfunction(L, kill);
    lua_setfield(L, -2, "kill");
}