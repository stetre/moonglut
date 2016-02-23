/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Stefano Trettel
 *
 * Software repository: MoonGLUT, https://github.com/stetre/moonglut
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/****************************************************************************
 * Menu stuff (see fg_menu.c)                                               *
 ****************************************************************************/

#include "internal.h"

#define L moonglut_L

void moonglut_callbacksMenuDestroy(void);

static void MenuDestroyCallback(void)
    {
    mnu_t *mnu = mnu_current(L);
    if(mnu->MenuDestroy != LUA_NOREF) /* execute user's callback */
        moonglut_callbacksMenuDestroy();
    mnu_free(mnu);
    }

#undef L

void moonglut_callbacksMenuCallback(int value);

static int CreateMenu(lua_State *L)
    {
    mnu_t *mnu;
    int id;
    if(!lua_isfunction(L, 1))
        return luaL_argerror(L, 1, "function expected");
    if((id = glutCreateMenu(moonglut_callbacksMenuCallback)) < 1)
        return luaL_error(L, "cannot create menu");
    if((mnu = mnu_new(id)) == NULL)
        return luaL_error(L, "cannot create menu");
    glutMenuDestroyFunc(MenuDestroyCallback);
    lua_pushvalue(L, 1);
    mnu->Callback = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_pushinteger(L, id);
    return 1;
    }

static int DestroyMenu(lua_State *L)
    {
    mnu_t *mnu;
    int id = luaL_checkinteger(L, 1);
    if((mnu = mnu_search(id)) == NULL)
        return luaL_argerror(L, 1, lua_pushfstring(L, "unknown menu %d", id));
    glutDestroyMenu(id);
    /* mnu_free(mnu); in the menu destroy callback */
    return 0;
    }

static int GetMenu(lua_State *L)
    {
    lua_pushinteger(L, glutGetMenu());
    return 1;
    }

static int SetMenu(lua_State *L)
    {
    int id = luaL_checkinteger(L, 1);
    glutSetMenu(id);
    if(mnu_search(id) == NULL)
        return luaL_argerror(L, 1, lua_pushfstring(L, "unknown menu %d", id));
    return 0;
    }

static int AddMenuEntry(lua_State *L) 
    {
    const char *label = luaL_checkstring(L, 1);
    int value = luaL_checkinteger(L, 2);
    glutAddMenuEntry(label, value);
    return 0;
    }

static int AddSubMenu(lua_State *L) 
    {
    const char *label = luaL_checkstring(L, 1);
    int submenu = luaL_checkinteger(L, 2);
    glutAddSubMenu(label,submenu);
    return 0;
    }

static int ChangeToMenuEntry(lua_State *L)
    {
    int item = luaL_checkinteger(L, 1);
    const char *label = luaL_checkstring(L, 2);
    int value = luaL_checkinteger(L, 3);
    glutChangeToMenuEntry(item, label, value);
    return 0;
    }

static int ChangeToSubMenu(lua_State *L) 
    {
    int item = luaL_checkinteger(L, 1);
    const char *label = luaL_checkstring(L, 2);
    int value = luaL_checkinteger(L, 3);
    glutChangeToSubMenu(item, label, value);
    return 0;
    }

static int RemoveMenuItem(lua_State *L) 
    {
    int item = luaL_checkinteger(L, 1);
    glutRemoveMenuItem(item);
    return 0;
    }

static const char* MenuStrings[] = { "left", "middle", "right", NULL };
static int MenuCodes[] = { GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON };

static int AttachMenu(lua_State *L)
    {
    int button = MenuCodes[checkoption(L, 1, NULL, MenuStrings)];
    glutAttachMenu(button);
    return 0;
    }

static int DetachMenu(lua_State *L)
    {
    int button = MenuCodes[checkoption(L, 1, NULL, MenuStrings)];
    glutDetachMenu(button);
    return 0;
    }

#if 0
void* moonglut_CheckBitmap(lua_State *L, int arg);
static int SetMenuFont(lua_State *L) /*@@*/
    {
    int id = luaL_checkinteger(L, 1);
    void *font = moonglut_CheckBitmap(L, 2);
    glutSetMenuFont(id, font);
    return 0;
    }
#endif


static int MenuNumItems(lua_State *L)
    {
    lua_pushinteger(L, glutGet(GLUT_MENU_NUM_ITEMS));
    return 1;
    }


static const struct luaL_Reg Functions[] = 
    {
        { "create_menu", CreateMenu },
        { "destroy_menu", DestroyMenu },
        { "get_menu", GetMenu },
        { "set_menu", SetMenu },
        { "add_menu_entry", AddMenuEntry },
        { "add_sub_menu", AddSubMenu },
        { "change_to_menu_entry", ChangeToMenuEntry },
        { "change_to_sub_menu", ChangeToSubMenu },
        { "remove_menu_item", RemoveMenuItem },
        { "attach_menu", AttachMenu },
        { "detach_menu", DetachMenu },
#if 0 
        { "set_menu_font", SetMenuFont },
#endif
        { "menu_num_items", MenuNumItems },
#if 0 
/* could have used these instead of mnu.c database... */
        { "GetMenuData", GetMenuData }, void* glutGetMenuData( void );
        { "SetMenuData", SetMenuData }, void glutSetMenuData(void* data);
#endif
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_menu(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

