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
 * Callback functions                                                       *
 ****************************************************************************/
#include "internal.h"

/*--------------------------------------------------------------------------*
 | Global callbacks execution                                               |
 *--------------------------------------------------------------------------*/

#define L moonglut_L

#define BEGIN(cb)  /* retrieve the callback */                      \
    int top = lua_gettop(L);                                        \
do {                                                                \
    if(lua_rawgeti(L, LUA_REGISTRYINDEX, cb) != LUA_TFUNCTION)      \
        { luaL_error(L, UNEXPECTED_ERROR); return; }                \
} while(0)

#define EXEC(nargs)  do {                                               \
    if(lua_pcall(L, (nargs), 0, 0) != LUA_OK) { lua_error(L); return; } \
    lua_settop(L, top);                                                 \
} while(0)

static int InitError = LUA_NOREF;
static void InitErrorCallback(const char *fmt, va_list ap)
    {
    BEGIN(InitError);
    lua_pushvfstring(L, fmt, ap);
    EXEC(1);
    }


static int InitWarning = LUA_NOREF;
static void InitWarningCallback(const char *fmt, va_list ap)
    {
    BEGIN(InitWarning);
    lua_pushvfstring(L, fmt, ap);
    EXEC(1);
    }


static int Idle = LUA_NOREF;
static void IdleCallback(void)
    {
    BEGIN(Idle);
    /* pass the current window and menu identifiers: */
    lua_pushinteger(L, glutGetWindow());
    lua_pushinteger(L, glutGetMenu());
    EXEC(2);
    }


static int MenuStatus = LUA_NOREF;
static void MenuStatusCallback(int status, int x, int y)
    {
    BEGIN(MenuStatus);
    switch(status)
        {
        case GLUT_MENU_NOT_IN_USE: lua_pushstring(L, "not in use"); break;
        case GLUT_MENU_IN_USE: lua_pushstring(L, "in use"); break;
        default:
            luaL_error(L, UNEXPECTED_ERROR);
        }
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    EXEC(3);
    }

/* MOBILE FUNCTIONS -----------------------------------------------*/

#ifdef MOONGLUT_MOBILE
static int InitContext = LUA_NOREF;
static void InitContextCallback(void)
    {
    BEGIN(InitContext);
    EXEC(0);
    }

static int AppStatus = LUA_NOREF;
static void AppStatusCallback(int event)
    {
    BEGIN(AppStatus);
    lua_pushinteger(L, event);
    EXEC(1);
    }
#endif


#undef BEGIN
#undef EXEC
#undef L

/*--------------------------------------------------------------------------*
 | Global callbacks registration                                            |
 *--------------------------------------------------------------------------*/

#define REGISTER(cb, func_index) do {               \
    if(!lua_isfunction(L, func_index))              \
        return luaL_error(L, "bad argument #%d (function expected)", func_index);\
    if(cb != LUA_NOREF)                             \
        luaL_unref(L, LUA_REGISTRYINDEX, cb);       \
    lua_pushvalue(L, func_index);                   \
    cb = luaL_ref(L, LUA_REGISTRYINDEX);            \
} while (0)


static int InitErrorFunc(lua_State *L)
    {
    REGISTER(InitError,1);
    glutInitErrorFunc(InitErrorCallback);
    return 0;
    }

static int InitWarningFunc(lua_State *L)
    {
    REGISTER(InitWarning,1);
    glutInitWarningFunc(InitWarningCallback);
    return 0;
    }

static int IdleFunc(lua_State *L)
    {
    REGISTER(Idle,1);
    glutIdleFunc(IdleCallback);
    return 0;
    }

static int MenuStatusFunc(lua_State *L)
    {
    REGISTER(MenuStatus, 1);
    glutMenuStatusFunc(MenuStatusCallback);
    return 0;
    }


/* MOBILE FUNCTIONS -----------------------------------------------*/


#ifdef MOONGLUT_MOBILE 
static int InitContextFunc(lua_State *L)
    {
    REGISTER(InitContext,1);
    glutInitContextFunc(InitContextCallback);
    return 0;
    }

static int AppStatusFunc(lua_State *L)
    {
    REGISTER(AppStatus,1);
    glutAppStatusFunc(AppStatusCallback);
    return 0;
    }
#endif

