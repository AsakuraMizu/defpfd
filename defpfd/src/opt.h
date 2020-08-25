#ifndef __OPT_H__
#define __OPT_H__

#include <dmsdk/sdk.h>
#include "portable-file-dialogs.h"

class Opt
{
public:
    static void push(lua_State *L);
};

#endif