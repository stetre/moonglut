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
 * Video resize functions (see fg_videoresize.c)                            *
 ****************************************************************************/

#include "internal.h"

#if 0
NOT_IMPLEMENTED(VideoResizeGet)
NOT_IMPLEMENTED(SetupVideoResizing)
NOT_IMPLEMENTED(StopVideoResizing)
NOT_IMPLEMENTED(VideoResize)
NOT_IMPLEMENTED(VideoPan)

static const struct luaL_Reg Functions[] = 
    {
        { "video_resize_get", VideoResizeGet },
        { "setup_video_resizing", SetupVideoResizing },
        { "stop_video_resizing", StopVideoResizing },
        { "video_resize", VideoResize },
        { "video_pan", VideoPan },
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_videoresize(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }

#else

void moonglut_open_videoresize(lua_State *L)
    {
    (void)L; /*unused*/
    }

#endif

