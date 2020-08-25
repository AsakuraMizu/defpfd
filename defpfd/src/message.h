#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <dmsdk/sdk.h>
#include "portable-file-dialogs.h"

class Message
{
private:
    pfd::message *message;
    Message(pfd::message *message);
    static int ready(lua_State *L);
    static int kill(lua_State *L);
    static int result(lua_State *L);
public:
    static Message *create(lua_State *L);
    void push(lua_State *L);
};

#endif