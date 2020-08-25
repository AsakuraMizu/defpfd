#ifndef __OPEN_FILE_H__
#define __OPEN_FILE_H__

#include <dmsdk/sdk.h>
#include "portable-file-dialogs.h"

class Open_File
{
private:
    pfd::open_file *open_file;
    Open_File(pfd::open_file *open_file);
    static int ready(lua_State *L);
    static int kill(lua_State *L);
    static int result(lua_State *L);
public:
    static Open_File *create(lua_State *L);
    void push(lua_State *L);
};

#endif