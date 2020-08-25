#include "opt.h"

void Opt::push(lua_State *L)
{
    lua_newtable(L);

    lua_pushinteger(L, (int)pfd::opt::none);
    lua_setfield(L, -2, "none");
    lua_pushinteger(L, (int)pfd::opt::multiselect);
    lua_setfield(L, -2, "multiselect");
    lua_pushinteger(L, (int)pfd::opt::force_overwrite);
    lua_setfield(L, -2, "force_overwrite");
    lua_pushinteger(L, (int)pfd::opt::force_path);
    lua_setfield(L, -2, "force_path");

    lua_setfield(L, -2, "opt");
}