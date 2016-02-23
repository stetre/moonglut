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
 * Overlay stuff (see fg_overlay.c)                                         *
 ****************************************************************************/

#include "internal.h"

#if 0
NOT_IMPLEMENTED(EstablishOverlay)
NOT_IMPLEMENTED(RemoveOverlay)
NOT_IMPLEMENTED(UseLayer)
NOT_IMPLEMENTED(PostOverlayRedisplay)
NOT_IMPLEMENTED(PostWindowOverlayRedisplay)
NOT_IMPLEMENTED(ShowOverlay)
NOT_IMPLEMENTED(HideOverlay)

static const struct luaL_Reg Functions[] = 
    {
        { "establish_overlay", EstablishOverlay },
        { "remove_overlay", RemoveOverlay },
        { "use_layer", UseLayer },
        { "post_overlay_redisplay", PostOverlayRedisplay },
        { "post_window_overlay_redisplay", PostWindowOverlayRedisplay },
        { "show_overlay", ShowOverlay },
        { "hide_overlay", HideOverlay },
        /* { "LayerGet", LayerGet },    int glutLayerGet( GLenum query ); */
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_overlay(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

#else

void moonglut_open_overlay(lua_State *L)
    {
    (void)L; /* unused */
    }

#endif
