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
 * Misc functions (fg_misc.c)                                               *
 ****************************************************************************/

#include "internal.h"

/*--------------------------------------------------------------------------*
 | Color index functions                                                    |
 *--------------------------------------------------------------------------*/

static int Color(lua_State *L) 
    {
    int color = luaL_checkinteger(L, 1);
    GLfloat red, green, blue;
    if(!lua_isnoneornil(L, 2)) /* set */
        {
        red = luaL_checknumber(L, 2);
        green = luaL_checknumber(L, 3);
        blue = luaL_checknumber(L, 4);
        glutSetColor(color, red, green, blue);
        }
    lua_pushnumber(L, glutGetColor(color, GLUT_RED));
    lua_pushnumber(L, glutGetColor(color, GLUT_GREEN));
    lua_pushnumber(L, glutGetColor(color, GLUT_BLUE));
    return 3;
    }

static int CopyColormap(lua_State *L) 
    {
    int window = luaL_checkinteger(L, 1);
    glutCopyColormap(window);
    return 0;
    }

/*--------------------------------------------------------------------------*
 | Key-repeat functions                                                     |
 *--------------------------------------------------------------------------*/

static const char* KeyStrings[] = { "off", "on", "default", NULL };
static int KeyCodes[] = { GLUT_KEY_REPEAT_OFF, GLUT_KEY_REPEAT_ON, GLUT_KEY_REPEAT_DEFAULT };

static int IgnoreKeyRepeat(lua_State *L) 
    {
    int ignore = 1;
    if(lua_isnoneornil(L, 1))
        return luaL_argerror(L, 1, "boolean expected");
    if(lua_isboolean(L,1)) ignore = lua_toboolean(L, 1);
    glutIgnoreKeyRepeat(ignore);
    return 0;
    }

static int SetKeyRepeat(lua_State *L) 
    {
    int mode = KeyCodes[checkoption(L, 1, NULL, KeyStrings)];
    glutSetKeyRepeat(mode);
    return 0;
    }

/*--------------------------------------------------------------------------*
 | Other                                                                    |
 *--------------------------------------------------------------------------*/

#if 0
NOT_IMPLEMENTED(ForceJoystickFunc) //void  glutForceJoystickFunc( void );
#endif

static int ExtensionSupported(lua_State *L) 
    {
    const char* extension = luaL_checkstring(L, 1);
    lua_pushboolean(L, glutExtensionSupported(extension));
    return 1;
    }

VOID_FUNC(ReportErrors) 

/*--------------------------------------------------------------------------*
 | Various state setters/getters                                            |
 *--------------------------------------------------------------------------*/

static int ElapsedTime(lua_State *L)
    {
    lua_pushinteger(L, glutGet(GLUT_ELAPSED_TIME));
    return 1;
    }

static int Screen(lua_State *L)
    {
    lua_pushinteger(L, glutGet(GLUT_SCREEN_WIDTH));
    lua_pushinteger(L, glutGet(GLUT_SCREEN_HEIGHT));
    lua_pushinteger(L, glutGet(GLUT_SCREEN_WIDTH_MM));
    lua_pushinteger(L, glutGet(GLUT_SCREEN_HEIGHT_MM));
    return 4;
    }

static int DeviceProperties(lua_State *L)
    {
    int table_index, val;
    lua_newtable(L);
    table_index = lua_gettop(L);
#define GET_BOOLEAN(s, code) do {                       \
    val = glutDeviceGet(code) == GL_TRUE ? 1 : 0;       \
    lua_pushboolean(L, val);                            \
    lua_setfield(L, table_index, (s));                  \
} while(0)
#define GET_INTEGER(s, code) do {                       \
    val = glutDeviceGet(code);                          \
    lua_pushinteger(L, val);                            \
    lua_setfield(L, table_index, (s));                  \
} while(0)
    
    GET_BOOLEAN("has_keyboard", GLUT_HAS_KEYBOARD);
    GET_BOOLEAN("has_mouse", GLUT_HAS_MOUSE);
    GET_INTEGER("num_mouse_buttons", GLUT_NUM_MOUSE_BUTTONS);

    GET_BOOLEAN("has_tablet", GLUT_HAS_TABLET);
    GET_INTEGER("num_tablet_buttons", GLUT_NUM_TABLET_BUTTONS);

    GET_BOOLEAN("device_ignore_key_repeat", GLUT_DEVICE_IGNORE_KEY_REPEAT);
    GET_BOOLEAN("device_key_repeat", GLUT_DEVICE_KEY_REPEAT);

    GET_BOOLEAN("has_spaceball", GLUT_HAS_SPACEBALL);
    GET_INTEGER("num_spaceball_buttons", GLUT_NUM_SPACEBALL_BUTTONS);

    GET_BOOLEAN("has_dial_and_button_box", GLUT_HAS_DIAL_AND_BUTTON_BOX);
    GET_INTEGER("num_button_box_buttons", GLUT_NUM_BUTTON_BOX_BUTTONS);
    GET_INTEGER("num_dials", GLUT_NUM_DIALS);

    GET_BOOLEAN("has_joystick", GLUT_HAS_JOYSTICK);
    GET_BOOLEAN("owns_joystick", GLUT_OWNS_JOYSTICK);
    GET_INTEGER("joystick_buttons", GLUT_JOYSTICK_BUTTONS);
    GET_INTEGER("joystick_axes", GLUT_JOYSTICK_AXES);
    GET_INTEGER("joystick_poll_rate", GLUT_JOYSTICK_POLL_RATE);
    return 1;
