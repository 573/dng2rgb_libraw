Prerequisites for Windows users
---

You need to install Mingw (compilers) and msys on your system to compile with `g++`. Personally I prefer the [mingw-get-inst](http://sourceforge.net/projects/mingw/files/Automated%20MinGW%20Installer/mingw-get-inst/) tool, where I have the opportunity to add/remove packages later on (`mingw-get --help` once installed), installing a basic set first, two hints: Take the `Use pre-packaged repository catalogues` option on the third installer page and choose at least `MinGW Compiler Suite >> C Compiler`, `MinGW Compiler Suite >> C++ Compiler` and `MSYS Basic System` on the seventh one. Start the shell by using the `msys.bat` file.

This seems the most consistent/recommended/assumed* (* by other projects I make use of) way of using unix/posix tools on Windows in my opinion, after trying other distributions in the past. Unless you plan 64-Bit support, git* (* I installed msysgit in an extra folder side-by-side, because mixing up wasn't maintainable for me) hacking or similar, take this approach.

Install `libraw` stuff: Load the [source archive](http://www.libraw.org/download#stable), e. g. `LibRaw-0.13.2.zip` to some folder, lets say `e:\temp` and unpack it there. In the msys shell you started, change to the folder location where you have the unpacked sources and type:

    mingw32-make -f Makefile.mingw

Assumed your mingw/msys is installed in `h:\mingw`/`h:\mingw\msys\1.0` make a sub-directory local in `h:\mingw\msys\1.0` and then copy the libraw.a file (in folder `lib` of the sources) to `h:\mingw\msys\1.0\local\lib\` and the folder `libraw` in the sources folder as it is to `h:\mingw\msys\1.0\local\include`.

You may use the `.project` file for opening/building the app in [CodeLite IDE](http://www.codelite.org/): Create a new workspace there (`Workspace >> New Workspace`) and add the project (`Workspace >> Add an existing project`). Now hit `Rebuild` simply (context menu on the new project in the `Workspace` view).

You may also use the `Makefile.mingw` from the source distribution as a model to build your own `libraw` apps, as it contains all the needed compiler/linker switches and parameters already, personally I derived the CodeLite project configuration file from it.

Optional steps
---

In case you're using the `pkg-config` tool [available as a bundle here](http://ftp.gnome.org/pub/GNOME/binaries/win32/glade3/3.6/glade3-3.6.7-with-GTK+.exe) already it could make sense to copy the pc files too, but that step is optional, here is what I did:

    cp /e/temp/LibRaw-0.13.2/libraw_r.pc.in /h/mingw/msys/1.0/local/lib/pkgconfig/libraw_r.pc
	cp /e/temp/LibRaw-0.13.2/libraw.pc.in /h/mingw/msys/1.0/local/lib/pkgconfig/libraw.pc

and changed the lines to (`libraw.pc` as an example):

    prefix=/usr/local
	exec_prefix=${prefix}
	libdir=${exec_prefix}/lib
	includedir=${prefix}/include
	
	Name: libraw
	Description: Raw image decoder library (non-thread-safe)
	Version: 0.13.2
	Libs: -L${libdir} -lraw -lws2_32 -lm -lstdc++
	Cflags: -I${includedir}/libraw -w -DLIBRAW_NODLL -DLIBRAW_NOTHREADS

Then the `PKG_CONFIG_PATH` environment variable has to include this new path:
    
    $ echo $PKG_CONFIG_PATH
	H:/Gtk+/lib/pkgconfig;H:/MinGW/msys/1.0/local/lib/pkgconfig

vim: filetype=markdown
