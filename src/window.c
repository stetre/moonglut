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
 * Window management functions (see fg_window.c)                            *
 ****************************************************************************/

#include "internal.h"

static const char* ActionStrings[] = { "exit", "return", "continue", NULL };
static int ActionCodes[] = { 
    GLUT_ACTION_EXIT, GLUT_ACTION_GLUTMAINLOOP_RETURNS, GLUT_ACTION_CONTINUE_EXECUTION };

static int ActionOnWindowClose(lua_State *L) 
    {
    int val, i, n;
    if(!lua_isnoneornil(L, 1))
        {
        val = ActionCodes[checkoption(L, 1, NULL, ActionStrings)];
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, val);
        }
    n = sizeof(ActionCodes)/sizeof(ActionCodes[0]);
    val = glutGet(GLUT_ACTION_ON_WINDOW_CLOSE);
    for(i = 0; i <n; i ++)
        {
        if(val == ActionCodes[i])
            { lua_pushstring(L, ActionStrings[i]); return 1; }
        }
    lua_pushstring(L, "????");
    return 1;
    }

static int InitWindowPosition(lua_State *L) 
    {
    int x, y;
    if(!lua_isnoneornil(L, 1))
        {
        x = luaL_checkinteger(L, 1);
        y = luaL_checkinteger(L, 2);
        glutInitWindowPosition(x, y);
        }
    lua_pushinteger(L, glutGet(GLUT_INIT_WINDOW_X));
    lua_pushinteger(L, glutGet(GLUT_INIT_WINDOW_Y));
    return 2;
    }
 
static int InitWindowSize(lua_State *L) 
    {
    int width, height;
    if(!lua_isnoneornil(L, 1))
        {
        width = luaL_checkinteger(L, 1);
        height = luaL_checkinteger(L, 2);
        glutInitWindowSize(width, height);
        }
    lua_pushinteger(L, glutGet(GLUT_INIT_WINDOW_WIDTH));
    lua_pushinteger(L, glutGet(GLUT_INIT_WINDOW_HEIGHT));
    return 2;
    }

#define L moonglut_L
void windowCloseCallback(void)
/* This callback is always registered for windows and subwindows.
 * It calls the user's Lua callback (if registered) and releases
 * the window entry in the win.c database.
 */
    {
    win_t *win = win_current(L);
/*  printf("windowCloseCallback %d\n", win->id); */
    if(win->Close != LUA_NOREF) /* execute user's callback */
        moonglut_callbacksClose();
    win_free(win);
    }
#undef L


#if 0
int windowEnterGameMode(lua_State *L)
    {
    int id;
    win_t *win;
    const char *title = NULL;
    if(lua_isstring(L, 1))
        title = lua_tostring(L, 1);
    if((id = glutCreateWindow(title)) < 1)
        return luaL_error(L, "cannot create window");
    if((win = win_new(id, 0)) == NULL)
        return luaL_error(L, "cannot create window");
    glutCloseFunc(windowCloseCallback);
    lua_pushinteger(L, id);
    return 1;
    }
#endif

static int CreateWindowXXX(lua_State *L)
    {
    int id;
    win_t *win;
    const char *title = NULL;
    if(lua_isstring(L, 1))
        title = lua_tostring(L, 1);
    if((id = glutCreateWindow(title)) < 1)
        return luaL_error(L, "cannot create window");
    if((win = win_new(id, 0)) == NULL)
        return luaL_error(L, "cannot create window");
    glutCloseFunc(windowCloseCallback);
    lua_pushinteger(L, id);
    return 1;
    }

static int CreateSubWindow(lua_State *L) 
    {
    int id;
    win_t *win;
    int parent = luaL_checkinteger(L, 1);
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    int width = luaL_checkinteger(L, 4);
    int height = luaL_checkinteger(L, 5);
    if(win_search(parent) == NULL)
        return luaL_argerror(L, 1, lua_pushfstring(L, "unknown window %d", parent));
    if((id = glutCreateSubWindow(parent, x, y, width, height)) < 1)
        return luaL_error(L, "cannot create sub window");
    if((win = win_new(id, parent)) == NULL)
        return luaL_error(L, "cannot create sub window");
    glutCloseFunc(windowCloseCallback);
    lua_pushinteger(L, id);
    return 1;
    }

static int DestroyWindowXXX(lua_State *L)
    {
    int id = luaL_checkinteger(L, 1);
    if(win_search(id) == NULL)
        return luaL_argerror(L, 1, lua_pushfstring(L, "unknown window %d", id));
    glutDestroyWindow(id);  
    return 0;
    }