#undef GET_BOOLEAN
#undef GET_INTEGER
    }

static int GetModifiers(lua_State *L)
/* Returns a table with the following boolean fields: shift, ctrl, alt */
    {
    int mod;
    mod = glutGetModifiers();
    lua_pushboolean(L, (mod & GLUT_ACTIVE_SHIFT) != 0);
    lua_pushboolean(L, (mod & GLUT_ACTIVE_CTRL) != 0);
    lua_pushboolean(L, (mod & GLUT_ACTIVE_ALT) != 0);
    return 3;
    }

#if 0 
    glutSetOption(GLUT_DIRECT_RENDERING, value); @@
    glutGet():
    case GLUT_DIRECT_RENDERING:      return fgState.DirectContext; @@
    case :      return fgState.SkipStaleMotion; @@
    default: return fgPlatformGlutGet ( eWhat ); break; @@
#endif

static int Multisample(lua_State *L) 
    {
    int n;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        n = luaL_checkinteger(L, 1);
        glutSetOption(GLUT_MULTISAMPLE, n);
        }
    lua_pushinteger(L, glutGet(GLUT_MULTISAMPLE));
    return 1;
    }

static int AuxBuffers(lua_State *L) 
    {
    int n;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        n = luaL_checkinteger(L, 1);
        glutSetOption(GLUT_AUX, n);
        }
    lua_pushinteger(L, glutGet(GLUT_AUX));
    return 1;
    }

static int SkipStaleMotionEvents(lua_State *L) 
    {
    int b;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        b = checkboolean(L, 1);
        glutSetOption(GLUT_SKIP_STALE_MOTION_EVENTS, b);
        }
    lua_pushboolean(L, (glutGet(GLUT_SKIP_STALE_MOTION_EVENTS) == GL_TRUE));
    return 1;
    }

#ifdef GLUT_STROKE_FONT_DRAW_JOIN_DOTS
static int StrokeFontDrawJoinDots(lua_State *L) 
    {
    int b;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        b = checkboolean(L, 1);
        glutSetOption(GLUT_STROKE_FONT_DRAW_JOIN_DOTS, b);
        }
    lua_pushboolean(L, (glutGet(GLUT_STROKE_FONT_DRAW_JOIN_DOTS) == GL_TRUE));
    return 1;
    }
#endif




/*--------------------------------------------------------------------------*
 | Functions registration                                                   |
 *--------------------------------------------------------------------------*/

static const struct luaL_Reg Functions[] = 
    {
        { "set_color", Color },
        { "get_color", Color },
        { "copy_color_map", CopyColormap },
        { "ignore_key_repeat", IgnoreKeyRepeat },
        { "set_key_repeat", SetKeyRepeat },
        { "extension_supported", ExtensionSupported },
        { "report_errors", ReportErrors },
        { "elapsed_time", ElapsedTime},
        { "screen", Screen},
        { "device_properties", DeviceProperties },
        { "get_modifiers", GetModifiers },
        { "multisample", Multisample },
        { "aux_buffers", AuxBuffers },
        { "skip_stale_motion_events", SkipStaleMotionEvents },
#ifdef GLUT_STROKE_FONT_DRAW_JOIN_DOTS
        { "stroke_font_draw_join_dots", StrokeFontDrawJoinDots },
#endif
#if 0 /* not supported */
        { "",  },
        { "force_joystick_func", ForceJoystickFunc },
        { "GetModeValues", GetModeValues }, int* glutGetModeValues(GLenum mode, int * size);
#endif
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_misc(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

