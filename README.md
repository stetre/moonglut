##MoonGLUT: Lua bindings for FreeGLUT

MoonGLUT is a Lua binding library for [FreeGLUT](http://freeglut.sourceforge.net/).

It runs on GNU/Linux and requires [Lua](http://www.lua.org/) (>=5.3)
and [FreeGLUT](http://freeglut.sourceforge.net/index.php#download) (>=3.0.0).

_Authored by:_ _[Stefano Trettel](https://www.linkedin.com/in/stetre)_

[![Lua logo](./doc/powered-by-lua.gif)](http://www.lua.org/)

#### License

MIT/X11 license (same as Lua). See [LICENSE](./LICENSE).

#### Documentation, Getting and installing, etc.

See the [Reference Manual](https://stetre.github.io/moonglut/doc/index.html).

#### Example

```lua
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
```

The script can be executed at the shell prompt with the standard Lua interpreter:

```shell
$ lua hello.lua
```

Other examples can be found in the **examples/** directory contained in the release package.
