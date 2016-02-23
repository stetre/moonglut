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


/********************************************************************************
 * Structs definitions                                                          *
 ********************************************************************************/

#ifndef structsDEFINED
#define structsDEFINED


/* Types redefinitions (I know, I know... ) */
#define win_t       moonglut_win_t
#define win_s       moonglut_win_s
#define mnu_t       moonglut_mnu_t
#define mnu_s       moonglut_mnu_s
#define tmr_t       moonglut_tmr_t
#define tmr_s       moonglut_tmr_s

#define moonglut_win_t struct moonglut_win_s
struct moonglut_win_s {
    RB_ENTRY(moonglut_win_s) entry;
    int id;         /* window id (search key) */
    int parent;     /* parent window id (=0 if not a subwindow) */
    /* references for callbacks on the Lua registry */
    int Display;
    int Close;
    int Reshape;
    int Position;
    int Keyboard;
    int KeyboardUp;
    int Special;
    int SpecialUp;
    int Mouse;
    int MouseWheel;
    int WindowStatus;
    int Motion;
    int PassiveMotion;
    int Entry;
};

#define moonglut_mnu_t struct moonglut_mnu_s
struct moonglut_mnu_s {
    RB_ENTRY(moonglut_mnu_s) entry;
    int id;         /* menu id (search key) */
    /* references for callbacks on the Lua registry */
    int Callback;
    int MenuDestroy;
};

#define moonglut_tmr_t struct moonglut_tmr_s
struct moonglut_tmr_s {
    RB_ENTRY(moonglut_tmr_s) entry;
    int id;     /* search key (passed as arg) */
    int arg;    /* user arg */
    int Callback; /* reference for callbacks on the Lua registry */

};


#endif /* structsDEFINED */
