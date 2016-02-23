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
 * Mouse cursor functions (see fg_cursor.c)                                 *
 ****************************************************************************/

#include "internal.h"

static const char* CursorStrings[] = { 
    "right arrow",
    "left arrow",
    "info",
    "destroy",
    "help",
    "cycle",
    "spray",
    "wait",
    "text",
    "crosshair",
    "up down",
    "left right",
    "top side",
    "bottom side",
    "left side",
    "right side",
    "top left corner",
    "top right corner",
    "bottom right corner",
    "bottom left corner",
    "inherit",
    "none",
    "full crosshair",
    NULL
};
static int CursorCodes[] = {
    GLUT_CURSOR_RIGHT_ARROW,
    GLUT_CURSOR_LEFT_ARROW,
    GLUT_CURSOR_INFO,
    GLUT_CURSOR_DESTROY,
    GLUT_CURSOR_HELP,
    GLUT_CURSOR_CYCLE,
    GLUT_CURSOR_SPRAY,
    GLUT_CURSOR_WAIT,
    GLUT_CURSOR_TEXT,
    GLUT_CURSOR_CROSSHAIR,
    GLUT_CURSOR_UP_DOWN,
    GLUT_CURSOR_LEFT_RIGHT,
    GLUT_CURSOR_TOP_SIDE,
    GLUT_CURSOR_BOTTOM_SIDE,
    GLUT_CURSOR_LEFT_SIDE,
    GLUT_CURSOR_RIGHT_SIDE,
    GLUT_CURSOR_TOP_LEFT_CORNER,
    GLUT_CURSOR_TOP_RIGHT_CORNER,
    GLUT_CURSOR_BOTTOM_RIGHT_CORNER,
    GLUT_CURSOR_BOTTOM_LEFT_CORNER,
    GLUT_CURSOR_INHERIT,
    GLUT_CURSOR_NONE,
    GLUT_CURSOR_FULL_CROSSHAIR
};

static int Cursor(lua_State *L) 
    {
    int opt, i, n, val;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        opt = checkoption(L, 1, NULL, CursorStrings);
        glutSetCursor(CursorCodes[opt]);
        }
    n = sizeof(CursorCodes)/sizeof(CursorCodes[0]);
    val = glutGet(GLUT_WINDOW_CURSOR);
    for(i = 0; i <n; i ++)
        {
        if(val == CursorCodes[i])
            { lua_pushstring(L, CursorStrings[i]); return 1; }
        }
    lua_pushstring(L, "????");
    return 1;
    }

static int WarpPointer(lua_State *L) /* move pointer */
    {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    glutWarpPointer(x, y);
    return 0;
    }

static const struct luaL_Reg Functions[] = 
    {
        { "warp_pointer", WarpPointer },
        { "cursor", Cursor },
        { "set_cursor", Cursor }, /* alias */
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_cursor(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

