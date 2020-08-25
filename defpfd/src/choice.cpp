#include "choice.h"

void Choice::push(lua_State *L)
{
    lua_newtable(L);

    lua_pushinteger(L, (int)pfd::choice::ok);
    lua_setfield(L, -2, "ok");
    lua_pushinteger(L, (int)pfd::choice::ok_cancel);
    lua_setfield(L, -2, "ok_cancel");
    lua_pushinteger(L, (int)pfd::choice::yes_no);
    lua_setfield(L, -2, "yes_no");
    lua_pushinteger(L, (int)pfd::choice::yes_no_cancel);
    lua_setfield(L, -2, "yes_no_cancel");
    lua_pushinteger(L, (int)pfd::choice::retry_cancel);
    lua_setfield(L, -2, "retry_cancel");
    lua_pushinteger(L, (int)pfd::choice::abort_retry_ignore);
    lua_setfield(L, -2, "abort_retry_ignore");

    lua_setfield(L, -2, "choice");
}