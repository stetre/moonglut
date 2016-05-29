
## How to install MoonGLUT

### On Ubuntu

Install Lua as described in the installation instructions for 
[MoonFLTK](https://github.com/stetre/moonfltk/).

Install FreeGLUT:

```sh
$ sudo apt-get install freeglut3-dev
```

Download MoonGLUT's [latest release](https://github.com/stetre/moonglut/releases)
(e.g. moonglut-0.1.tar.gz).

```sh
$ tar -zxpvf moonglut-0.1.tar.gz
$ cd moonglut-0.1
moonglut-0.1$ make
moonglut-0.1$ sudo make install
```

### On Windows with MSYS2/MinGW

Set up the MSYS2/MinGW environment and install Lua as described in the installation 
instructions for [MoonFLTK](https://github.com/stetre/moonfltk/).

Install FreeGLUT:

```sh
$ pacman -S mingw-w64-i686-freeglut      # (32-bit)
$ pacman -S mingw-w64-x86_64-freeglut    # (64-bit)
```

Download MoonGLUT's [latest release](https://github.com/stetre/moonglut/releases)
(e.g. moonglut-0.1.tar.gz).

```sh
$ tar -zxpvf moonglut-0.1.tar.gz
$ cd moonglut-0.1
moonglut-0.1$ make platform=mingw
moonglut-0.1$ make install platform=mingw
```