#undef REGISTER

/*--------------------------------------------------------------------------*
 | Window-specific callbacks execution                                      |
 *--------------------------------------------------------------------------*/

#define L moonglut_L

#define BEGIN(cb)  /* retrieve the callback */                      \
    int top = lua_gettop(L);                                        \
    int id = glutGetWindow();                                       \
do {                                                                \
    win_t *win = win_current(L);                                    \
    if(lua_rawgeti(L, LUA_REGISTRYINDEX, win->cb) != LUA_TFUNCTION) \
        { luaL_error(L, UNEXPECTED_ERROR); return; }                \
    lua_pushinteger(L, id);                                         \
} while(0)

#define EXEC(nargs)  do {                                               \
    if(lua_pcall(L, (nargs) + 1, 0, 0) != LUA_OK) { lua_error(L); return; } \
    lua_settop(L, top);                                                 \
} while(0)

#define RETURN do {                                                     \
    lua_settop(L, top); return;                                         \
} while(0)

static void DisplayCallback(void)
    {
    BEGIN(Display);
    EXEC(0);
    }

static void CloseCallback(void) { } /* dummy */

void moonglut_callbacksClose(void)
    {
    BEGIN(Close);
    EXEC(0);
    }

static void ReshapeCallback(int width, int height)
    {
    BEGIN(Reshape);
    lua_pushinteger(L, width);
    lua_pushinteger(L, height);
    EXEC(2);
    }

static void KeyboardCallback(unsigned char key, int x, int y)
    {
    BEGIN(Keyboard);
    pushkey(L, key); 
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    lua_pushinteger(L, key);
    EXEC(4);
    }

static void KeyboardUpCallback(unsigned char key, int x, int y)
    {
    BEGIN(KeyboardUp);
    pushkey(L, key);
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    lua_pushinteger(L, key);
    EXEC(4);
    }

static void SpecialCallback(int key, int x, int y)
    {
    BEGIN(Special);
    pushspecial(L, key);
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    lua_pushinteger(L, key);
    EXEC(4);
    }

static void SpecialUpCallback(int key, int x, int y)
    {
    BEGIN(SpecialUp);
    pushspecial(L, key);
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    lua_pushinteger(L, key);
    EXEC(4);
    }

static void MouseCallback(int button, int state, int x, int y)
    {
    BEGIN(Mouse);
    switch(button)
        {
        case GLUT_LEFT_BUTTON: lua_pushstring(L, "left"); break;
        case GLUT_MIDDLE_BUTTON: lua_pushstring(L, "middle"); break;
        case GLUT_RIGHT_BUTTON: lua_pushstring(L, "right"); break;
        default:
            lua_pushfstring(L, "mouse%d", button); break; /* wheel event? */
        }
    switch(state)
        {
        case GLUT_UP: lua_pushstring(L, "up"); break;
        case GLUT_DOWN: lua_pushstring(L, "down"); break;
        default:
            luaL_error(L, UNEXPECTED_ERROR); return;
        }
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    EXEC(4);
    }

static void MouseWheelCallback(int wheel, int direction, int x, int y)
    {
    BEGIN(MouseWheel);
    lua_pushinteger(L, wheel);
    lua_pushinteger(L, direction);
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    EXEC(4);
    }

static void WindowStatusCallback(int state)
    {
    BEGIN(WindowStatus);
    switch(state)
        {
        case GLUT_HIDDEN: lua_pushstring(L, "hidden"); break;
        case GLUT_FULLY_RETAINED: lua_pushstring(L, "fully retained"); break;
        case GLUT_PARTIALLY_RETAINED: lua_pushstring(L, "partially retained"); break;
        case GLUT_FULLY_COVERED: lua_pushstring(L, "fully covered"); break;
        default:
            luaL_error(L, UNEXPECTED_ERROR); return;
        }
    EXEC(1);
    }

static void MotionCallback(int x, int y)
    {
    BEGIN(Motion);
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    EXEC(2);
    }

static void PassiveMotionCallback(int x, int y)
    {
    BEGIN(PassiveMotion);
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    EXEC(2);
    }

static void EntryCallback(int state)
    {
    BEGIN(Entry);
    switch(state)
        {
        case GLUT_LEFT: lua_pushstring(L, "out"); break;
        case GLUT_ENTERED: lua_pushstring(L, "in"); break;
        default:
            luaL_error(L, UNEXPECTED_ERROR); return;
        }
    EXEC(1);
    }


