#ifndef __SAVE_FILE_H__
#define __SAVE_FILE_H__

#include <dmsdk/sdk.h>
#include "portable-file-dialogs.h"

class Save_File
{
private:
    pfd::save_file *save_file;
    Save_File(pfd::save_file *save_file);
    static int ready(lua_State *L);
    static int kill(lua_State *L);
    static int result(lua_State *L);
public:
    static Save_File *create(lua_State *L);
    void push(lua_State *L);
};

#endif