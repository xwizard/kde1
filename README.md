1de
===
Currently it contains only Qt-1.45 patched to build with gcc4.
Most examples work, two or three segfault. Currently it's not an issue.

Legal issues
===
As Qt License state, its sources cannot be modified,
which obviously had to be done in order to build it
with modern toolchain. I'm going to contact Qt owner
to clarify situation soon :)

Build order
===
qt
kdesupport
kdelibs
kdebase
kdeadmin

Todo
===
Fix kdebase/kaudio build
Fix kdeadmin/kuser build
