-- Script: hello.lua

glut = require("moonglut")

glut.init(arg)
glut.init_context(3, 3, "core")
glut.init_display_mode("rgb", "double", "depth")

glut.init_window_size(400, 300)
glut.init_window_position(200, 200)
glut.create_window("Hello world!");

glut.display_func(function() 
   print ("rendering function")
end)

glut.main_loop()
