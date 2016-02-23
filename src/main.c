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

#include "internal.h"


static void AddVersions(lua_State *L)
/* Add version strings to the glut table */
    {
    lua_pushstring(L, "_VERSION");
    lua_pushstring(L, "MoonGLUT "MOONGLUT_VERSION);
    lua_settable(L, -3);

    lua_pushstring(L, "_GLUT_VERSION");
    lua_pushfstring(L, "FreeGLUT %d api %d xlib %d",
                    FREEGLUT, GLUT_API_VERSION, GLUT_XLIB_IMPLEMENTATION);
    lua_settable(L, -3);

    }

void moonglut_open_init(lua_State *L);
void moonglut_open_joystick(lua_State *L);
void moonglut_open_window(lua_State *L);
void moonglut_open_display(lua_State *L);
void moonglut_open_cursor(lua_State *L);
void moonglut_open_overlay(lua_State *L);
void moonglut_open_menu(lua_State *L);
void moonglut_open_callbacks(lua_State *L);
void moonglut_open_font(lua_State *L);
void moonglut_open_geometry(lua_State *L);
void moonglut_open_teapot(lua_State *L);
void moonglut_open_gamemode(lua_State *L);
void moonglut_open_videoresize(lua_State *L);
void moonglut_open_misc(lua_State *L);
void moonglut_open_ext(lua_State *L);

lua_State *moonglut_L = NULL;

int luaopen_moonglut(lua_State *L)
/* Lua calls this function to load the module */
    {
    moonglut_L = L; 

    lua_newtable(L); /* the glut table */
    AddVersions(L);

    /* add glut functions: */
    moonglut_open_init(L);
    moonglut_open_joystick(L);
    moonglut_open_window(L);
    moonglut_open_display(L);
    moonglut_open_cursor(L);
    moonglut_open_overlay(L);
    moonglut_open_menu(L);
    moonglut_open_callbacks(L);
    moonglut_open_font(L);
    moonglut_open_geometry(L);
    moonglut_open_teapot(L);
    moonglut_open_gamemode(L);
    moonglut_open_videoresize(L);
    moonglut_open_misc(L);
    moonglut_open_ext(L);

    return 1;
    }

