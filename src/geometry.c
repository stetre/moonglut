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
 * Geometry functions (see fg_geometry.c)                                   *
 ****************************************************************************/

#include "internal.h"

#if 0


/* Simple functions with no arguments */
#define FUNCTION(func)          \
static int func(lua_State *L)   \
    {                           \
    (void)L; /* unused */       \
    glut##func();               \
    return 0;                   \
    }



static int WireCube(lua_State *L) 
    {
    double size = luaL_checknumber(L, 1);
    glutWireCube(size);
    return 0;
    }

static int SolidCube(lua_State *L)
    {
    double size = luaL_checknumber(L, 1);
    glutSolidCube(size);
    return 0;
    }

static int WireSphere(lua_State *L) 
    {
    double radius = luaL_checknumber(L, 1);
    int slices = luaL_checkinteger(L, 2);
    int stacks = luaL_checkinteger(L, 3);
    glutWireSphere(radius, slices, stacks);
    return 0;
    }

static int SolidSphere(lua_State *L) 
    {
    double radius = luaL_checknumber(L, 1);
    int slices = luaL_checkinteger(L, 2);
    int stacks = luaL_checkinteger(L, 3);
    glutSolidSphere(radius, slices, stacks);
    return 0;
    }

static int WireCone(lua_State *L) 
    {
    double base = luaL_checknumber(L, 1);
    double height = luaL_checknumber(L, 2);
    int slices = luaL_checkinteger(L, 3);
    int stacks = luaL_checkinteger(L, 4);
    glutWireCone(base, height, slices, stacks);
    return 0;
    }

static int SolidCone(lua_State *L) 
    {
    double base = luaL_checknumber(L, 1);
    double height = luaL_checknumber(L, 2);
    int slices = luaL_checkinteger(L, 3);
    int stacks = luaL_checkinteger(L, 4);
    glutSolidCone(base, height, slices, stacks);
    return 0;
    }

static int WireTorus(lua_State *L) 
    {
    double inner_radius = luaL_checknumber(L, 1);
    double outer_radius = luaL_checknumber(L, 2);
    int sides = luaL_checkinteger(L, 3);
    int rings = luaL_checkinteger(L, 4);
    glutWireTorus(inner_radius, outer_radius, sides, rings);
    return 0;
    }

static int SolidTorus(lua_State *L) 
    {
    double inner_radius = luaL_checknumber(L, 1);
    double outer_radius = luaL_checknumber(L, 2);
    int sides = luaL_checkinteger(L, 3);
    int rings = luaL_checkinteger(L, 4);
    glutSolidTorus(inner_radius, outer_radius, sides, rings);
    return 0;
    }

FUNCTION(WireDodecahedron)
FUNCTION(SolidDodecahedron)
FUNCTION(WireOctahedron)
FUNCTION(SolidOctahedron)
FUNCTION(WireTetrahedron)
FUNCTION(SolidTetrahedron)
FUNCTION(WireIcosahedron)
FUNCTION(SolidIcosahedron)
FUNCTION(WireRhombicDodecahedron)
FUNCTION(SolidRhombicDodecahedron)


static int WireSierpinskiSponge (lua_State *L) 
    {
    double scale, offset[3];
    int num_levels = luaL_checkinteger(L, 1);
    offset[0] = luaL_checknumber(L, 2);
    offset[1] = luaL_checknumber(L, 3);
    offset[2] = luaL_checknumber(L, 4);
    scale = luaL_checknumber(L, 5);
    glutWireSierpinskiSponge(num_levels, offset, scale);
    return 0;
    }

static int SolidSierpinskiSponge (lua_State *L) 
    {
    double scale, offset[3];
    int num_levels = luaL_checkinteger(L, 1);
    offset[0] = luaL_checknumber(L, 2);
    offset[1] = luaL_checknumber(L, 3);
    offset[2] = luaL_checknumber(L, 4);
    scale = luaL_checknumber(L, 5);
    glutSolidSierpinskiSponge(num_levels, offset, scale);
    return 0;
    }

static int WireCylinder(lua_State *L) 
    {
    double base = luaL_checknumber(L, 1);
    double height = luaL_checknumber(L, 2);
    int slices = luaL_checkinteger(L, 3);
    int stacks = luaL_checkinteger(L, 4);
    glutWireCylinder(base, height, slices, stacks);
    return 0;
    }

static int SolidCylinder(lua_State *L) 
    {
    double base = luaL_checknumber(L, 1);
    double height = luaL_checknumber(L, 2);
    int slices = luaL_checkinteger(L, 3);
    int stacks = luaL_checkinteger(L, 4);
    glutSolidCylinder(base, height, slices, stacks);
    return 0;
    }


#undef FUNCTION

static const struct luaL_Reg Functions[] = 
    {
        { "wire_cube", WireCube },
        { "solid_cube", SolidCube },
        { "wire_sphere", WireSphere },
        { "solid_sphere", SolidSphere },
        { "wire_cone", WireCone },
        { "solid_cone", SolidCone },
        { "wire_torus", WireTorus },
        { "solid_torus", SolidTorus },
        { "wire_dodecahedron", WireDodecahedron },
        { "solid_dodecahedron", SolidDodecahedron },
        { "wire_octahedron", WireOctahedron },
        { "solid_octahedron", SolidOctahedron },
        { "wire_tetrahedron", WireTetrahedron },
        { "solid_tetrahedron", SolidTetrahedron },
        { "wire_icosahedron", WireIcosahedron },
        { "solid_icosahedron", SolidIcosahedron },
        { "wire_rhombic_dodecahedron", WireRhombicDodecahedron },
        { "solid_rhombic_dodecahedron", SolidRhombicDodecahedron },
        { "wire_sierpinski_sponge ", WireSierpinskiSponge  },
        { "solid_sierpinski_sponge ", SolidSierpinskiSponge  },
        { "wire_cylinder", WireCylinder },
        { "solid_cylinder", SolidCylinder },
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_geometry(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

#else

void moonglut_open_geometry(lua_State *L)
    {
    (void)L;
    }

#endif
