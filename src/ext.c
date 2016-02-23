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
 * Extension functions                                                      *
 ****************************************************************************/

#include "internal.h"

NOT_IMPLEMENTED(GetProcAddress) //GLUTproc glutGetProcAddress( const char *procName );

#if GLUT_HAS_MULTI
NOT_IMPLEMENTED(MultiEntryFunc) //void glutMultiEntryFunc(void(*callback)(int,int));
NOT_IMPLEMENTED(MultiButtonFunc) //void glutMultiButtonFunc(void(*callback)(int,int,int,int,int));
NOT_IMPLEMENTED(MultiMotionFunc) //void glutMultiMotionFunc(void(*callback)(int,int,int));
NOT_IMPLEMENTED(MultiPassiveFunc) //void glutMultiPassiveFunc(void(*callback)(int,int,int));
#endif

static const struct luaL_Reg Functions[] = 
    {
        { "get_proc_address", GetProcAddress },
#if GLUT_HAS_MULTI
        { "multi_entry_func", MultiEntryFunc },
        { "multi_button_func", MultiButtonFunc },
        { "multi_motion_func", MultiMotionFunc },
        { "multi_passive_func", MultiPassiveFunc },
#endif
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_ext(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

