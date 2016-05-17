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
 * Window database                                                          *
 ****************************************************************************/

#include "internal.h"

static int cmp(win_t *win1, win_t *win2) /* the compare function */
    { return (win1->id < win2->id ? -1 : win1->id > win2->id); } 

static RB_HEAD(wintree_s, win_s) Head = RB_INITIALIZER(&Head);

RB_PROTOTYPE_STATIC(wintree_s, win_s, entry, cmp) 
RB_GENERATE_STATIC(wintree_s, win_s, entry, cmp) 
 
static win_t *win_remove(win_t *win) 
    { return RB_REMOVE(wintree_s, &Head, win); }
static win_t *win_insert(win_t *win) 
    { return RB_INSERT(wintree_s, &Head, win); }
win_t *win_search(int id) 
    { win_t tmp; tmp.id = id; return RB_FIND(wintree_s, &Head, &tmp); }
win_t *win_first(int id) 
    { win_t tmp; tmp.id = id; return RB_NFIND(wintree_s, &Head, &tmp); }
win_t *win_next(win_t *win)
    { return RB_NEXT(wintree_s, &Head, win); }
#if 0
win_t *win_prev(win_t *win)
    { return RB_PREV(wintree_s, &Head, win); }
win_t *win_min(void)
    { return RB_MIN(wintree_s, &Head); }
win_t *win_max(void)
    { return RB_MAX(wintree_s, &Head); }
win_t *win_root(void)
    { return RB_ROOT(&Head); }
#endif
win_t *win_new(int id, int parent)
    {
    win_t *win;
    if((win = (win_t*)malloc(sizeof(win_t))) == NULL) return NULL;
    memset(win, 0, sizeof(win_t));
    win->id = id;
    win->parent = parent;
    if(win_search(win->id))
        { free(win); return NULL; }
    win->Display = LUA_NOREF;
    win->Close = LUA_NOREF;
    win->Reshape = LUA_NOREF;
    win->Position = LUA_NOREF;
    win->Keyboard = LUA_NOREF;
    win->KeyboardUp = LUA_NOREF;
    win->Special = LUA_NOREF;
    win->SpecialUp = LUA_NOREF;
    win->Mouse = LUA_NOREF;
    win->MouseWheel = LUA_NOREF;
    win->WindowStatus = LUA_NOREF;
    win->Motion = LUA_NOREF;
    win->PassiveMotion = LUA_NOREF;
    win->Entry = LUA_NOREF;
    win_insert(win);
    return win;
    }

void win_free(win_t* win)
    {
    if(win_search(win->id) == win)
        {
        /* release callback references */
        CALLBACK_UNREF(win->Display);
        CALLBACK_UNREF(win->Close);
        CALLBACK_UNREF(win->Reshape);
        CALLBACK_UNREF(win->Position);
        CALLBACK_UNREF(win->Keyboard);
        CALLBACK_UNREF(win->KeyboardUp);
        CALLBACK_UNREF(win->Special);
        CALLBACK_UNREF(win->SpecialUp);
        CALLBACK_UNREF(win->Mouse);
        CALLBACK_UNREF(win->MouseWheel);
        CALLBACK_UNREF(win->WindowStatus);
        CALLBACK_UNREF(win->Motion);
        CALLBACK_UNREF(win->PassiveMotion);
        CALLBACK_UNREF(win->Entry);
        win_remove(win);
        }
    free(win);  
    }

void win_free_all(void)
    {
    win_t *win;
    while((win = win_first(0)))
        win_free(win);
    }

win_t* win_check(lua_State *L, int arg)
    {
    int id = luaL_checkinteger(L, arg);
    win_t *win = win_search(id);
    if(!win)
        luaL_error(L, "invalid window id");
    return win;
    }

win_t *win_current(lua_State *L)
    {
    win_t *win;
    int id;
    if((id = glutGetWindow()) < 1)
        luaL_error(L, "no current window");
    if((win = win_search(id)) == NULL)
        luaL_error(L, "unknown current window");
    return win; 
    }

