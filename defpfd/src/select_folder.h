#ifndef __SELECT_FOLDER_H__
#define __SELECT_FOLDER_H__

#include <dmsdk/sdk.h>
#include "portable-file-dialogs.h"

class Select_Folder
{
private:
    pfd::select_folder *select_folder;
    Select_Folder(pfd::select_folder *select_folder);
    static int ready(lua_State *L);
    static int kill(lua_State *L);
    static int result(lua_State *L);
public:
    static Select_Folder *create(lua_State *L);
    void push(lua_State *L);
};

#endif