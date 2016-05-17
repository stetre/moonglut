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
 * Timer database                                                           *
 ****************************************************************************/

#include "internal.h"

static int id_new(void)
/* returns a free id or -1 if none are found (unlikely) */
    {
    static int idfree = 0;
    int guard = idfree-1;
    if((idfree==-1)||(idfree==0)||(idfree==1))
        { idfree=1; guard=-1; }
    while(1)
        {
        if(idfree==guard) /* we made a complete round */
            return -1;
        if(idfree==-1) idfree=1;
        if(tmr_search(idfree)==NULL) return idfree++;
        idfree++;
        }
    return -1;
    }

static int cmp(tmr_t *tmr1, tmr_t *tmr2) /* the compare function */
    { return (tmr1->id < tmr2->id ? -1 : tmr1->id > tmr2->id); } 

static RB_HEAD(tmrtree_s, tmr_s) Head = RB_INITIALIZER(&Head);

RB_PROTOTYPE_STATIC(tmrtree_s, tmr_s, entry, cmp) 
RB_GENERATE_STATIC(tmrtree_s, tmr_s, entry, cmp) 
 
static tmr_t *tmr_remove(tmr_t *tmr) 
    { return RB_REMOVE(tmrtree_s, &Head, tmr); }
static tmr_t *tmr_insert(tmr_t *tmr) 
    { return RB_INSERT(tmrtree_s, &Head, tmr); }
tmr_t *tmr_search(int id) 
    { tmr_t tmp; tmp.id = id; return RB_FIND(tmrtree_s, &Head, &tmp); }
#if 0
static tmr_t *tmr_first(int id) 
    { tmr_t tmp; tmp.id = id; return RB_NFIND(tmrtree_s, &Head, &tmp); }
tmr_t *tmr_next(tmr_t *tmr)
    { return RB_NEXT(tmrtree_s, &Head, tmr); }
tmr_t *tmr_prev(tmr_t *tmr)
    { return RB_PREV(tmrtree_s, &Head, tmr); }
tmr_t *tmr_min(void)
    { return RB_MIN(tmrtree_s, &Head); }
tmr_t *tmr_max(void)
    { return RB_MAX(tmrtree_s, &Head); }
tmr_t *tmr_root(void)
    { return RB_ROOT(&Head); }
#endif


tmr_t *tmr_new(void)
    {
    tmr_t *tmr;
    int id =  id_new(); /* allocate a free id */
    if(id == -1)
        return NULL;
    if((tmr = (tmr_t*)malloc(sizeof(tmr_t))) == NULL) return NULL;
    memset(tmr, 0, sizeof(tmr_t));
    tmr->id = id;
    tmr->Callback = LUA_NOREF;
    tmr_insert(tmr);
    return tmr;
    }

void tmr_free(tmr_t* tmr)
    {
    if(tmr_search(tmr->id) == tmr)
        {
        CALLBACK_UNREF(tmr->Callback);
        tmr_remove(tmr);
        }
    free(tmr);  
    }

#if 0
void tmr_free_all(void)
    {
    tmr_t *tmr;
    while((tmr = tmr_first(0)))
        tmr_free(tmr);
    }
#endif

