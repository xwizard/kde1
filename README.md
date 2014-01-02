KDE1
===
Currently it contains working (more or less) kdebase, admin, games, graphics.
Qt-1.45 patched to build with gcc4.
Most Qt examples work, two or three segfault. Currently it's not an issue.

Issues
===
- No UTF.
- Mouse scroll doesn't work
- Keyboard layouts doesn't work
- Sometimes crashes during launch
If you find any other issues - leave a sign in issues list

Legal issues
===
As Qt License state, its sources cannot be modified,
which obviously had to be done in order to build it
with modern toolchain. I don't care ;)

Build order
===
- qt
- kdesupport
- kdelibs
- kdebase
- kdeadmin and the rest in any order

Todo
===
- Fix kdebase/kaudio build
- Fix kdeadmin/kuser build
- Move todos to issue list :)
- Fix kdeutils/kfloppy build
