#include "message.h"
#include "LuaUtils.h"

Message::Message(pfd::message *message) : message(message) {}

Message *Message::create(lua_State *L)
{
    checkArgCount(L, 2, 4);
    int count = lua_gettop(L);

    checkString(L, 1);
    checkString(L, 2);
    if (count >= 3) checkNumber(L, 3);
    if (count >= 4) checkNumber(L, 4);

    const char *title = lua_tostring(L, 1);
    const char *text = lua_tostring(L, 2);
    int choice = 0;
    if (count >= 3) choice = lua_tointeger(L, 3);
    if (choice < 0 || choice > 5) choice = 0;
    int icon = 0;
    if (count >= 4) icon = lua_tointeger(L, 4);
    if (icon < 0 || icon > 3) icon = 0;

    pfd::message *message = new pfd::message(title, text, (pfd::choice)choice, (pfd::icon)icon);
    return new Message(message);
}

int Message::ready(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Message *message = (Message *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    int count = lua_gettop(L);
    int timeout = 20;
    if (count >= 2)
    {
        checkNumber(L, 2);
        int timeout = lua_tointeger(L, 2);
    }
    bool res = message->message->ready(timeout);
    lua_pushboolean(L, res);
    return 1;
}

int Message::kill(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Message *message = (Message *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    bool res = message->message->kill();
    lua_pushboolean(L, res);
    return 1;
}

int Message::result(lua_State *L)
{
    checkArgCount(L, 1, 2);
    checkTable(L, 1);

    lua_getfield(L, 1, "__userdata");
    if (!lua_islightuserdata(L, -1)) return 0;
    Message *message = (Message *)lua_touserdata(L, -1);
    lua_pop(L, 1);

    pfd::button res = message->message->result();
    lua_pushinteger(L, (int)res);
    return 1;
}

void Message::push(lua_State *L)
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