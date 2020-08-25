#include "save_file.h"
#include "LuaUtils.h"

Save_File::Save_File(pfd::save_file *save_file) : save_file(save_file) {}

Save_File *Save_File::create(lua_State *L)
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

    pfd::save_file *save_file = new pfd::save_file(title, initial_path, filters, (pfd::opt)option);
    return new Save_File(save_file);
}

int Save_File::ready(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Save_File *save_file = (Save_File *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    int count = lua_gettop(L);
    int timeout = 20;
    if (count >= 2)
    {
        checkNumber(L, 2);
        int timeout = lua_tointeger(L, 2);
    }
    bool res = save_file->save_file->ready(timeout);
    lua_pushboolean(L, res);
    return 1;
}

int Save_File::kill(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Save_File *save_file = (Save_File *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    bool res = save_file->save_file->kill();
    lua_pushboolean(L, res);
    return 1;
}

int Save_File::result(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Save_File *save_file = (Save_File *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    std::string res = save_file->save_file->result();
    lua_pushstring(L, res.c_str());
    return 1;
}

void Save_File::push(lua_State *L)
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