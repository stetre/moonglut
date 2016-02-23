-- MoonGLUT example: timer.lua

glut = require("moonglut")

glut.init()
glut.init_context(3, 3, "core")
glut.init_window_size(400, 300)
glut.init_window_position(200, 200)
glut.create_window("Timer example");

local interval = 1000 -- msec
local last_time = 0

function expired(arg)
   local now = glut.elapsed_time()
   if arg ~= 0 then
      print(string.format("Timer expired (elapsed %g msec)", now - last_time))
   end
   glut.timer_func(interval, expired, 1)
   last_time = now
end

glut.timer_func(0, expired, 0)

glut.main_loop()
