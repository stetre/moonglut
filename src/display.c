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
 * Display-related functions (see fg_display.c)                             *
 ****************************************************************************/

#include "internal.h"

static const char* ModeStrings[] = { 
        "rgb", "rgba", "index", "single", "double", "accum", "alpha",
        "depth", "stencil", "multisample", "stereo", "luminance", NULL };
static unsigned int ModeCodes[] = {
    GLUT_RGB, GLUT_RGBA, GLUT_INDEX, GLUT_SINGLE, GLUT_DOUBLE, GLUT_ACCUM,GLUT_ALPHA,
    GLUT_DEPTH, GLUT_STENCIL, GLUT_MULTISAMPLE, GLUT_STEREO, GLUT_LUMINANCE };

static int InitDisplayMode(lua_State *L)
    {
    int i, n, rc, arg; 
    unsigned int opt, val;
    if(!lua_isnoneornil(L, 1))
        {
        arg = 1;
        val = 0;
        while(!lua_isnoneornil(L, arg))
            { 
            opt = checkoption(L, arg, NULL, ModeStrings);
            val |= ModeCodes[opt];
            arg++;
            }   
        glutInitDisplayMode(val);
        }
    n = sizeof(ModeCodes)/sizeof(ModeCodes[0]);
    rc = 0;
    val = glutGet(GLUT_INIT_DISPLAY_MODE);
    if(!(val & GLUT_INDEX)) { lua_pushstring(L, "rgba"); rc++; }
    if(!(val & GLUT_DOUBLE)) { lua_pushstring(L, "single"); rc++; }
    for(i = 0; i <n; i ++)
        {
        if(val & ModeCodes[i])
            { lua_pushstring(L, ModeStrings[i]); rc++; }
        }
    return rc;
    }

static int PostWindowRedisplay(lua_State *L) 
    {
    int window = luaL_checkinteger(L, 1);
    glutPostWindowRedisplay(window);
    return 0;
    }

VOID_FUNC(PostRedisplay)
VOID_FUNC(SwapBuffers)

static const struct luaL_Reg Functions[] = 
    {
        { "init_display_mode", InitDisplayMode },
        { "post_window_redisplay", PostWindowRedisplay },
        { "post_redisplay", PostRedisplay },
        { "swap_buffers", SwapBuffers },
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_display(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

