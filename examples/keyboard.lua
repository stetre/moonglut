-- Script: keyboard.lua

glut = require("moonglut")

glut.init()
glut.init_context(3, 3, "core")

glut.init_window_size(400, 200)
glut.init_window_position(100, 100)
glut.create_window("Keyboard callbacks");

glut.keyboard_func(function(id, key, x, y, code)
   print("keyboard:", key, x, y, code)
   if key == "esc" then
      print("Unregistering keyboard callbacks")
      glut.keyboard_func()
      glut.keyboard_up_func()
      glut.special_func()
      glut.special_up_func()
   end
end)

glut.keyboard_up_func(function(id, key, x, y, code)
   print("keyboard up:", key, x, y, code)
end)

glut.special_func(function(id, key, x, y, code)
   print("special:", key, x, y, code)
end)

glut.special_up_func(function(id, key, x, y, code)
   print("special up:", key, x, y, code)
end)

print("press any key, or ESC to unregister the callbacks")

glut.main_loop()
