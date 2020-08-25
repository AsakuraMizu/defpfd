#include "button.h"

void Button::push(lua_State *L)
{
    lua_newtable(L);

    lua_pushinteger(L, (int)pfd::button::cancel);
    lua_setfield(L, -2, "cancel");
    lua_pushinteger(L, (int)pfd::button::ok);
    lua_setfield(L, -2, "ok");
    lua_pushinteger(L, (int)pfd::button::yes);
    lua_setfield(L, -2, "yes");
    lua_pushinteger(L, (int)pfd::button::no);
    lua_setfield(L, -2, "no");
    lua_pushinteger(L, (int)pfd::button::abort);
    lua_setfield(L, -2, "abort");
    lua_pushinteger(L, (int)pfd::button::retry);
    lua_setfield(L, -2, "retry");
    lua_pushinteger(L, (int)pfd::button::ignore);
    lua_setfield(L, -2, "ignore");

    lua_setfield(L, -2, "button");
}