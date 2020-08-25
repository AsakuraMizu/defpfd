#include "open_file.h"
#include "LuaUtils.h"

Open_File::Open_File(pfd::open_file *open_file) : open_file(open_file) {}

Open_File *Open_File::create(lua_State *L)
{
    checkArgCount(L, 2, 4);
    int count = lua_gettop(L);

    checkString(L, 1);
    checkString(L, 2);
    if (count >= 3) checkTable(L, 3);
    if (count >= 4) checkNumber(L, 4);

    const char *title = lua_tostring(L, 1);
    const char *initial_path = lua_tostring(L, 2);
    std::vector<std::string> filters = { "All Files", "*" };
    if (count >= 3)
    {
        filters.clear();
        int len = lua_objlen(L, 3);
        for (int i = 1; i <= len; ++i)
        {
            lua_pushinteger(L, i);
            lua_gettable(L, 3);
            checkString(L, -1);
            filters.push_back(lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }
    int option = 0;
    if (count >= 4) option = lua_tointeger(L, 4);

    pfd::open_file *open_file = new pfd::open_file(title, initial_path, filters, (pfd::opt)option);
    return new Open_File(open_file);
}

int Open_File::ready(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Open_File *open_file = (Open_File *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    int count = lua_gettop(L);
    int timeout = 20;
    if (count >= 2)
    {
        checkNumber(L, 2);
        int timeout = lua_tointeger(L, 2);
    }
    bool res = open_file->open_file->ready(timeout);
    lua_pushboolean(L, res);
    return 1;
}

int Open_File::kill(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Open_File *open_file = (Open_File *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    bool res = open_file->open_file->kill();
    lua_pushboolean(L, res);
    return 1;
}

int Open_File::result(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Open_File *open_file = (Open_File *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    std::vector<std::string> res = open_file->open_file->result();
    lua_newtable(L);
    for (int i = 0; i < res.size(); ++i)
    {
        lua_pushstring(L, res[i].c_str());
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

void Open_File::push(lua_State *L)
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