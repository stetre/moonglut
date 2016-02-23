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

/********************************************************************************
 * internal common header                                                       *
 ********************************************************************************/

#ifndef internalDEFINED
#define internalDEFINED

#include <string.h>
#include "moonglut.h"
#include "tree.h"

#define TOSTR_(x) #x
#define TOSTR(x) TOSTR_(x)

/* Note: all the dynamic symbols of this library (should) start with 'moonglut_' .
 * The only exception is the luaopen_moonglut() function, which is searched for
 * with that name by Lua.
 * MoonGLUT's string references on the Lua registry also start with 'moonglut_'.
 */

#if LUA_VERSION_NUM < 503 /* defined in lua.h */
#error "MoonGLUT requires Lua v5.3 or greater"
#endif

#if (LUAVER != LUA_VERSION_NUM)
#pragma message ("lua.h version is "TOSTR(LUA_VERSION_NUM))
#error "Lua version mismatch"
#endif

#include "structs.h"

extern lua_State *moonglut_L; /* the global Lua state */

#if 0
/* .c */
#define  moonglut_
#endif

    
/* win.c */
#define win_search moonglut_win_search
win_t *win_search(int id);
#define win_first moonglut_win_first
win_t *win_first(int id);
#define win_next moonglut_win_next
win_t *win_next(win_t *win);
#define win_new moonglut_win_new
win_t *win_new(int id, int parent);
#define win_free moonglut_win_free
void win_free(win_t* win);
#define win_free_all moonglut_win_free_all
void win_free_all(void);
#define win_check moonglut_win_check
win_t* win_check(lua_State *L, int arg);
#define win_current moonglut_win_current
win_t *win_current(lua_State *L);

/* mnu.c */
#define mnu_search moonglut_mnu_search
mnu_t *mnu_search(int id);
#define mnu_new moonglut_mnu_new
mnu_t *mnu_new(int id);
#define mnu_free moonglut_mnu_free
void mnu_free(mnu_t* mnu);
#define mnu_current moonglut_mnu_current
mnu_t *mnu_current(lua_State *L);

/* tmr.c */
#define tmr_search moonglut_tmr_search
tmr_t *tmr_search(int id); 
#define tmr_new moonglut_tmr_new
tmr_t *tmr_new(void);
#define tmr_free moonglut_tmr_free
void tmr_free(tmr_t* tmr);


/* window.c */
#define windowCloseCallback moonglut_windowCloseCallback
void windowCloseCallback(void);

/* utils.c */
#define checkoption moonglut_checkoption
int checkoption(lua_State *L, int arg, const char *def, const char *const lst[]);
#define checkboolean moonglut_checkboolean
GLboolean checkboolean(lua_State *L, int arg);
#define noprintf moonglut_noprintf
int noprintf(const char *fmt, ...);
#define pushkey moonglut_pushkey
int pushkey(lua_State *L, int key);
#define pushspecial moonglut_pushspecial
int pushspecial(lua_State *L, int key);

/*------------------------------------------------------------------------------*
 | Debug and other utilities                                                    |
 *------------------------------------------------------------------------------*/

/* If this is printed, it denotes a suspect bug: */
#define UNEXPECTED_ERROR "unexpected error (%s, %d)", __FILE__, __LINE__

#define NOT_AVAILABLE "function not available"

#define NOT_IMPLEMENTED(func)               \
static int func(lua_State *L)               \
    {                                       \
    luaL_error(L, "function "#func" is not implemented");   \
    return 0;                           \
    }

#define NOT_SUPPORTED(func)                 \
static int func(lua_State *L)               \
    {                                       \
    luaL_error(L, "function "#func" is not supported"); \
    return 0;                           \
    }

#if defined(DEBUG)

#define DBG printf

#define TR() do {                                           \
    printf("trace %s %d\n",__FILE__,__LINE__);              \
} while(0)

#define BK() do {                                           \
    printf("break %s %d\n",__FILE__,__LINE__);              \
    getchar();                                              \
} while(0)

#else 

#define DBG noprintf
#define TR()
#define BK()

#endif /* DEBUG */

/*------------------------------------------------------------------------------*
 | Code generators                                                              |
 *------------------------------------------------------------------------------*/

#define CALLBACK_UNREF(cb) do { \
        if((cb) != LUA_NOREF)   { \
            luaL_unref(moonglut_L, LUA_REGISTRYINDEX, (cb));    \
            (cb) = LUA_NOREF;   } \
} while(0)

#define VOID_FUNC(func) \
    static int func(lua_State *L) { (void)L; glut##func(); return 0; }


#endif /* internalDEFINED */
