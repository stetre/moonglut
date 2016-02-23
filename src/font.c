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
 * Font stuff (see fg_font.c)                                               *
 ****************************************************************************/

#include "internal.h"

static const char *BitmapStrings[] = {
    "bitmap 9 by 15", 
    "bitmap 8 by 13",
    "bitmap times roman 10",
    "bitmap times roman 24", 
    "bitmap helvetica 10", 
    "bitmap helvetica 12", 
    "bitmap helvetica 18", 
    NULL
};

static void* BitmapCodes[] = {
    GLUT_BITMAP_9_BY_15,
    GLUT_BITMAP_8_BY_13,
    GLUT_BITMAP_TIMES_ROMAN_10,
    GLUT_BITMAP_TIMES_ROMAN_24,
    GLUT_BITMAP_HELVETICA_10,
    GLUT_BITMAP_HELVETICA_12,
    GLUT_BITMAP_HELVETICA_18,
};

static void* CheckBitmap(lua_State *L, int arg)
    {
    return BitmapCodes[luaL_checkoption(L, arg, NULL, BitmapStrings)];
    }

void* moonglut_CheckBitmap(lua_State *L, int arg)
    { return CheckBitmap(L, arg); }

static const char *StrokeStrings[] = {
    "stroke roman", 
    "stroke mono roman", 
    NULL
};

static void* StrokeCodes[] = {
    GLUT_STROKE_ROMAN,
    GLUT_STROKE_MONO_ROMAN,
};

static void* CheckStroke(lua_State *L, int arg)
    {
    return StrokeCodes[luaL_checkoption(L, arg, NULL, StrokeStrings)];
    }


static int CheckCharacter(lua_State *L,  int arg)
    {
    const char *c;
    if(lua_isinteger(L, arg))
        return lua_tointeger(L, arg);
    else if(lua_isstring(L, arg))
        {
        c = lua_tostring(L, arg);
        return (int)(c[0]);
        }
    return luaL_error(L, "invalid character");
    }

static int BitmapCharacter(lua_State *L) 
    {
    int character;
    void *font = CheckBitmap(L, 1);
    character = CheckCharacter(L, 2);
    glutBitmapCharacter(font, character);
    return 0;
    }

static int BitmapWidth(lua_State *L) 
    {
    int character;
    void *font = CheckBitmap(L, 1);
    character = CheckCharacter(L, 2);
    lua_pushinteger(L, glutBitmapWidth(font, character));
    return 1;
    }

static int StrokeCharacter(lua_State *L) 
    {
    void *font = CheckStroke(L, 1);
    int character = CheckCharacter(L, 2);
    glutStrokeCharacter(font, character);
    return 0;
    }

static int StrokeWidth(lua_State *L)
    {
    void *font = CheckStroke(L, 1);
    int character = CheckCharacter(L, 2);
    lua_pushinteger(L, glutStrokeWidth(font, character));
    return 1;
    }

static int BitmapLength(lua_State *L)
    {
    void *font = CheckBitmap(L, 1);
    const unsigned char *string = (unsigned char*)luaL_checkstring(L, 2);
    lua_pushinteger(L, glutBitmapLength(font, string));
    return 1;
    }

static int StrokeLength(lua_State *L)
    {
    void *font = CheckStroke(L, 1);
    const unsigned char *string = (unsigned char*)luaL_checkstring(L, 2);
    lua_pushinteger(L, glutStrokeLength(font, string));
    return 1;
    }

static int BitmapHeight(lua_State *L)
    {
    void *font = CheckBitmap(L, 1);
    lua_pushinteger(L, glutBitmapHeight(font));
    return 1;
    }

static int StrokeHeight(lua_State *L)
    {
    void *font = CheckStroke(L, 1);
    lua_pushnumber(L, glutStrokeHeight(font));
    return 1;
    }

static int BitmapString(lua_State *L)
    {
    void *font = CheckBitmap(L, 1);
    const unsigned char *string = (unsigned char*)luaL_checkstring(L, 2);
    glutBitmapString(font, string);
    return 0;
    }

static int StrokeString(lua_State *L)
    {
    void *font = CheckStroke(L, 1);
    const unsigned char *string = (unsigned char*)luaL_checkstring(L, 2);
    glutStrokeString(font, string);
    return 0;
    }

static const struct luaL_Reg Functions[] = 
    {
        { "bitmap_character", BitmapCharacter },
        { "bitmap_width", BitmapWidth },
        { "stroke_character", StrokeCharacter },
        { "stroke_width", StrokeWidth },
        { "bitmap_length", BitmapLength },
        { "stroke_length", StrokeLength },
        { "bitmap_height", BitmapHeight },
        { "stroke_height", StrokeHeight },
        { "bitmap_string", BitmapString },
        { "stroke_string", StrokeString },
#if 0
        { "stroke_widthf", StrokeWidthf }, in an unreleased GLUT 3.8
        { "stroke_lengthf", StrokeLengthf },in an unreleased GLUT 3.8
#endif
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_font(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

