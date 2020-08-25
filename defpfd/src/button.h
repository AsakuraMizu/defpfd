#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <dmsdk/sdk.h>
#include "portable-file-dialogs.h"

class Button
{
public:
    static void push(lua_State *L);
};

#endif