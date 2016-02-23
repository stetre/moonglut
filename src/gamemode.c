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
 * Game mode functions (see fg_gamemode.c)                                  *
 ****************************************************************************/

#include "internal.h"

static const char* ModeStrings[] = {
        "active", "possible", "width", "height", 
        "pixel depth", "refresh rate", "display changed", NULL
    };
static int ModeCodes[] = { 
        GLUT_GAME_MODE_ACTIVE, GLUT_GAME_MODE_POSSIBLE, GLUT_GAME_MODE_WIDTH,
        GLUT_GAME_MODE_HEIGHT, GLUT_GAME_MODE_PIXEL_DEPTH, GLUT_GAME_MODE_REFRESH_RATE,
        GLUT_GAME_MODE_DISPLAY_CHANGED
    };

static int GameModeString(lua_State *L) 
    {
    const char *string =luaL_checkstring(L, 1);
    glutGameModeString(string);
    return 0;
    }

static int EnterGameMode(lua_State *L)
    {
    int id;
    win_t *win;
    if((id = glutEnterGameMode()) < 1)
        return luaL_error(L, "cannot create window");
    if((win = win_new(id, 0)) == NULL)
        return luaL_error(L, "cannot create window");
    glutCloseFunc(windowCloseCallback);
    lua_pushinteger(L, id);
    return 1;
    }



VOID_FUNC(LeaveGameMode)

static int GameModeGet(lua_State *L)
    {
    int val = ModeCodes[checkoption(L, 1, NULL, ModeStrings)];
    switch(val)
        {
        case GLUT_GAME_MODE_ACTIVE: 
        case GLUT_GAME_MODE_POSSIBLE:
        case GLUT_GAME_MODE_DISPLAY_CHANGED:
                lua_pushboolean(L, glutGameModeGet(val) == 1); return 1;
        case GLUT_GAME_MODE_WIDTH:
        case GLUT_GAME_MODE_HEIGHT:
        case GLUT_GAME_MODE_PIXEL_DEPTH:
        case GLUT_GAME_MODE_REFRESH_RATE:
                lua_pushinteger(L, glutGameModeGet(val)); return 1;
        }
    return luaL_error(L, UNEXPECTED_ERROR);
    }


static const struct luaL_Reg Functions[] = 
    {
        { "game_mode_string", GameModeString },
        { "enter_game_mode", EnterGameMode },
        { "leave_game_mode", LeaveGameMode },
        { "game_mode_get", GameModeGet },
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_gamemode(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

