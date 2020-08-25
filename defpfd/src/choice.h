#ifndef __CHOICE_H__
#define __CHOICE_H__

#include <dmsdk/sdk.h>
#include "portable-file-dialogs.h"

class Choice
{
public:
    static void push(lua_State *L);
};

#endif