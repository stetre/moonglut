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
 * Teapot rendering functions(see fg_teapot.c)                              *
 ****************************************************************************/

#include "internal.h"

#if 0
#define FUNCTION_SIZE(func)                 \
static int func(lua_State *L)               \
    {                                       \
    double size = luaL_checknumber(L, 1);   \
    glut##func(size);                       \
    return 0;                               \
    }

#define FUNCTION_ATTRIB(func)               \
static int func(lua_State *L)               \
    {                                       \
    GLint attrib = luaL_checkinteger(L, 1); \
    glut##func(attrib);                     \
    return 0;                               \
    }


FUNCTION_SIZE(WireTeapot)
FUNCTION_SIZE(SolidTeapot)

FUNCTION_SIZE(WireTeacup)
FUNCTION_SIZE(SolidTeacup)
FUNCTION_SIZE(WireTeaspoon)
FUNCTION_SIZE(SolidTeaspoon)

FUNCTION_ATTRIB(SetVertexAttribCoord3)
FUNCTION_ATTRIB(SetVertexAttribNormal)
FUNCTION_ATTRIB(SetVertexAttribTexCoord2)

#undef FUNCTION_SIZE
#undef FUNCTION_ATTRIB

static const struct luaL_Reg Functions[] = 
    {
        { "wire_teapot", WireTeapot },
        { "solid_teapot", SolidTeapot },
        { "wire_teacup", WireTeacup },
        { "solid_teacup", SolidTeacup },
        { "wire_teaspoon", WireTeaspoon },
        { "solid_teaspoon", SolidTeaspoon },
        { "set_vertex_attrib_coord3", SetVertexAttribCoord3 },
        { "set_vertex_attrib_normal", SetVertexAttribNormal },
        { "set_vertex_attrib_tex_coord2", SetVertexAttribTexCoord2 },
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_teapot(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }
#else
void moonglut_open_teapot(lua_State *L)
    {
    (void)L;
    }
#endif
