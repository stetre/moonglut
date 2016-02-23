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
 * Initialization and main functions (see fglut_init.c, fg_init.c, fg_main) *
 ****************************************************************************/

#include "internal.h"


static int Init(lua_State *L)
    {
    int table_index;
    int argc, i;
    char **argv;
    const char *arg;

    if(lua_isnoneornil(L, 1))
        argc = 1;
    else
        {
        if(!lua_istable(L,1))
            return luaL_argerror(L, 1, "table expected");
        table_index = 1;
        argc = luaL_len(L, table_index) + 1;
        }

    argv = malloc(sizeof(char*) * argc);
    if(argv == NULL)
        return luaL_error(L, "cannot allocate memory"); 
    argv[0] = "moonglut";
    if(argc > 1)
        {
        for(i = 1; i < argc; i++)
            {
            lua_geti(L, table_index, i);
            arg = luaL_checkstring(L, -1);
            argv[i] = strdup(arg);
            if(argv[i] == NULL)
                return luaL_error(L, "cannot allocate memory");
            lua_pop(L, 1);
            }
        }
    glutInit(&argc, argv); 

    /* return the modified arg table */
    lua_newtable(L);
    table_index = lua_gettop(L);
    for(i = 1; i < argc; i++)
        {
        lua_pushstring(L, argv[i]);
        lua_seti(L, table_index, i);
        }
    return 1;
    }

static int InitState(lua_State *L)
    {
    lua_pushboolean(L, glutGet(GLUT_INIT_STATE) == GL_TRUE);
    return 1;
    }

static int Version(lua_State *L)
    {
    int ver = glutGet(GLUT_VERSION);
    int major = ver/10000;
    int minor = (ver-major*10000)/100;
    int micro = (ver-major*10000-minor*100);
    lua_pushinteger(L, major);
    lua_pushinteger(L, minor);
    lua_pushinteger(L, micro);
    return 3;
    }

#if 0
static int InitContextVersion(lua_State *L) 
    {
    int major, minor;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        major = luaL_checkinteger(L, 1);
        minor = luaL_checkinteger(L, 2);
        glutInitContextVersion(major, minor);
        }
    major = glutGet(GLUT_INIT_MAJOR_VERSION);
    minor = glutGet(GLUT_INIT_MINOR_VERSION);
    lua_pushinteger(L, major);
    lua_pushinteger(L, minor);
    return 2;
    }

static const char *FlagsStrings[] = { "debug", "forward compatible", NULL };
static int FlagsCodes[] = { GLUT_DEBUG, GLUT_FORWARD_COMPATIBLE };

static int InitContextFlags(lua_State *L)
    {
    int i, n, rc;
    int opt, val, arg = 1;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        val = 0;
        while(!lua_isnoneornil(L, arg))
            { 
            opt = checkoption(L, arg, NULL, FlagsStrings);
            val |= FlagsCodes[opt];
            arg++;
            }
        glutInitContextFlags(val);
        }
    /* get */   
    n = sizeof(FlagsCodes)/sizeof(FlagsCodes[0]);
    rc = 0;
    val = glutGet(GLUT_INIT_FLAGS);
    for(i = 0; i <n; i ++)
        {
        if(val & FlagsCodes[i])
            { lua_pushstring(L, FlagsStrings[i]); rc++; }
        }
    return rc;
    }

static const char *ProfileStrings[] = { "core", "compatibility", NULL };
static int ProfileCodes[] = { GLUT_CORE_PROFILE, GLUT_COMPATIBILITY_PROFILE };

static int InitContextProfile(lua_State *L)
  {
    int i, n, rc;
    int opt, val, arg = 1;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        val = 0;
        while(!lua_isnoneornil(L, arg))
            { 
            opt = checkoption(L, arg, NULL, ProfileStrings);
            val |= ProfileCodes[opt];
            arg++;
            }
        glutInitContextProfile(val);
        }
    /* get */   
    n = sizeof(ProfileCodes)/sizeof(ProfileCodes[0]);
    rc = 0;
    val = glutGet(GLUT_INIT_PROFILE);
    for(i = 0; i <n; i ++)
        {
        if(val & ProfileCodes[i])
            { lua_pushstring(L, ProfileStrings[i]); rc++; }
        }
    return rc;
    }
#endif

