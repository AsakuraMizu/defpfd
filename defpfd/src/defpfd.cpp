#define LIB_NAME "defpfd"
#define MODULE_NAME LIB_NAME

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_LINUX) || defined(DM_PLATFORM_OSX) || defined(DM_PLATFORM_WINDOWS)

#include "button.h"
#include "choice.h"
#include "icon.h"
#include "opt.h"
#include "settings.h"

#include "message.h"
#include "notify.h"
#include "open_file.h"
#include "save_file.h"
#include "select_folder.h"

static int message(lua_State *L)
{
    Message *message = Message::create(L);
    message->push(L);
    return 1;
}

static int notify(lua_State *L)
{
    Notify *notify = Notify::create(L);
    notify->push(L);
    return 1;
}

static int open_file(lua_State *L)
{
    Open_File *open_file = Open_File::create(L);
    open_file->push(L);
    return 1;
}

static int save_file(lua_State *L)
{
    Save_File *save_file = Save_File::create(L);
    save_file->push(L);
    return 1;
}

static int select_folder(lua_State *L)
{
    Select_Folder *select_folder = Select_Folder::create(L);
    select_folder->push(L);
    return 1;
}

static const luaL_reg Module_methods[] =
{
    {"message", message},
    {"notify", notify},
    {"open_file", open_file},
    {"save_file", save_file},
    {"select_folder", select_folder},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    if (!pfd::settings::available())
        dmLogError("Portable File Dialogs are not available on this platform.");

    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    Settings::push(L);
    Button::push(L);
    Choice::push(L);
    Icon::push(L);
    Opt::push(L);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

#else

static const luaL_reg Module_methods[] =
{
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

#endif

dmExtension::Result InitializeDefpfd(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeDefpfd(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(defpfd, LIB_NAME, 0, 0, InitializeDefpfd, 0, 0, FinalizeDefpfd)