#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <dmsdk/sdk.h>
#include "portable-file-dialogs.h"

class Settings
{
private:
    static int available(lua_State *L);
    static int verbose(lua_State *L);
    static int rescan(lua_State *L);
public:
    static void push(lua_State *L);
};

#endif