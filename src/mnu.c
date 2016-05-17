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

static int cmp(mnu_t *mnu1, mnu_t *mnu2) /* the compare function */
    { return (mnu1->id < mnu2->id ? -1 : mnu1->id > mnu2->id); } 

static RB_HEAD(mnutree_s, mnu_s) Head = RB_INITIALIZER(&Head);

RB_PROTOTYPE_STATIC(mnutree_s, mnu_s, entry, cmp) 
RB_GENERATE_STATIC(mnutree_s, mnu_s, entry, cmp) 
 
static mnu_t *mnu_remove(mnu_t *mnu) 
    { return RB_REMOVE(mnutree_s, &Head, mnu); }
static mnu_t *mnu_insert(mnu_t *mnu) 
    { return RB_INSERT(mnutree_s, &Head, mnu); }
mnu_t *mnu_search(int id) 
    { mnu_t tmp; tmp.id = id; return RB_FIND(mnutree_s, &Head, &tmp); }
#if 0
mnu_t *mnu_first(int id) 
    { mnu_t tmp; tmp.id = id; return RB_NFIND(mnutree_s, &Head, &tmp); }
mnu_t *mnu_next(mnu_t *mnu)
    { return RB_NEXT(mnutree_s, &Head, mnu); }
mnu_t *mnu_prev(mnu_t *mnu)
    { return RB_PREV(mnutree_s, &Head, mnu); }
mnu_t *mnu_min(void)
    { return RB_MIN(mnutree_s, &Head); }
mnu_t *mnu_max(void)
    { return RB_MAX(mnutree_s, &Head); }
mnu_t *mnu_root(void)
    { return RB_ROOT(&Head); }
#endif
mnu_t *mnu_new(int id)
    {
    mnu_t *mnu;
    if((mnu = (mnu_t*)malloc(sizeof(mnu_t))) == NULL) return NULL;
    memset(mnu, 0, sizeof(mnu_t));
    mnu->id = id;
    if(mnu_search(mnu->id))
        { free(mnu); return NULL; }
    mnu->Callback = LUA_NOREF;
    mnu->MenuDestroy = LUA_NOREF;
    mnu_insert(mnu);
    return mnu;
    }

void mnu_free(mnu_t* mnu)
    {
    if(mnu_search(mnu->id) == mnu)
        {
        /* release callback references */
        CALLBACK_UNREF(mnu->Callback);
        CALLBACK_UNREF(mnu->MenuDestroy);
        mnu_remove(mnu);
        }
    free(mnu);  
    }

#if 0
void mnu_free_all(void)
    {
    mnu_t *mnu;
    while((mnu = mnu_first(0)))
        mnu_free(mnu);
    }

mnu_t* mnu_check(lua_State *L, int arg)
    {
    int id = luaL_checkinteger(L, arg);
    mnu_t *mnu = mnu_search(id);
    if(!mnu)
        luaL_error(L, "invalid menu id");
    return mnu;
    }
#endif

mnu_t *mnu_current(lua_State *L)
    {
    mnu_t *mnu;
    int id;
    if((id = glutGetMenu()) < 1)
        luaL_error(L, "no current menu");
    if((mnu = mnu_search(id)) == NULL)
        luaL_error(L, "unknown current menu");
    return mnu; 
    }

