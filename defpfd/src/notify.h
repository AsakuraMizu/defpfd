#ifndef __NOTIFY_H__
#define __NOTIFY_H__

#include <dmsdk/sdk.h>
#include "portable-file-dialogs.h"

class Notify
{
private:
    pfd::notify *notify;
    Notify(pfd::notify *notify);
    static int ready(lua_State *L);
    static int kill(lua_State *L);
public:
    static Notify *create(lua_State *L);
    void push(lua_State *L);
};

#endif