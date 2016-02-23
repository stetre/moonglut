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

int noprintf(const char *fmt, ...) 
    { (void)fmt; return 0; }

/*------------------------------------------------------------------------------*
 | Custom luaL_checkxxx() style functions                                       |
 *------------------------------------------------------------------------------*/

int checkoption(lua_State *L, int arg, const char *def, const char *const lst[])
/* Variant of luaL_checkoption(), with an added hint in the error message */
    {
    const char *hint = NULL;
    const char *name = (def) ? luaL_optstring(L, arg, def) : luaL_checkstring(L, arg);
    int i;
    for (i=0; lst[i]; i++)
        if (strcmp(lst[i], name) == 0)  return i;

    if(lua_checkstack(L, i*2))
        {
        for(i=0; lst[i]; i++)
            {
            lua_pushfstring(L, "'%s'", lst[i]);
            lua_pushstring(L, "|");
            }
        i = i*2;
        if(i>0)
            {
            lua_pop(L, 1); /* the last separator */
            lua_concat(L, i-1);
            hint = lua_tostring(L, -1); 
            }
        }
    if(hint)
        return luaL_argerror(L, arg, lua_pushfstring(L, 
                    "invalid option '%s', valid options are: %s", name, hint));
    return luaL_argerror(L, arg, lua_pushfstring(L, "invalid option '%s'", name));
    }


GLboolean checkboolean(lua_State *L, int arg)
    {
    if(!lua_isboolean(L, arg))
        return (GLboolean)luaL_argerror(L, arg, "boolean expected");
    return lua_toboolean(L, arg) ? GL_TRUE : GL_FALSE;
    }


int pushkey(lua_State *L, int key)
    {
    if((key > 32) && (key < 127))
        { lua_pushfstring(L, "%c", key); return 1; }
    switch(key)
        {
#define PUSH(s) do { lua_pushstring(L, s); return 1; } while(0);
        case  0: PUSH("nul") /* NUL '\0' (null character) */
        case  1: PUSH("soh") /* SOH (start of heading) */
        case  2: PUSH("stx") /* STX (start of text) */
        case  3: PUSH("etx") /* ETX (end of text) */
        case  4: PUSH("eot") /* EOT (end of transmission) */
        case  5: PUSH("enq") /* ENQ (enquiry) */
        case  6: PUSH("ack") /* ACK (acknowledge) */
        case  7: PUSH("bel") /* BEL '\a' (bell) */
        case  8: PUSH("bs") /* BS  '\b' (backspace) */
        case  9: PUSH("ht") /* HT  '\t' (horizontal tab) */
        case  10: PUSH("nl") /* LF  '\n' (new line) */
        case  11: PUSH("vt") /* VT  '\v' (vertical tab) */
        case  12: PUSH("ff") /* FF  '\f' (form feed) */
        case  13: PUSH("cr") /* CR  '\r' (carriage ret) */
        case  14: PUSH("so") /* SO  (shift out) */
        case  15: PUSH("si") /* SI  (shift in) */
        case  16: PUSH("dle") /* DLE (data link escape) */
        case  17: PUSH("dc1") /* DC1 (device control 1) */
        case  18: PUSH("dc2") /* DC2 (device control 2) */
        case  19: PUSH("dc3") /* DC3 (device control 3) */
        case  20: PUSH("dc4") /* DC4 (device control 4) */
        case  21: PUSH("nak") /* NAK (negative ack.) */
        case  22: PUSH("syn") /* SYN (synchronous idle) */
        case  23: PUSH("etb") /* ETB (end of trans. blk) */
        case  24: PUSH("can") /* CAN (cancel) */
        case  25: PUSH("em") /* EM  (end of medium) */
        case  26: PUSH("sub") /* SUB (substitute) */
        case  27: PUSH("esc") /* ESC (escape) */
        case  28: PUSH("fs") /* FS  (file separator) */
        case  29: PUSH("gs") /* GS  (group separator) */
        case  30: PUSH("rs") /* RS  (record separator) */
        case  31: PUSH("us") /* US  (unit separator) */
        case  32: PUSH("space") /* SPACE */
        case  127: PUSH("del") /* DEL */
        default:
            lua_pushfstring(L, "\\%d", key);
            return 1;
#undef PUSH
        }
    return luaL_error(L, UNEXPECTED_ERROR);
    }

int pushspecial(lua_State *L, int key)
    {
    switch(key)
        {
        case GLUT_KEY_F1: lua_pushstring(L, "f1"); return 1;
        case GLUT_KEY_F2: lua_pushstring(L, "f2"); return 1;
        case GLUT_KEY_F3: lua_pushstring(L, "f3"); return 1;
        case GLUT_KEY_F4: lua_pushstring(L, "f4"); return 1;
        case GLUT_KEY_F5: lua_pushstring(L, "f5"); return 1;
        case GLUT_KEY_F6: lua_pushstring(L, "f6"); return 1;
        case GLUT_KEY_F7: lua_pushstring(L, "f7"); return 1;
        case GLUT_KEY_F8: lua_pushstring(L, "f8"); return 1;
        case GLUT_KEY_F9: lua_pushstring(L, "f9"); return 1;
        case GLUT_KEY_F10: lua_pushstring(L, "f10"); return 1;
        case GLUT_KEY_F11: lua_pushstring(L, "f11"); return 1;
        case GLUT_KEY_F12: lua_pushstring(L, "f12"); return 1;
        case GLUT_KEY_LEFT: lua_pushstring(L, "left"); return 1;
        case GLUT_KEY_UP: lua_pushstring(L, "up"); return 1;
        case GLUT_KEY_RIGHT: lua_pushstring(L, "right"); return 1;
        case GLUT_KEY_DOWN: lua_pushstring(L, "down"); return 1;
        case GLUT_KEY_PAGE_UP: lua_pushstring(L, "page-up"); return 1;
        case GLUT_KEY_PAGE_DOWN: lua_pushstring(L, "page-down"); return 1;
        case GLUT_KEY_HOME: lua_pushstring(L, "home"); return 1;
        case GLUT_KEY_END: lua_pushstring(L, "end"); return 1;
        case GLUT_KEY_INSERT: lua_pushstring(L, "ins"); return 1;
        case GLUT_KEY_NUM_LOCK: lua_pushstring(L, "num-lock"); return 1;
        case GLUT_KEY_BEGIN: lua_pushstring(L, "begin"); return 1;
        case GLUT_KEY_DELETE: lua_pushstring(L, "del"); return 1;
        case GLUT_KEY_SHIFT_L: lua_pushstring(L, "shift-l"); return 1;
        case GLUT_KEY_SHIFT_R: lua_pushstring(L, "shift-r"); return 1;
        case GLUT_KEY_CTRL_L: lua_pushstring(L, "ctrl-l"); return 1;
        case GLUT_KEY_CTRL_R: lua_pushstring(L, "ctrl-r"); return 1;
        case GLUT_KEY_ALT_L: lua_pushstring(L, "alt-l"); return 1;
        case GLUT_KEY_ALT_R: lua_pushstring(L, "alt-r"); return 1;
#if 0
        case GLUT_KEY_REPEAT_OFF: lua_pushstring(L, "repeat-off"); return 1;
        case GLUT_KEY_REPEAT_ON: lua_pushstring(L, "repeat-on"); return 1;
        case GLUT_KEY_REPEAT_DEFAULT: lua_pushstring(L, "repeat-default"); return 1;
#endif
        default:
            lua_pushfstring(L, "???",key);
            return 1;
        }
    return luaL_error(L, UNEXPECTED_ERROR);
    }