#if 0
static void Callback(void)
    {
    BEGIN();
    EXEC(0);
    }

static void PositionCallback(int x, int y)
    {
    BEGIN(Position);
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    EXEC(2);
    }
#endif

#undef BEGIN
#undef EXEC
#undef L

/*--------------------------------------------------------------------------*
 | Window-specific callbacks registration                                   |
 *--------------------------------------------------------------------------*/

#define REGISTER_FUNC(cb, register_in_glut)             \
static int cb##Func(lua_State *L)                       \
    {                                                   \
    win_t *win = win_current(L);                        \
    if((lua_isnoneornil(L, 1)))                         \
        { /* unregister callback */                     \
        if(win->cb == LUA_NOREF) return 0; /* nothing to do */  \
        CALLBACK_UNREF(win->cb);                        \
        if(register_in_glut)                            \
            glut##cb##Func(NULL);                       \
        return 0;                                       \
        }                                               \
    if(!lua_isfunction(L, 1))                           \
        return luaL_error(L, "bad argument #%d (function expected)", 1);\
    if(win->cb != LUA_NOREF)                            \
        luaL_unref(L, LUA_REGISTRYINDEX, win->cb);      \
    lua_pushvalue(L, 1);                                \
    win->cb = luaL_ref(L, LUA_REGISTRYINDEX);           \
    if(register_in_glut)                                \
        glut##cb##Func(cb##Callback);                   \
    return 0;                                           \
    }


REGISTER_FUNC(Display, 1)
REGISTER_FUNC(Close, 0)
REGISTER_FUNC(Reshape, 1)
REGISTER_FUNC(Keyboard, 1)
REGISTER_FUNC(KeyboardUp, 1)
REGISTER_FUNC(Special, 1)
REGISTER_FUNC(SpecialUp, 1)
REGISTER_FUNC(Mouse, 1)
REGISTER_FUNC(MouseWheel, 1) /*@@ not working... why? */
REGISTER_FUNC(WindowStatus, 1)
REGISTER_FUNC(Motion, 1)
REGISTER_FUNC(PassiveMotion, 1)
REGISTER_FUNC(Entry, 1)

#if 0
REGISTER_FUNC(Position, 1, 0)
#endif

#undef REGISTER_FUNC

/*--------------------------------------------------------------------------*
 | Menu-specific callbacks execution                                        |
 *--------------------------------------------------------------------------*/

#define L moonglut_L

#define BEGIN(cb)  /* retrieve the callback */                      \
    int top = lua_gettop(L);                                        \
    int wid = glutGetWindow();                                      \
    int mid = glutGetMenu();                                        \
do {                                                                \
    mnu_t *mnu = mnu_current(L);                                    \
    if(lua_rawgeti(L, LUA_REGISTRYINDEX, mnu->cb) != LUA_TFUNCTION) \
        { luaL_error(L, UNEXPECTED_ERROR); return; }                \
    lua_pushinteger(L, wid);                                        \
    lua_pushinteger(L, mid);                                        \
} while(0)

#define EXEC(nargs)  do {                                               \
    if(lua_pcall(L, (nargs) + 2, 0, 0) != LUA_OK) { lua_error(L); return; } \
    lua_settop(L, top);                                                 \
} while(0)

#define RETURN do {                                                     \
    lua_settop(L, top); return;                                         \
} while(0)

void moonglut_callbacksMenuDestroy(void)
    {
    BEGIN(MenuDestroy);
    EXEC(0);
    }

void moonglut_callbacksMenuCallback(int value)
    {
    BEGIN(Callback);
    lua_pushinteger(L, value);
    EXEC(1);
    }

#undef BEGIN
#undef EXEC
#undef L

/*--------------------------------------------------------------------------*
 | Menu-specific callbacks registration                                     |
 *--------------------------------------------------------------------------*/

#define REGISTER(cb, func_index) do {                   \
    mnu_t *mnu = mnu_current(L);                        \
    if(!lua_isfunction(L, func_index))                  \
        return luaL_error(L, "bad argument #%d (function expected)", func_index);\
    if(mnu->cb != LUA_NOREF)                            \
        luaL_unref(L, LUA_REGISTRYINDEX, mnu->cb);      \
    lua_pushvalue(L, func_index);                       \
    mnu->cb = luaL_ref(L, LUA_REGISTRYINDEX);           \
} while (0)