static int SetWindow(lua_State *L)
    {
    int id = luaL_checkinteger(L, 1);
    if(win_search(id) != NULL)
        return luaL_argerror(L, 1, lua_pushfstring(L, "unknown window %d", id));
    glutSetWindow(id);
    return 0;
    }

static int GetWindowXXX(lua_State *L)
    {
    lua_pushinteger(L, glutGetWindow());
    return 1;
    }

static int SetWindowTitle(lua_State *L)
    {
    const char *title = luaL_checkstring(L, 1);
    glutSetWindowTitle(title);
    return 0;
    }

static int SetIconTitle(lua_State *L) 
    {
    const char *title = luaL_checkstring(L, 1);
    glutSetIconTitle(title);
    return 0;
    }

static int ReshapeWindow(lua_State *L) 
    {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    glutReshapeWindow(width, height);
    return 0;
    }

static int PositionWindow(lua_State *L) 
    {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    glutPositionWindow(x, y);
    return 0;
    }

#if defined(DEBUG)
#define PRINT(func) do { printf(""#func"(%d)\n", glutGetWindow()); } while(0)
#else
#define PRINT(func) do { } while(0)
#endif

/* Simple functions with no arguments */
#define FUNCTION(func)          \
static int func##XXX(lua_State *L)   \
    {                           \
    (void)L; /* unused */       \
    PRINT(func);                \
    glut##func();               \
    return 0;                   \
    }

FUNCTION(ShowWindow)
FUNCTION(HideWindow)
FUNCTION(IconifyWindow)
FUNCTION(PushWindow)
FUNCTION(PopWindow)

static int WindowParent(lua_State *L)
    {
    lua_pushinteger(L, glutGet(GLUT_WINDOW_PARENT));
    return 1;
    }

static int WindowNumChildren(lua_State *L)
    {
    lua_pushinteger(L, glutGet(GLUT_WINDOW_NUM_CHILDREN));
    return 1;
    }

FUNCTION(FullScreenToggle)

static int FullScreen(lua_State *L)
    {
    if(!lua_isnoneornil(L,1))
        {
        if(!lua_isboolean(L,1))
            return luaL_argerror(L, 1, "boolean expected");
        if(lua_toboolean(L, 1))
            glutFullScreen();
        else
            glutLeaveFullScreen();
        }
/* Uhm... is this a bug in freeglut fg_state.c? (unchecked pointer)    
case GLUT_FULL_SCREEN:      return fgStructure.CurrentWindow->State.IsFullscreen;
*/
    lua_pushboolean(L, glutGet(GLUT_FULL_SCREEN) == GL_TRUE);
    return 1;
    }

#undef FUNCTION

#ifdef GLUT_GEOMETRY_VISUALIZE_NORMALS
static int GeometryVisualizeNormals(lua_State *L)
    {
    int val;
    if(!lua_isnoneornil(L, 1))
        {
        val = checkboolean(L, 1);
        glutSetOption(GLUT_GEOMETRY_VISUALIZE_NORMALS, val);
        }
    lua_pushboolean(L, glutGet(GLUT_GEOMETRY_VISUALIZE_NORMALS) == GL_TRUE);
    return 1;
    }
#endif

static const struct luaL_Reg Functions[] = 
    {
        { "init_window_position", InitWindowPosition },
        { "init_window_size", InitWindowSize },
        { "action_on_window_close", ActionOnWindowClose },
        { "create_window", CreateWindowXXX },
        { "create_sub_window", CreateSubWindow },
        { "destroy_window", DestroyWindowXXX },
        { "set_window", SetWindow },
        { "get_window", GetWindowXXX },
        { "set_window_title", SetWindowTitle },
        { "set_icon_title", SetIconTitle },
        { "reshape_window", ReshapeWindow },
        { "position_window", PositionWindow },
        { "show_window", ShowWindowXXX },
        { "hide_window", HideWindowXXX },
        { "iconify_window", IconifyWindowXXX },
        { "push_window", PushWindowXXX },
        { "pop_window", PopWindowXXX },
        { "full_screen_toggle", FullScreenToggleXXX },
#if 0 /* could have used these instead of win.c database... */
        { "GetWindowData", GetWindowData }, void* glutGetWindowData( void );
        { "SetWindowData", SetWindowData }, void  glutSetWindowData(void* data);
#endif
        { "window_parent", WindowParent },
        { "window_num_children", WindowNumChildren },
        { "full_screen", FullScreen },
#ifdef GLUT_GEOMETRY_VISUALIZE_NORMALS
        { "geometry_visualize_normals", GeometryVisualizeNormals },
#endif
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_window(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