static int UseCurrentContext(lua_State *L)
    {
    int val;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        if(!lua_isboolean(L, 1))
            return luaL_argerror(L, 1, "boolean expected");
        val = lua_toboolean(L, 1) ? GLUT_USE_CURRENT_CONTEXT : GLUT_USE_CURRENT_CONTEXT;
        glutSetOption(GLUT_RENDERING_CONTEXT, val);
        }
    val = glutGet(GLUT_RENDERING_CONTEXT);
    switch(val)
        {
        case GLUT_USE_CURRENT_CONTEXT: lua_pushboolean(L, 1); break;
        case GLUT_CREATE_NEW_CONTEXT: lua_pushboolean(L, 0); break;
        default:
            return luaL_error(L, UNEXPECTED_ERROR);
        }
    return 1;
    }

#define MOONGL_CORE                 1
#define MOONGL_COMPATIBLE           2
#define MOONGL_FORWARD_COMPATIBLE   3

static const char *ContextStrings[] = 
    { "core", "compatible", "forward compatible", NULL };
static int ContextCodes[] = 
    { MOONGL_CORE, MOONGL_COMPATIBLE, MOONGL_FORWARD_COMPATIBLE };

static int InitContext(lua_State *L) 
/* init_context([major, minor, context, debug])
 *
 *                      type  | profile     | features
 * ---------------------------------------------------------
 * core                 full  | core        | current release
 * compatible           full  | compatible  | all ever
 * forward compatible   f.c.  | core        | non-deprecated
 */
    {
    int major, minor, context, flags, profile;
    if(!lua_isnoneornil(L, 1)) /* set */
        {
        major = luaL_checkinteger(L, 1);
        minor = luaL_checkinteger(L, 2);

        flags = profile = 0;
        context = ContextCodes[checkoption(L, 3, NULL, ContextStrings)];
        switch(context)
            {
            case MOONGL_CORE: 
                        profile |= GLUT_CORE_PROFILE;
                        break;
            case MOONGL_COMPATIBLE:
                        profile |= GLUT_COMPATIBILITY_PROFILE;
                        break;
            case MOONGL_FORWARD_COMPATIBLE:
                        flags |= GLUT_FORWARD_COMPATIBLE;
                        profile |= GLUT_CORE_PROFILE;
                        break;
            default:
                return luaL_error(L, UNEXPECTED_ERROR);
            }

        if(lua_isboolean(L, 4))
            {
            if(lua_toboolean(L, 4))
                flags |= GLUT_DEBUG;
            }
        else if(!lua_isnoneornil(L, 4))
            return luaL_argerror(L, 4, "boolean expected");

        glutInitContextVersion(major, minor);
        glutInitContextFlags(flags);
        glutInitContextProfile(profile);
        }

    major = glutGet(GLUT_INIT_MAJOR_VERSION);
    minor = glutGet(GLUT_INIT_MINOR_VERSION);
    profile = glutGet(GLUT_INIT_PROFILE);
    flags = glutGet(GLUT_INIT_FLAGS);
    lua_pushinteger(L, major);
    lua_pushinteger(L, minor);
    
    if(profile & GLUT_CORE_PROFILE)
        {
        if(flags & GLUT_FORWARD_COMPATIBLE)
            lua_pushstring(L, "forward compatible");
        else
            lua_pushstring(L, "core");
        }
    else if(profile & GLUT_COMPATIBILITY_PROFILE)
        lua_pushstring(L, "compatible");
    else
        lua_pushstring(L, "default");
    lua_pushboolean(L, (flags & GLUT_DEBUG));
    return 4;
    }

VOID_FUNC(MainLoopEvent)
VOID_FUNC(LeaveMainLoop)
VOID_FUNC(MainLoop)
VOID_FUNC(Exit)


static const struct luaL_Reg Functions[] = 
    {
        { "init", Init },
        { "init_state", InitState },
/*      { "init_display_string", InitDisplayString }, void glutInitDisplayString(const char*); */
        { "version", Version },
        { "init_context", InitContext },
#if 0
        { "init_context_version", InitContextVersion },
        { "init_context_flags", InitContextFlags },
        { "init_context_profile", InitContextProfile },
#endif
        { "use_current_context", UseCurrentContext },
        { "main_loop_event", MainLoopEvent },
        { "leave_main_loop", LeaveMainLoop },
        { "main_loop", MainLoop },
        { "exit", Exit },
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_init(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