static int MenuDestroyFunc(lua_State *L)
    {
    REGISTER(MenuDestroy,1);
/*  glutMenuDestroyFunc() is already called at menu creation (see menu.c) */
    return 0;
    }


#undef REGISTER

/*--------------------------------------------------------------------------*
 | Timers                                                                   |
 *--------------------------------------------------------------------------*/

#define L moonglut_L

static void TimerCallback(int id)
    {
    int top = lua_gettop(L);
    tmr_t *tmr = tmr_search(id);
    if(tmr==NULL)
        { luaL_error(L, UNEXPECTED_ERROR, id); return; }
    if(lua_rawgeti(L, LUA_REGISTRYINDEX, tmr->Callback) != LUA_TFUNCTION)
        { tmr_free(tmr); luaL_error(L, UNEXPECTED_ERROR); return; }
    lua_pushinteger(L, tmr->arg);
    if(lua_pcall(L, 1, 0, 0) != LUA_OK) 
        { tmr_free(tmr); lua_error(L); return; }
    tmr_free(tmr);
    lua_settop(L, top);
    }

#undef L

static int TimerFunc(lua_State *L)
    {
    tmr_t *tmr;
    unsigned int msec = luaL_checkinteger(L, 1);
    int arg = luaL_checkinteger(L, 3);
    if(!lua_isfunction(L, 2))
        return luaL_argerror(L, 2, "function expected");
    if((tmr = tmr_new()) == NULL)
        return luaL_error(L, "cannot create timer");
    lua_pushvalue(L, 2);
    tmr->Callback = luaL_ref(L, LUA_REGISTRYINDEX);
    tmr->arg = arg;
    /* use the id as arg so that we can identify the timer in the C callback */
    glutTimerFunc(msec, TimerCallback, tmr->id); 
    return 0;
    }

/*--------------------------------------------------------------------------*
 | Functions registration                                                   |
 *--------------------------------------------------------------------------*/

static const struct luaL_Reg Functions[] = 
    {
        /* global */
        { "idle_func", IdleFunc },
        { "init_error_func", InitErrorFunc },
        { "init_warning_func", InitWarningFunc },
#ifdef MOONGLUT_MOBILE
        { "init_context_func", InitContextFunc },
        { "app_status_func", AppStatusFunc },
#endif
        /* window specific */
        { "display_func", DisplayFunc },
        { "close_func", CloseFunc  },
        { "reshape_func", ReshapeFunc },
        { "keyboard_func", KeyboardFunc },
        { "keyboard_up_func", KeyboardUpFunc },
        { "special_func", SpecialFunc },
        { "special_up_func", SpecialUpFunc },
        { "mouse_func", MouseFunc },
        { "mouse_wheel_func", MouseWheelFunc },
        { "window_status_func", WindowStatusFunc },
        { "motion_func", MotionFunc },
        { "passive_motion_func", PassiveMotionFunc  },
        { "entry_func", EntryFunc },
#if 0
        { "",  },
        { "position_func", PositionFunc },
#endif
#if 0
glutVisibilityFunc() (deprecated)
void  glutSpaceballMotionFunc( void (* callback)( int, int, int ) );
void  glutSpaceballRotateFunc( void (* callback)( int, int, int ) );
void  glutSpaceballButtonFunc( void (* callback)( int, int ) );
void  glutJoystickFunc( void (* callback)( unsigned int, int, int, int ), int pollInterval );
void  glutOverlayDisplayFunc( void (* callback)( void ) );
void  glutButtonBoxFunc( void (* callback)( int, int ) );
void  glutDialsFunc( void (* callback)( int, int ) );
void  glutTabletMotionFunc( void (* callback)( int, int ) );
void  glutTabletButtonFunc( void (* callback)( int, int, int, int ) );
#endif
        /* menu specific */
        { "menu_status_func", MenuStatusFunc  },
        { "menu_destroy_func", MenuDestroyFunc  },

        /* timer specific */
        { "timer_func", TimerFunc  },
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_callbacks(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

