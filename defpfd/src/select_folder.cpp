#include "select_folder.h"
#include "LuaUtils.h"

Select_Folder::Select_Folder(pfd::select_folder *select_folder) : select_folder(select_folder) {}

Select_Folder *Select_Folder::create(lua_State *L)
{
    checkArgCount(L, 1, 3);
    int count = lua_gettop(L);

    checkString(L, 1);
    if (count >= 2) checkString(L, 2);
    if (count >= 3) checkNumber(L, 3);

    const char *title = lua_tostring(L, 1);
    const char *default_path = "";
    if (count >= 2) default_path = lua_tostring(L, 2);
    int option = 0;
    if (count >= 3) option = lua_tointeger(L, 3);

    pfd::select_folder *select_folder = new pfd::select_folder(title, default_path, (pfd::opt)option);
    return new Select_Folder(select_folder);
}

int Select_Folder::ready(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Select_Folder *select_folder = (Select_Folder *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    int count = lua_gettop(L);
    int timeout = 20;
    if (count >= 2)
    {
        checkNumber(L, 2);
        int timeout = lua_tointeger(L, 2);
    }
    bool res = select_folder->select_folder->ready(timeout);
    lua_pushboolean(L, res);
    return 1;
}

int Select_Folder::kill(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Select_Folder *select_folder = (Select_Folder *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    bool res = select_folder->select_folder->kill();
    lua_pushboolean(L, res);
    return 1;
}

int Select_Folder::result(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Select_Folder *select_folder = (Select_Folder *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    std::string res = select_folder->select_folder->result();
    lua_pushstring(L, res.c_str());
    return 1;
}

void Select_Folder::push(lua_State *L)
{
    lua_newtable(L);

    lua_pushlightuserdata(L, this);
    lua_setfield(L, -2, "__userdata");
    lua_pushcfunction(L, ready);
    lua_setfield(L, -2, "ready");
    lua_pushcfunction(L, kill);
    lua_setfield(L, -2, "kill");
    lua_pushcfunction(L, result);
    lua_setfield(L, -2, "result");
}