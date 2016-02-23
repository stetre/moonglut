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
 * Joystick functions (DEPRECATED)                                          *
 ****************************************************************************/

#include "internal.h"

#if 0

NOT_IMPLEMENTED(JoystickGetNumAxes)
NOT_IMPLEMENTED(JoystickGetNumButtons)
NOT_IMPLEMENTED(JoystickNotWorking)
NOT_IMPLEMENTED(JoystickGetDeadBand)
NOT_IMPLEMENTED(JoystickSetDeadBand)
NOT_IMPLEMENTED(JoystickGetSaturation)
NOT_IMPLEMENTED(JoystickSetSaturation)
NOT_IMPLEMENTED(JoystickSetMinRange)
NOT_IMPLEMENTED(JoystickSetMaxRange)
NOT_IMPLEMENTED(JoystickSetCenter)
NOT_IMPLEMENTED(JoystickGetMinRange)
NOT_IMPLEMENTED(JoystickGetMaxRange)
NOT_IMPLEMENTED(JoystickGetCenter)

static const struct luaL_Reg Functions[] = 
    {
        { "joystick_get_num_axes", JoystickGetNumAxes },
        { "joystick_get_num_buttons", JoystickGetNumButtons },
        { "joystick_not_working", JoystickNotWorking },
        { "joystick_get_dead_band", JoystickGetDeadBand },
        { "joystick_set_dead_band", JoystickSetDeadBand },
        { "joystick_get_saturation", JoystickGetSaturation },
        { "joystick_set_saturation", JoystickSetSaturation },
        { "joystick_set_min_range", JoystickSetMinRange },
        { "joystick_set_max_range", JoystickSetMaxRange },
        { "joystick_set_center", JoystickSetCenter },
        { "joystick_get_min_range", JoystickGetMinRange },
        { "joystick_get_max_range", JoystickGetMaxRange },
        { "joystick_get_center", JoystickGetCenter },
        { NULL, NULL } /* sentinel */
    };

void moonglut_open_joystick(lua_State *L)
    {
    luaL_setfuncs(L, Functions, 0);
    }
#else

void moonglut_open_joystick(lua_State *L)
    {
    (void)L; /*unused*/
    }

#endif
