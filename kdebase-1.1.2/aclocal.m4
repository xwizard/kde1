dnl aclocal.m4 generated automatically by aclocal 1.4

dnl Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY, to the extent permitted by law; without
dnl even the implied warranty of MERCHANTABILITY or FITNESS FOR A
dnl PARTICULAR PURPOSE.


dnl    This file is part of the KDE libraries/packages
dnl    Copyright (C) 1997 Janos Farkas (chexum@shadow.banki.hu)
dnl              (C) 1997,98,99 Stephan Kulow (coolo@kde.org)

dnl    This file is free software; you can redistribute it and/or
dnl    modify it under the terms of the GNU Library General Public
dnl    License as published by the Free Software Foundation; either
dnl    version 2 of the License, or (at your option) any later version.

dnl    This library is distributed in the hope that it will be useful,
dnl    but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl    Library General Public License for more details.

dnl    You should have received a copy of the GNU Library General Public License
dnl    along with this library; see the file COPYING.LIB.  If not, write to
dnl    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
dnl    Boston, MA 02111-1307, USA.        

dnl IMPORTANT NOTE:
dnl Please do not modify this file unless you expect your modifications to be
dnl carried into every other module in the repository. If you decide that you
dnl really want to modify it, contact coolo@kde.org mentioning that you have
dnl and that the modified file should be committed to every module.
dnl
dnl Single-module modifications are best placed in configure.in for kdelibs
dnl and kdebase or configure.in.in if present.


dnl ------------------------------------------------------------------------
dnl Find a file (or one of more files in a list of dirs)
dnl ------------------------------------------------------------------------
dnl
AC_DEFUN(AC_FIND_FILE,
[
$3=NO
for i in $2;
do
  for j in $1;
  do
    if test -r "$i/$j"; then
      $3=$i
      break 2
    fi
  done
done
])

AC_DEFUN(KDE_FIND_PATH,
[
   AC_MSG_CHECKING([for $1])
   AC_CACHE_VAL(kde_cv_path_$1,
   [
     kde_cv_path_$1="NONE"
     if test -n "$$2"; then
        kde_cv_path_$1="$$2";
     else
	dirs="$3"
	kde_save_IFS=$IFS
	IFS=':'
	for dir in $PATH; do
	  dirs="$dirs $dir"
        done
	IFS=$kde_save_IFS

        for dir in $dirs; do
	  if test -x "$dir/$1"; then
	    if test -n "$5"
	    then
              evalstr="$dir/$1 $5 2>&1 "
	      if eval $evalstr; then
                kde_cv_path_$1="$dir/$1"
                break
	      fi
            else
		kde_cv_path_$1="$dir/$1"
                break
	    fi
          fi
	done

     fi
         
   ])

   if test -z "$kde_cv_path_$1" || test "$kde_cv_path_$1" = "NONE"; then
      AC_MSG_RESULT(not found)
      $4
   else 
     AC_MSG_RESULT($kde_cv_path_$1)
     $2=$kde_cv_path_$1
   fi
])

AC_DEFUN(KDE_MOC_ERROR_MESSAGE,
[
    AC_MSG_ERROR([No Qt meta object compiler (moc) found!
Please check whether you installed Qt correctly. 
You need to have a running moc binary.
configure tried to run $ac_cv_path_moc and the test didn't
succeed. If configure shouldn't have tried this one, set
the environment variable MOC to the right one before running
configure.
])
])

dnl ------------------------------------------------------------------------
dnl Find the meta object compiler in the PATH, in $QTDIR/bin, and some
dnl more usual places
dnl ------------------------------------------------------------------------
dnl
AC_DEFUN(AC_PATH_QT_MOC,
[
   KDE_FIND_PATH(moc, MOC, [$ac_qt_bindir $QTDIR/bin \
	    /usr/bin /usr/X11R6/bin /usr/lib/qt/bin \
	    /usr/local/qt/bin], [KDE_MOC_ERROR_MESSAGE])
 
   if test -z "$MOC"; then
     if test -n "$ac_cv_path_moc"; then
       output=`eval "$ac_cv_path_moc --help 2>&1 | sed -e '1q' | grep Qt"`
     fi
     echo "configure:__oline__: tried to call $ac_cv_path_moc --help 2>&1 | sed -e '1q' | grep Qt" >&AC_FD_CC
     echo "configure:__oline__: moc output: $output" >&AC_FD_CC

     if test -z "$output"; then
       KDE_MOC_ERROR_MESSAGE
    fi
   fi
   
   AC_SUBST(MOC)
])

AC_DEFUN(KDE_REPLACE_ROOT,
  $1=`echo "$$1" | sed -e "s#^/#\$\{install_root\}/#"`
)

AC_DEFUN(KDE_CHECK_PATH_HEADERS,
[
    AC_MSG_CHECKING([for KDE headers installed])
    AC_LANG_CPLUSPLUS
cat > conftest.$ac_ext <<EOF
#include <stdio.h>
#include "confdefs.h"
#include <kapp.h>

int main() {
    printf("kde_htmldir=\\"%s\\"\n", KApplication::kde_htmldir().data());
    printf("kde_appsdir=\\"%s\\"\n", KApplication::kde_appsdir().data());
    printf("kde_icondir=\\"%s\\"\n", KApplication::kde_icondir().data());
    printf("kde_sounddir=\\"%s\\"\n", KApplication::kde_sounddir().data());
    printf("kde_datadir=\\"%s\\"\n", KApplication::kde_datadir().data());
    printf("kde_locale=\\"%s\\"\n", KApplication::kde_localedir().data());
    printf("kde_cgidir=\\"%s\\"\n", KApplication::kde_cgidir().data());
    printf("kde_confdir=\\"%s\\"\n", KApplication::kde_configdir().data());
    printf("kde_mimedir=\\"%s\\"\n", KApplication::kde_mimedir().data());
    printf("kde_toolbardir=\\"%s\\"\n", KApplication::kde_toolbardir().data());
    printf("kde_wallpaperdir=\\"%s\\"\n", 
	KApplication::kde_wallpaperdir().data());
    printf("kde_bindir=\\"%s\\"\n", KApplication::kde_bindir().data());
    printf("kde_partsdir=\\"%s\\"\n", KApplication::kde_partsdir().data());
    return 0;
    }
EOF

ac_compile='${CXX-g++} -c $CXXFLAGS $all_includes $CPPFLAGS conftest.$ac_ext'
if AC_TRY_EVAL(ac_compile); then
  AC_MSG_RESULT(yes)
else
  AC_MSG_ERROR([your system is not able to compile a small KDE application!
Check, if you installed the KDE header files correctly.])
fi
])

AC_DEFUN(AC_CREATE_KFSSTND,
[
AC_REQUIRE([AC_CHECK_RPATH])
AC_REQUIRE([AC_CHECK_BOOL])

AC_MSG_CHECKING([for KDE paths])
kde_result=""

AC_CACHE_VAL(kde_cv_all_paths,
[
if test "$1" = "default"; then

  if test -z "$kde_htmldir"; then
    kde_htmldir='\$(prefix)/share/doc/HTML'
  fi
  if test -z "$kde_appsdir"; then
    kde_appsdir='\$(prefix)/share/applnk'
  fi
  if test -z "$kde_icondir"; then
    kde_icondir='\$(prefix)/share/icons'
  fi
  if test -z "$kde_sounddir"; then
    kde_sounddir='\$(prefix)/share/sounds'
  fi
  if test -z "$kde_datadir"; then
    kde_datadir='\$(prefix)/share/apps'
  fi
  if test -z "$kde_locale"; then
    kde_locale='\$(prefix)/share/locale'
  fi
  if test -z "$kde_cgidir"; then
    kde_cgidir='\$(exec_prefix)/cgi-bin'
  fi
  if test -z "$kde_confdir"; then
    kde_confdir='\$(prefix)/share/config'
  fi
  if test -z "$kde_mimedir"; then
    kde_mimedir='\$(prefix)/share/mimelnk'
  fi
  if test -z "$kde_toolbardir"; then
    kde_toolbardir='\$(prefix)/share/toolbar'
  fi
  if test -z "$kde_wallpaperdir"; then
    kde_wallpaperdir='\$(prefix)/share/wallpapers'
  fi
  if test -z "$kde_bindir"; then
    kde_bindir='\$(exec_prefix)/bin'
  fi
  if test -z "$kde_partsdir"; then
    kde_partsdir='\$(exec_prefix)/parts'
  fi

  kde_cv_all_paths="kde_have_all_paths=\"yes\" \
	kde_htmldir=\"$kde_htmldir\" \
	kde_appsdir=\"$kde_appsdir\" \
	kde_icondir=\"$kde_icondir\" \
	kde_sounddir=\"$kde_sounddir\" \
	kde_datadir=\"$kde_datadir\" \
	kde_locale=\"$kde_locale\" \
	kde_cgidir=\"$kde_cgidir\" \
	kde_confdir=\"$kde_confdir\" \
	kde_mimedir=\"$kde_mimedir\" \
	kde_toolbardir=\"$kde_toolbardir\" \
	kde_wallpaperdir=\"$kde_wallpaperdir\" \
	kde_bindir=\"$kde_bindir\" \
	kde_partsdir=\"$kde_partsdir\" \
	kde_result=defaults"

else 

AC_MSG_RESULT([compiling])

KDE_CHECK_PATH_HEADERS

KDE_TEST_RPATH=

if test -n "$USE_RPATH"; then

  if test -n "$kde_libraries"; then
    KDE_TEST_RPATH="-rpath $kde_libraries"
  fi

  if test -n "$qt_libraries"; then
    KDE_TEST_RPATH="$KDE_TEST_RPATH -rpath $qt_libraries"
  fi

  if test -n "$x_libraries"; then
    KDE_TEST_RPATH="$KDE_TEST_RPATH -rpath $x_libraries"
  fi

  KDE_TEST_RPATH="$KDE_TEST_RPATH $KDE_EXTRA_RPATH"
fi

AC_MSG_CHECKING([for KDE libraries installed])
ac_link='/bin/sh ./libtool --silent --mode=link ${CXX-g++} -o conftest $CXXFLAGS $all_includes $CPPFLAGS $LDFLAGS $all_libraries conftest.$ac_ext $LIBS -lkdecore $LIBQT $KDE_TEST_RPATH 1>&5'

if AC_TRY_EVAL(ac_link) && test -s conftest; then 
  AC_MSG_RESULT(yes)
else
  AC_MSG_ERROR([your system fails at linking a small KDE application!
Check, if your compiler is installed correctly and if you have used the
same compiler to compile Qt and kdelibs as you did use now])
fi

if eval `KDEDIR= ./conftest 2>&5`; then
  kde_result=done
else
  kde_result=problems
fi

KDEDIR= ./conftest 2> /dev/null >&5 # make an echo for config.log
kde_have_all_paths=yes
AC_LANG_CPLUSPLUS

if test "$kde_have_all_paths" = "yes"; then
kde_cv_all_paths="kde_have_all_paths=\"yes\" \
	kde_htmldir=\"$kde_htmldir\" \
	kde_appsdir=\"$kde_appsdir\" \
	kde_icondir=\"$kde_icondir\" \
	kde_sounddir=\"$kde_sounddir\" \
	kde_datadir=\"$kde_datadir\" \
	kde_locale=\"$kde_locale\" \
	kde_cgidir=\"$kde_cgidir\" \
	kde_confdir=\"$kde_confdir\" \
	kde_mimedir=\"$kde_mimedir\" \
	kde_toolbardir=\"$kde_toolbardir\" \
	kde_wallpaperdir=\"$kde_wallpaperdir\" \
	kde_bindir=\"$kde_bindir\" \
	kde_partsdir=\"$kde_partsdir\" \
	kde_result=$kde_result"
fi
rm -fr conftest*

fi
])

eval "$kde_cv_all_paths"

if test -z "$kde_htmldir" || test -z "$kde_appsdir" ||
   test -z "$kde_icondir" || test -z "$kde_sounddir" ||
   test -z "$kde_datadir" || test -z "$kde_locale"  ||
   test -z "$kde_cgidir"  || test -z "$kde_confdir" ||
   test -z "$kde_mimedir" || test -z "$kde_toolbardir" ||
   test -z "$kde_wallpaperdir" || test -z "$kde_bindir" ||
   test -z "$kde_partsdir" || test "$kde_have_all_paths" != "yes"; then
  kde_have_all_paths=no
  AC_MSG_ERROR([configure could not run a little KDE program to test the environment. 
Since it had compiled and linked before, it must be a strange problem on your system.
Look at config.log for details. If you are not able to fix this, look at
http://www.kde.org/faq/installation.html or any www.kde.org mirror.
(If you're using an egcs version on Linux, you may update binutils!)
])
else
  AC_MSG_RESULT($kde_result)
fi

if test -n "$install_root"; then
  KDE_REPLACE_ROOT(kde_htmldir)
  KDE_REPLACE_ROOT(kde_appsdir)
  KDE_REPLACE_ROOT(kde_icondir)
  KDE_REPLACE_ROOT(kde_sounddir)
  KDE_REPLACE_ROOT(kde_datadir)
  KDE_REPLACE_ROOT(kde_locale)
  KDE_REPLACE_ROOT(kde_cgidir)
  KDE_REPLACE_ROOT(kde_confdir)
  KDE_REPLACE_ROOT(kde_mimedir)
  KDE_REPLACE_ROOT(kde_toolbardir)
  KDE_REPLACE_ROOT(kde_wallpaperdir)
  KDE_REPLACE_ROOT(kde_bindir)
  KDE_REPLACE_ROOT(kde_partsdir)
  AC_SUBST(install_root)
fi

bindir=$kde_bindir

])

AC_DEFUN(AC_SUBST_KFSSTND,
[
AC_SUBST(kde_htmldir)
AC_SUBST(kde_appsdir)
AC_SUBST(kde_icondir)
AC_SUBST(kde_sounddir)
kde_minidir="$kde_icondir/mini"
AC_SUBST(kde_minidir)
AC_SUBST(kde_datadir)
AC_SUBST(kde_locale)
AC_SUBST(kde_cgidir)
AC_SUBST(kde_confdir)
AC_SUBST(kde_mimedir)
AC_SUBST(kde_toolbardir)
AC_SUBST(kde_wallpaperdir)
AC_SUBST(kde_bindir)
AC_SUBST(kde_partsdir)
])

AC_DEFUN(KDE_MISC_TESTS,
[
   AC_LANG_C
   dnl Checks for libraries. 
   AC_CHECK_LIB(compat, main, [LIBCOMPAT="-lcompat"]) dnl for FreeBSD
   AC_SUBST(LIBCOMPAT)
   AC_CHECK_LIB(crypt, main, [LIBCRYPT="-lcrypt"]) dnl for BSD
   AC_SUBST(LIBCRYPT)
   AC_CHECK_KSIZE_T
   AC_LANG_C
   AC_CHECK_LIB(dnet, dnet_ntoa, [X_EXTRA_LIBS="$X_EXTRA_LIBS -ldnet"])
   if test $ac_cv_lib_dnet_dnet_ntoa = no; then
      AC_CHECK_LIB(dnet_stub, dnet_ntoa,
        [X_EXTRA_LIBS="$X_EXTRA_LIBS -ldnet_stub"])
   fi
   AC_CHECK_FUNC(inet_ntoa)
   if test $ac_cv_func_inet_ntoa = no; then
     AC_CHECK_LIB(nsl, inet_ntoa, X_EXTRA_LIBS="$X_EXTRA_LIBS -lnsl")
   fi
   AC_CHECK_FUNC(connect)
   if test $ac_cv_func_connect = no; then
      AC_CHECK_LIB(socket, connect, X_EXTRA_LIBS="-lsocket $X_EXTRA_LIBS", ,
        $X_EXTRA_LIBS)
   fi

   AC_CHECK_FUNC(remove)
   if test $ac_cv_func_remove = no; then
      AC_CHECK_LIB(posix, remove, X_EXTRA_LIBS="$X_EXTRA_LIBS -lposix")
   fi
 
   # BSDI BSD/OS 2.1 needs -lipc for XOpenDisplay.
   AC_CHECK_FUNC(shmat)
   if test $ac_cv_func_shmat = no; then
     AC_CHECK_LIB(ipc, shmat, X_EXTRA_LIBS="$X_EXTRA_LIBS -lipc")
   fi

   LIBSOCKET="$X_EXTRA_LIBS"
   AC_SUBST(LIBSOCKET)
   AC_SUBST(X_EXTRA_LIBS)
   AC_CHECK_LIB(ucb, killpg, [LIBUCB="-lucb"]) dnl for Solaris2.4
   AC_SUBST(LIBUCB)

   case $host in  dnl this *is* LynxOS specific
   *-*-lynxos* )
        AC_MSG_CHECKING([LynxOS header file wrappers])
        [CFLAGS="$CFLAGS -D__NO_INCLUDE_WARN__"]
        AC_MSG_RESULT(disabled)
        AC_CHECK_LIB(bsd, gethostbyname, [LIBSOCKET="-lbsd"]) dnl for LynxOS
         ;;
    esac

])

dnl ------------------------------------------------------------------------
dnl Find the header files and libraries for X-Windows. Extended the 
dnl macro AC_PATH_X
dnl ------------------------------------------------------------------------
dnl
AC_DEFUN(K_PATH_X,
[
AC_REQUIRE([AC_PROG_CPP])
AC_MSG_CHECKING(for X)
AC_LANG_SAVE
AC_LANG_C
AC_CACHE_VAL(ac_cv_have_x,
[# One or both of the vars are not set, and there is no cached value.
if test "{$x_includes+set}" = set || test "$x_includes" = NONE; then
   ac_x_includes=NO
else
   ac_x_includes=$x_includes
fi
if test "{$x_libraries+set}" = set || test "$x_libraries" = NONE; then
   ac_x_libraries=NO
else
   ac_x_libraries=$x_libraries
fi
AC_PATH_X_DIRECT
if test "$ac_x_includes" = NO ||  test "$ac_x_libraries" = NO; then
  AC_PATH_X_XMKMF
# I had too many reports about broken xmkmfs that I don't care about
# empty output of xmkmf any longer
  test -z "$ac_x_includes" && ac_x_includes=NO
  test -z "$ac_x_libraries" && ac_x_libraries=NO
fi

if test "$ac_x_includes" = NO; then
  AC_MSG_ERROR([Can't find X includes. Please check your installation and add the correct paths!])
fi

if test "$ac_x_libraries" = NO; then
  AC_MSG_ERROR([Can't find X libraries. Please check your installation and add the correct paths!])
fi

# Record where we found X for the cache.
ac_cv_have_x="have_x=yes \
         ac_x_includes=$ac_x_includes ac_x_libraries=$ac_x_libraries"
])dnl
eval "$ac_cv_have_x"
 
if test "$have_x" != yes; then
  AC_MSG_RESULT($have_x)
  no_x=yes
else
  AC_MSG_RESULT([libraries $ac_x_libraries, headers $ac_x_includes])
fi

if test -z "$ac_x_includes" || test "x$ac_x_includes" = xNONE; then
  X_INCLUDES=""
  x_includes="."; dnl better than nothing :-
 else
  x_includes=$ac_x_includes
  X_INCLUDES="-I$x_includes"
fi

if test -z "$ac_x_libraries" || test "x$ac_x_libraries" = xNONE; then
  X_LDFLAGS=""
  x_libraries="/usr/lib"; dnl better than nothing :-
 else
  x_libraries=$ac_x_libraries
  X_LDFLAGS="-L$x_libraries"
fi
all_includes="$all_includes $X_INCLUDES"  
all_libraries="$all_libraries $X_LDFLAGS"  

AC_SUBST(X_INCLUDES)
AC_SUBST(X_LDFLAGS)
AC_SUBST(x_libraries)
AC_SUBST(x_includes)

LIB_X11='-lX11 $(LIBSOCKET)'
AC_SUBST(LIB_X11)

AC_LANG_RESTORE
])

AC_DEFUN(KDE_PRINT_QT_PROGRAM,
[
AC_LANG_CPLUSPLUS
cat > conftest.$ac_ext <<EOF
#include "confdefs.h"
#include <qglobal.h>
#include <qapplication.h>
#include <qobjcoll.h>

#if ! (QT_VERSION >= 142)
#error 1
#endif

int main() {
    return 0;
}
EOF
])

AC_DEFUN(KDE_CHECK_QT_DIRECT,
[
AC_MSG_CHECKING([if Qt compiles without flags])
AC_CACHE_VAL(kde_cv_qt_direct,
[
ac_LD_LIBRARY_PATH_safe=$LD_LIBRARY_PATH
ac_LIBRARY_PATH="$LIBRARY_PATH"
ac_cxxflags_safe="$CXXFLAGS"
ac_ldflags_safe="$LDFLAGS"
ac_libs_safe="$LIBS"

CXXFLAGS="$CXXFLAGS -I$qt_includes"
LDFLAGS="$X_LDFLAGS"
LIBS="-lqt -lXext -lX11 $LIBSOCKET"
LD_LIBRARY_PATH=
export LD_LIBRARY_PATH
LIBRARY_PATH=
export LIBRARY_PATH

KDE_PRINT_QT_PROGRAM

if AC_TRY_EVAL(ac_link) && test -s conftest; then
  kde_cv_qt_direct="yes"
else
  kde_cv_qt_direct="no"
  echo "configure: failed program was:" >&AC_FD_CC
  cat conftest.$ac_ext >&AC_FD_CC
fi
rm -f conftest*
CXXFLAGS="$ac_cxxflags_safe"
LDFLAGS="$ac_ldflags_safe"
LIBS="$ac_libs_safe"

LD_LIBRARY_PATH="$ac_LD_LIBRARY_PATH_safe"
export LD_LIBRARY_PATH
LIBRARY_PATH="$ac_LIBRARY_PATH"
export LIBRARY_PATH
])

if test "$kde_cv_qt_direct" = "yes"; then
  AC_MSG_RESULT(yes)
  $1
else
  AC_MSG_RESULT(no)
  $2
fi
])

dnl ------------------------------------------------------------------------
dnl Try to find the Qt headers and libraries.
dnl $(QT_LDFLAGS) will be -Lqtliblocation (if needed)
dnl and $(QT_INCLUDES) will be -Iqthdrlocation (if needed)
dnl ------------------------------------------------------------------------
dnl
AC_DEFUN(AC_PATH_QT_1_3,
[
AC_REQUIRE([K_PATH_X])

AC_MSG_CHECKING([for Qt])
LIBQT="-lqt -lXext -lX11 $LIBSOCKET"
ac_qt_includes=NO ac_qt_libraries=NO ac_qt_bindir=NO
qt_libraries=""
qt_includes=""
AC_ARG_WITH(qt-dir,
    [  --with-qt-dir=DIR       where the root of Qt is installed ],
    [  ac_qt_includes="$withval"/include
       ac_qt_libraries="$withval"/lib
       ac_qt_bindir="$withval"/bin
    ])

AC_ARG_WITH(qt-includes,
    [  --with-qt-includes=DIR  where the Qt includes are. ],
    [  
       ac_qt_includes="$withval"
    ])
    
kde_qt_libs_given=no

AC_ARG_WITH(qt-libraries,
    [  --with-qt-libraries=DIR where the Qt library is installed.],
    [  ac_qt_libraries="$withval"
       kde_qt_libs_given=yes
    ])

AC_CACHE_VAL(ac_cv_have_qt,
[#try to guess Qt locations

qt_incdirs="$ac_qt_includes /usr/lib/qt/include /usr/local/qt/include /usr/include/qt /usr/include /usr/X11R6/include/X11/qt $x_includes $QTINC"
test -n "$QTDIR" && qt_incdirs="$QTDIR/include $QTDIR $qt_incdirs"
AC_FIND_FILE(qmovie.h, $qt_incdirs, qt_incdir)
ac_qt_includes="$qt_incdir"

if test ! "$ac_qt_libraries" = "NO"; then
  qt_libdirs="$ac_qt_libraries"
fi

qt_libdirs="$qt_libdirs /usr/lib/qt/lib /usr/X11R6/lib /usr/lib /usr/local/qt/lib /usr/lib/qt $x_libraries $QTLIB"
test -n "$QTDIR" && qt_libdirs="$QTDIR/lib $QTDIR $qt_libdirs"

test=NONE
qt_libdir=NONE
for dir in $qt_libdirs; do
  try="ls -1 $dir/libqt*"
  if test=`eval $try 2> /dev/null`; then qt_libdir=$dir; break; else echo "tried $dir" >&AC_FD_CC ; fi
done

dnl AC_FIND_FILE(libqt.so libqt.so.1.40 libqt.so.1.41 libqt.so.1.42 libqt.so.1 libqt.a libqt.sl, $qt_libdirs, qt_libdir)
ac_qt_libraries="$qt_libdir"

ac_cxxflags_safe="$CXXFLAGS"
ac_ldflags_safe="$LDFLAGS"
ac_libs_safe="$LIBS"

CXXFLAGS="$CXXFLAGS -I$qt_incdir $all_includes"
LDFLAGS="-L$qt_libdir $all_libraries"
LIBS="$LIBS $LIBQT"

KDE_PRINT_QT_PROGRAM

if AC_TRY_EVAL(ac_link) && test -s conftest; then
  rm -f conftest*
else
  echo "configure: failed program was:" >&AC_FD_CC
  cat conftest.$ac_ext >&AC_FD_CC
  ac_qt_libraries="NO"
fi
rm -f conftest*
CXXFLAGS="$ac_cxxflags_safe"
LDFLAGS="$ac_ldflags_safe"
LIBS="$ac_libs_safe"

if test "$ac_qt_includes" = NO || test "$ac_qt_libraries" = NO; then
  ac_cv_have_qt="have_qt=no"
  ac_qt_notfound=""
  if test "$ac_qt_includes" = NO; then
    if test "$ac_qt_libraries" = NO; then
      ac_qt_notfound="(headers and libraries)";
    else
      ac_qt_notfound="(headers)";
    fi
  else
    ac_qt_notfound="(libraries)";
  fi

  AC_MSG_ERROR([Qt >= 1.42 $ac_qt_notfound not found. Please check your installation! ]);
else
  have_qt="yes"
fi
])

eval "$ac_cv_have_qt"

if test "$have_qt" != yes; then
  AC_MSG_RESULT([$have_qt]);
else
  ac_cv_have_qt="have_qt=yes \
    ac_qt_includes=$ac_qt_includes ac_qt_libraries=$ac_qt_libraries"
  AC_MSG_RESULT([libraries $ac_qt_libraries, headers $ac_qt_includes])
  
  qt_libraries="$ac_qt_libraries"
  qt_includes="$ac_qt_includes"
fi

if test ! "$kde_qt_libs_given" = "yes"; then
KDE_CHECK_QT_DIRECT(qt_libraries= ,[])
fi

AC_SUBST(qt_libraries)
AC_SUBST(qt_includes)

if test "$qt_includes" = "$x_includes" || test -z "$qt_includes"; then
 QT_INCLUDES="";
else
 QT_INCLUDES="-I$qt_includes"
 all_includes="$QT_INCLUDES $all_includes"
fi

if test "$qt_libraries" = "$x_libraries" || test -z "$qt_libraries"; then
 QT_LDFLAGS=""
else
 QT_LDFLAGS="-L$qt_libraries"
 all_libraries="$QT_LDFLAGS $all_libraries"
fi

AC_SUBST(QT_INCLUDES)
AC_SUBST(QT_LDFLAGS)
AC_PATH_QT_MOC

LIB_QT='-lqt $(LIB_X11)'
AC_SUBST(LIB_QT)

])

AC_DEFUN(AC_PATH_QT,
[
AC_PATH_QT_1_3
])

dnl ------------------------------------------------------------------------
dnl Now, the same with KDE
dnl $(KDE_LDFLAGS) will be the kdeliblocation (if needed)
dnl and $(kde_includes) will be the kdehdrlocation (if needed)
dnl ------------------------------------------------------------------------
dnl
AC_DEFUN(AC_BASE_PATH_KDE,
[
AC_PREREQ([2.13])
AC_REQUIRE([KDE_MISC_TESTS])
AC_REQUIRE([AC_PATH_QT])dnl
AC_MSG_CHECKING([for KDE])

if test "${prefix}" != NONE; then
  kde_includes=${prefix}/include
  ac_kde_includes=$prefix/include

  if test "${exec_prefix}" != NONE; then
    kde_libraries=${exec_prefix}/lib
    ac_kde_libraries=$exec_prefix/lib
  else
    kde_libraries=${prefix}/lib
    ac_kde_libraries=$prefix/lib
  fi
else
  ac_kde_includes=
  ac_kde_libraries=
  kde_libraries=""
  kde_includes=""
fi

AC_CACHE_VAL(ac_cv_have_kde,
[#try to guess kde locations

if test -z "$1"; then

kde_incdirs="/usr/lib/kde/include /usr/local/kde/include /usr/kde/include /usr/include/kde /usr/include /opt/kde/include $x_includes $qt_includes"
test -n "$KDEDIR" && kde_incdirs="$KDEDIR/include $KDEDIR $kde_incdirs"
kde_incdirs="$ac_kde_includes $kde_incdirs"
AC_FIND_FILE(ksock.h, $kde_incdirs, kde_incdir)
ac_kde_includes="$kde_incdir"

if test -n "$ac_kde_includes" && test ! -r "$ac_kde_includes/ksock.h"; then
  AC_MSG_ERROR([
in the prefix, you've chosen, are no KDE headers installed. This will fail.
So, check this please and use another prefix!])
fi

kde_libdirs="/usr/lib/kde/lib /usr/local/kde/lib /usr/kde/lib /usr/lib/kde /usr/lib /usr/X11R6/lib /opt/kde/lib /usr/X11R6/kde/lib"
test -n "$KDEDIR" && kde_libdirs="$KDEDIR/lib $KDEDIR $kde_libdirs"
kde_libdirs="$ac_kde_libraries $kde_libdirs"
AC_FIND_FILE(libkdecore.la, $kde_libdirs, kde_libdir)

if test -n "$ac_kde_libraries" && test ! -r "$ac_kde_libraries/libkdecore.la"; then
AC_MSG_ERROR([
in the prefix, you've chosen, are no KDE libraries installed. This will fail.
So, check this please and use another prefix!])
fi
ac_kde_libraries="$kde_libdir"

if test "$ac_kde_includes" = NO || test "$ac_kde_libraries" = NO; then
  ac_cv_have_kde="have_kde=no"
else
  ac_cv_have_kde="have_kde=yes \
    ac_kde_includes=$ac_kde_includes ac_kde_libraries=$ac_kde_libraries"
fi

else dnl test -z $1 
  
  ac_cv_have_kde="have_kde=no"

fi
])dnl

eval "$ac_cv_have_kde"

if test "$have_kde" != "yes"; then
 if test "${prefix}" = NONE; then
  ac_kde_prefix="$ac_default_prefix"
 else
  ac_kde_prefix="$prefix"
 fi
 if test "$exec_prefix" = NONE; then
  ac_kde_exec_prefix="$ac_kde_prefix"
  AC_MSG_RESULT([will be installed in $ac_kde_prefix])
 else
  ac_kde_exec_prefix="$exec_prefix"
  AC_MSG_RESULT([will be installed in $ac_kde_prefix and $ac_kde_exec_prefix])
 fi

 kde_libraries="${ac_kde_exec_prefix}/lib"
 kde_includes=${ac_kde_prefix}/include

else
  ac_cv_have_kde="have_kde=yes \
    ac_kde_includes=$ac_kde_includes ac_kde_libraries=$ac_kde_libraries"
  AC_MSG_RESULT([libraries $ac_kde_libraries, headers $ac_kde_includes])
  
  kde_libraries="$ac_kde_libraries"
  kde_includes="$ac_kde_includes"
fi
AC_SUBST(kde_libraries)
AC_SUBST(kde_includes)

if test "$kde_includes" = "$x_includes" || test "$kde_includes" = "$qt_includes" ; then
 KDE_INCLUDES=""
else
 KDE_INCLUDES="-I$kde_includes"
 all_includes="$KDE_INCLUDES $all_includes"
fi

if test "$kde_libraries" = "$x_libraries" || test "$kde_libraries" = "$qt_libraries" ; then
 KDE_LDFLAGS=""
else
 KDE_LDFLAGS="-L$kde_libraries"
 all_libraries="$KDE_LDFLAGS $all_libraries"
fi

AC_SUBST(KDE_LDFLAGS)
AC_SUBST(KDE_INCLUDES)

AC_REQUIRE([KDE_CHECK_EXTRA_LIBS])

AC_SUBST(all_includes)
AC_SUBST(all_libraries)

])

AC_DEFUN(KDE_CHECK_EXTRA_LIBS,
[
AC_MSG_CHECKING(for extra includes)
AC_ARG_WITH(extra-includes, [  --with-extra-includes=DIR
                          adds non standard include paths], 
  kde_use_extra_includes="$withval",
  kde_use_extra_includes=NONE
)
if test -n "$kde_use_extra_includes" && \
   test "$kde_use_extra_includes" != "NONE"; then

   ac_save_ifs=$IFS
   IFS=':'
   for dir in $kde_use_extra_includes; do
     all_includes="$all_includes -I$dir"
     USER_INCLUDES="$USER_INCLUDES -I$dir"
   done
   IFS=$ac_save_ifs
   kde_use_extra_includes="added"
else
   kde_use_extra_includes="no"
fi

AC_MSG_RESULT($kde_use_extra_includes)

AC_MSG_CHECKING(for extra libs)
AC_ARG_WITH(extra-libs, [  --with-extra-libs=DIR   adds non standard library paths], 
  kde_use_extra_libs=$withval,
  kde_use_extra_libs=NONE
)
if test -n "$kde_use_extra_libs" && \
   test "$kde_use_extra_libs" != "NONE"; then

   ac_save_ifs=$IFS
   IFS=':'
   for dir in $kde_use_extra_libs; do
     all_libraries="$all_libraries -L$dir"
     KDE_EXTRA_RPATH="$KDE_EXTRA_RPATH -rpath $dir"
     USER_LDFLAGS="$USER_LDFLAGS -L$dir"
   done
   IFS=$ac_save_ifs
   kde_use_extra_libs="added"
else
   kde_use_extra_libs="no"
fi

AC_MSG_RESULT($kde_use_extra_libs)

])

AC_DEFUN(KDE_CHECK_KIMGIO,
[
   AC_REQUIRE([AC_BASE_PATH_KDE])
   AC_REQUIRE([KDE_CHECK_EXTRA_LIBS])
   AC_REQUIRE([AC_FIND_TIFF])
   AC_REQUIRE([AC_FIND_JPEG]) 
   AC_REQUIRE([AC_FIND_PNG]) 
   AC_REQUIRE([KDE_CREATE_LIBS_ALIASES])
   
   if test "$1" = "existance"; then
     AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
     kde_save_LIBS="$LIBS"
     LIBS="$LIBS $all_libraries $LIBJPEG $LIBTIFF $LIBPNG $LIBQT -lm"
     AC_CHECK_LIB(kimgio, kimgioRegister, [
      LIBKIMGIO_EXISTS=yes],LIBKIMGIO_EXISTS=no)
      LIBS="$kde_save_LIBS"
      AC_LANG_RESTORE   
   else
      LIBKIMGIO_EXISTS=yes
   fi

   if test "$LIBKIMGIO_EXISTS" = "yes"; then
     LIB_KIMGIO='-lkimgio $(LIBJPEG) $(LIBTIFF) $(LIBPNG) $(LIB_QT) -lm'
     LIB_KHTMLW='-lkhtmlw $(LIB_KIMGIO) -ljscript'
   else
     LIB_KIMGIO=''
     LIB_KHTMLW='-lkhtmlw $(LIBJPEG) -ljscript $(LIB_QT)'
   fi
   AC_SUBST(LIB_KIMGIO)
   
   AC_SUBST(LIB_KHTMLW)
   LIB_KHTML='-lkhtml $(LIB_KIMGIO) -ljscript'
   AC_SUBST(LIB_KHTML)
])

AC_DEFUN(KDE_CREATE_LIBS_ALIASES,
[
   AC_REQUIRE([KDE_MISC_TESTS])
   AC_REQUIRE([K_PATH_X])

   LIB_KDECORE='-lkdecore -lXext $(LIB_QT)'
   AC_SUBST(LIB_KDECORE)
   LIB_KDEUI='-lkdeui $(LIB_KDECORE)'
   AC_SUBST(LIB_KDEUI)
   LIB_KFM='-lkfm $(LIB_KDECORE)'
   AC_SUBST(LIB_KFM)
   LIB_KFILE='-lkfile $(LIB_KFM) $(LIB_KDEUI)'
   AC_SUBST(LIB_KFILE)
   LIB_KAB='-lkab $(LIB_KIMGIO) $(LIB_KDECORE)'
   AC_SUBST(LIB_KAB)
   LIB_MEDIATOOL='-lmediatool $(LIB_KDECORE)'
   AC_SUBST(LIB_MEDIATOOL) 
])

AC_DEFUN(AC_PATH_KDE,
[
  AC_BASE_PATH_KDE
  AC_ARG_ENABLE(path-check, [  --disable-path-check    don't try to find out, where to install],
  [
  if test "$enableval" = "no"; 
    then ac_use_path_checking="default"
    else ac_use_path_checking=""
  fi
  ], [ac_use_path_checking=""]
  )

  AC_ARG_WITH(install-root, [  --with-install-root=DIR the root, where to install to [default=/]],
  [
  if test "$withval" = "no";
    then kde_install_root="";
    else kde_install_root=$withval;
  fi
  ], [kde_install_root=""]
  )
  
  if test -n "$kde_install_root"; then
     install_root="$kde_install_root"
  else
     install_root=
  fi

  AC_CREATE_KFSSTND($ac_use_path_checking)

  AC_SUBST_KFSSTND
  KDE_CREATE_LIBS_ALIASES
])

dnl slightly changed version of AC_CHECK_FUNC(setenv)
AC_DEFUN(AC_CHECK_SETENV,
[AC_MSG_CHECKING([for setenv])
AC_CACHE_VAL(ac_cv_func_setenv,
[AC_LANG_C
AC_TRY_LINK(
dnl Don't include <ctype.h> because on OSF/1 3.0 it includes <sys/types.h>
dnl which includes <sys/select.h> which contains a prototype for
dnl select.  Similarly for bzero.
[#include <assert.h>
]ifelse(AC_LANG, CPLUSPLUS, [#ifdef __cplusplus
extern "C"
#endif
])dnl
[/* We use char because int might match the return type of a gcc2
    builtin and then its argument prototype would still apply.  */
#include <stdlib.h>
], [
/* The GNU C library defines this for functions which it implements
    to always fail with ENOSYS.  Some functions are actually named
    something starting with __ and the normal name is an alias.  */
#if defined (__stub_$1) || defined (__stub___$1)
choke me
#else
setenv("TEST", "alle", 1);
#endif
], eval "ac_cv_func_setenv=yes", eval "ac_cv_func_setenv=no")])

if test "$ac_cv_func_setenv" = "yes"; then
  AC_MSG_RESULT(yes)
  AC_DEFINE_UNQUOTED(HAVE_FUNC_SETENV)
else
  AC_MSG_RESULT(no)
fi
])

AC_DEFUN(AC_CHECK_GETDOMAINNAME,
[
AC_LANG_CPLUSPLUS
save_CXXFLAGS="$CXXFLAGS"
if test "$GCC" = "yes"; then
CXXFLAGS="$CXXFLAGS -pedantic-errors"
fi
AC_MSG_CHECKING(for getdomainname)
AC_CACHE_VAL(ac_cv_func_getdomainname,
[
AC_TRY_COMPILE([
#include <stdlib.h>
#include <unistd.h>
],
[
char buffer[200];
getdomainname(buffer, 200);
],
ac_cv_func_getdomainname=yes,
ac_cv_func_getdomainname=no)
])
AC_MSG_RESULT($ac_cv_func_getdomainname)
if eval "test \"`echo $ac_cv_func_getdomainname`\" = yes"; then
  AC_DEFINE(HAVE_GETDOMAINNAME)
fi
CXXFLAGS="$save_CXXFLAGS"
])

AC_DEFUN(AC_CHECK_GETHOSTNAME,
[
AC_LANG_CPLUSPLUS
save_CXXFLAGS="$CXXFLAGS"
if test "$GCC" = "yes"; then
CXXFLAGS="$CXXFLAGS -pedantic-errors"
fi

AC_MSG_CHECKING([for gethostname])
AC_CACHE_VAL(ac_cv_func_gethostname,
[
AC_TRY_COMPILE([
#include <stdlib.h>
#include <unistd.h>
],
[
char buffer[200];
gethostname(buffer, 200);
],
ac_cv_func_gethostname=yes,
ac_cv_func_gethostname=no)
])
AC_MSG_RESULT($ac_cv_func_gethostname)
if eval "test \"`echo $ac_cv_func_gethostname`\" = yes"; then
  AC_DEFINE(HAVE_GETHOSTNAME)
fi
CXXFLAGS="$save_CXXFLAGS"
])

AC_DEFUN(AC_CHECK_USLEEP,
[
AC_LANG_CPLUSPLUS

AC_MSG_CHECKING([for usleep])
AC_CACHE_VAL(ac_cv_func_usleep,
[
ac_libs_safe="$LIBS"
LIBS="$LIBS $LIBUCB"
AC_TRY_LINK([
#include <stdlib.h>
#include <unistd.h>
],
[
usleep(200);
],
ac_cv_func_usleep=yes,
ac_cv_func_usleep=no)
])
AC_MSG_RESULT($ac_cv_func_usleep)
if eval "test \"`echo $ac_cv_func_usleep`\" = yes"; then
  AC_DEFINE(HAVE_USLEEP)
fi
LIBS="$ac_libs_safe"
])

AC_DEFUN(AC_CHECK_RANDOM,
[
AC_LANG_CPLUSPLUS

AC_MSG_CHECKING([for random])
AC_CACHE_VAL(ac_cv_func_random,
[
ac_libs_safe="$LIBS"
LIBS="$LIBS $LIBUCB"
AC_TRY_LINK([
#include <stdlib.h>
],
[
random();
],
ac_cv_func_random=yes,
ac_cv_func_random=no)
])
AC_MSG_RESULT($ac_cv_func_random)
if eval "test \"`echo $ac_cv_func_random`\" = yes"; then
  AC_DEFINE(HAVE_RANDOM)
fi
LIBS="$ac_libs_safe"
])

AC_DEFUN(AC_CHECK_FGETPWENT,
[
AC_LANG_CPLUSPLUS
save_CXXFLAGS="$CXXFLAGS"
if test "$GCC" = "yes"; then
CXXFLAGS="$CXXFLAGS -pedantic-errors"
fi
AC_MSG_CHECKING(for fgetpwent)
AC_CACHE_VAL(ac_cv_func_fgetpwent,
[
AC_TRY_COMPILE([
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
],
[
passwd *p;
FILE *f;
p = fgetpwent(f);
],
ac_cv_func_fgetpwent=yes,
ac_cv_func_fgetpwent=no)
])
AC_MSG_RESULT($ac_cv_func_fgetpwent)
if eval "test \"`echo $ac_cv_func_fgetpwent`\" = yes"; then
  AC_DEFINE(HAVE_FGETPWENT)
fi
CXXFLAGS="$save_CXXFLAGS"
])

AC_DEFUN(AC_CHECK_FGETGRENT,
[
AC_LANG_CPLUSPLUS
save_CXXFLAGS="$CXXFLAGS"
if test "$GCC" = "yes"; then
CXXFLAGS="$CXXFLAGS -pedantic-errors"
fi
AC_MSG_CHECKING(for fgetgrent)
AC_CACHE_VAL(ac_cv_func_fgetgrent,
[
AC_TRY_COMPILE([
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
],
[
group *g;
FILE *f;
g = fgetgrent(f);
],
ac_cv_func_fgetgrent=yes,
ac_cv_func_fgetgrent=no)
])
AC_MSG_RESULT($ac_cv_func_fgetgrent)
if eval "test \"`echo $ac_cv_func_fgetgrent`\" = yes"; then
  AC_DEFINE(HAVE_FGETGRENT)
fi
CXXFLAGS="$save_CXXFLAGS"
])

AC_DEFUN(AC_FIND_GIF,
   [AC_MSG_CHECKING([for giflib])
AC_CACHE_VAL(ac_cv_lib_gif,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -lgif -lX11 $LIBSOCKET"
AC_TRY_LINK(dnl
[
#ifdef __cplusplus
extern "C" {
#endif
int GifLastError(void);
#ifdef __cplusplus
}
#endif
/* We use char because int might match the return type of a gcc2
    builtin and then its argument prototype would still apply.  */
],
            [return GifLastError();],
            eval "ac_cv_lib_gif=yes",
            eval "ac_cv_lib_gif=no")
LIBS="$ac_save_LIBS"
])dnl
if eval "test \"`echo $ac_cv_lib_gif`\" = yes"; then
  AC_MSG_RESULT(yes)
  AC_DEFINE_UNQUOTED(HAVE_LIBGIF)
else
  AC_MSG_ERROR(You need giflib30. Please install the kdesupport package)
fi
])

AC_DEFUN(AC_FIND_JPEG,
   [AC_MSG_CHECKING([for jpeglib])
AC_CACHE_VAL(ac_cv_lib_jpeg,
[
AC_LANG_C
ac_save_LIBS="$LIBS"
LIBS="$all_libraries -ljpeg -lm"
AC_TRY_LINK(
[/* Override any gcc2 internal prototype to avoid an error.  */
struct jpeg_decompress_struct;
typedef struct jpeg_decompress_struct * j_decompress_ptr;
typedef int size_t;
#ifdef __cplusplus
extern "C" {
#endif
    void jpeg_CreateDecompress(j_decompress_ptr cinfo,
                                    int version, size_t structsize);
#ifdef __cplusplus
}
#endif
/* We use char because int might match the return type of a gcc2
    builtin and then its argument prototype would still apply.  */
],
            [jpeg_CreateDecompress(0L, 0, 0);],
            eval "ac_cv_lib_jpeg=-ljpeg",
            eval "ac_cv_lib_jpeg=no")
LIBS="$ac_save_LIBS"

dnl what to do, if the normal way fails:
if eval "test \"`echo $ac_cv_lib_jpeg`\" = no"; then
	if test -f "$kde_libraries/libjpeg.so"; then
	   test -f ./libjpegkde.so || $LN_S $kde_libraries/libjpeg.so ./libjpegkde.so
	   ac_cv_lib_jpeg="-L\${topdir} -ljpegkde"
	else if test -f "$kde_libraries/libjpeg.sl"; then
	   test -f ./libjpegkde.sl ||$LN_S $kde_libraries/libjpeg.sl ./libjpegkde.sl
	   ac_cv_lib_jpeg="-L\${topdir} -ljpegkde"	
	else if test -f "$kde_libraries/libjpeg.a"; then
	   test -f ./libjpegkde.a || $LN_S $kde_libraries/libjpeg.a ./libjpegkde.a
	   ac_cv_lib_jpeg="-L\${topdir} -ljpegkde"
        else
	  AC_MSG_ERROR([
You need jpeglib6a. Please install the kdesupport package.
If you have already installed kdesupport, you may have an
old libjpeg somewhere. 
In this case copy $KDEDIR/lib/libjpeg* to /usr/lib.
])
	fi
      fi
   fi
fi
])dnl
if eval "test ! \"`echo $ac_cv_lib_jpeg`\" = no"; then
  LIBJPEG="$ac_cv_lib_jpeg"
  AC_SUBST(LIBJPEG)
  AC_MSG_RESULT($ac_cv_lib_jpeg)
  AC_DEFINE_UNQUOTED(HAVE_LIBJPEG)
fi
])

AC_DEFUN(AC_FIND_ZLIB,
[
AC_REQUIRE([KDE_CHECK_EXTRA_LIBS])
AC_MSG_CHECKING([for libz])
AC_CACHE_VAL(ac_cv_lib_z,
[
AC_LANG_C
kde_save_LIBS="$LIBS"
LIBS="$all_libraries -lz $LIBSOCKET"
kde_save_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS $all_includes"
AC_TRY_LINK(dnl
[
#include<zlib.h>
],
            [return (zlibVersion() == ZLIB_VERSION); ],
            eval "ac_cv_lib_z='-lz'",
            eval "ac_cv_lib_z=no")
LIBS="$kde_save_LIBS"
CFLAGS="$kde_save_CFLAGS"
])dnl
if eval "test ! \"`echo $ac_cv_lib_z`\" = no"; then
dnl  AC_DEFINE_UNQUOTED(HAVE_LIBZ)
  LIBZ="$ac_cv_lib_z"
  AC_SUBST(LIBZ)
  AC_MSG_RESULT($ac_cv_lib_z)
else
  AC_MSG_RESULT(no)
  LIBZ=""
  AC_SUBST(LIBZ)
fi
])

AC_DEFUN(KDE_TRY_TIFFLIB,
[
AC_MSG_CHECKING([for libtiff $1])

AC_CACHE_VAL(kde_cv_libtiff_$1, 
[
AC_LANG_C
kde_save_LIBS="$LIBS"
LIBS="$all_libraries -l$1 $LIBJPEG $LIBZ -lX11 $LIBSOCKET -lm"
kde_save_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS $all_includes"

AC_TRY_LINK(dnl
[
#include<tiffio.h>
],
    [return (TIFFOpen( "", "r") == 0); ],
[
    kde_cv_libtiff_$1="-l$1 $LIBJPEG $LIBZ"
], [
    kde_cv_libtiff_$1=no
])

LIBS="$kde_save_LIBS"
CFLAGS="$kde_save_CFLAGS"

])

if test "$kde_cv_libtiff_$1" = "no"; then
    AC_MSG_RESULT(no)
    LIBTIFF=""
    $3
else
    LIBTIFF="$kde_cv_libtiff_$1"
    AC_MSG_RESULT(yes)
    AC_DEFINE_UNQUOTED(HAVE_LIBTIFF)
    $2
fi

])

AC_DEFUN(AC_FIND_TIFF,
[
AC_REQUIRE([K_PATH_X])
AC_REQUIRE([AC_FIND_ZLIB])
AC_REQUIRE([AC_FIND_JPEG])
AC_REQUIRE([KDE_CHECK_EXTRA_LIBS])

KDE_TRY_TIFFLIB(tiff, [],
   KDE_TRY_TIFFLIB(tiff34))

AC_SUBST(LIBTIFF)
])


AC_DEFUN(AC_FIND_PNG,
[
AC_REQUIRE([AC_FIND_ZLIB])
AC_REQUIRE([KDE_CHECK_EXTRA_LIBS])
AC_MSG_CHECKING([for libpng])
AC_CACHE_VAL(ac_cv_lib_png,
[
kde_save_LIBS="$LIBS"
LIBS="$LIBS $all_libraries -lpng $LIBZ -lm -lX11 $LIBSOCKET"
kde_save_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS $all_includes"
AC_LANG_C
AC_TRY_LINK(dnl
    [
    #include<png.h>
    ],
    [
    png_structp png_ptr = png_create_read_struct(  /* image ptr */
		PNG_LIBPNG_VER_STRING, 0, 0, 0 );
    return( png_ptr != 0 ); 
    ],
    eval "ac_cv_lib_png='-lpng $LIBZ -lm'",
    eval "ac_cv_lib_png=no"
)
LIBS="$kde_save_LIBS"
CFLAGS="$kde_save_CFLAGS"
])dnl
if eval "test ! \"`echo $ac_cv_lib_png`\" = no"; then
  AC_DEFINE_UNQUOTED(HAVE_LIBPNG)
  LIBPNG="$ac_cv_lib_png"
  AC_SUBST(LIBPNG)
  AC_MSG_RESULT($ac_cv_lib_png)
else
  AC_MSG_RESULT(no)
  LIBPNG=""
  AC_SUBST(LIBPNG)
fi
])

AC_DEFUN(AC_CHECK_BOOL,
[
	AC_MSG_CHECKING([for bool])
        AC_CACHE_VAL(ac_cv_have_bool,
        [
		AC_LANG_CPLUSPLUS
          	AC_TRY_COMPILE([],
                 [bool aBool = true;],
                 [ac_cv_have_bool="yes"],
                 [ac_cv_have_bool="no"])
        ]) dnl end AC_CHECK_VAL
        AC_MSG_RESULT($ac_cv_have_bool)
        if test "$ac_cv_have_bool" = "yes"; then
        	AC_DEFINE(HAVE_BOOL) 
        fi 
])

AC_DEFUN(AC_CHECK_GNU_EXTENSIONS,
[
AC_MSG_CHECKING(if you need GNU extensions)
AC_CACHE_VAL(ac_cv_gnu_extensions,
[
cat > conftest.c << EOF
#include <features.h>

#ifdef __GNU_LIBRARY__
yes
#endif
EOF

if (eval "$ac_cpp conftest.c") 2>&5 |
  egrep "yes" >/dev/null 2>&1; then
  rm -rf conftest*
  ac_cv_gnu_extensions=yes
else
  ac_cv_gnu_extensions=no
fi
])

AC_MSG_RESULT($ac_cv_gnu_extensions)
if test "$ac_cv_gnu_extensions" = "yes"; then
  AC_DEFINE_UNQUOTED(_GNU_SOURCE)
fi
])

AC_DEFUN(AC_CHECK_COMPILERS,
[
  dnl this is somehow a fat lie, but prevents other macros from double checking
  AC_PROVIDE([AC_PROG_CC])
  AC_PROVIDE([AC_PROG_CPP])
  AC_ARG_ENABLE(debug,[  --enable-debug          creates debugging code [default=no]],
  [ 
   if test $enableval = "no"; dnl 
     then ac_use_debug_code="no"
     else ac_use_debug_code="yes"
   fi
  ], [ac_use_debug_code="no"])

  AC_ARG_ENABLE(strict,[  --enable-strict         compiles with strict compiler options (may not work!)],
   [ 
    if test $enableval = "no"; then 
         ac_use_strict_options="no"
       else 
         ac_use_strict_options="yes"
    fi
   ], [ac_use_strict_options="no"])

dnl this was AC_PROG_CC. I had to include it manualy, since I had to patch it
  AC_MSG_CHECKING(for a C-Compiler)
  dnl if there is one, print out. if not, don't matter
  AC_MSG_RESULT($CC) 
 
  if test -z "$CC"; then AC_CHECK_PROG(CC, gcc, gcc) fi
  if test -z "$CC"; then AC_CHECK_PROG(CC, cc, cc, , , /usr/ucb/cc) fi
  if test -z "$CC"; then AC_CHECK_PROG(CC, xlc, xlc) fi
  test -z "$CC" && AC_MSG_ERROR([no acceptable cc found in \$PATH])

  AC_PROG_CC_WORKS
  AC_PROG_CC_GNU

  if test $ac_cv_prog_gcc = yes; then
    GCC=yes
  else
    GCC=
  fi

  if test -z "$CFLAGS"; then
    if test "$ac_use_debug_code" = "yes"; then
      AC_PROG_CC_G
      if test $ac_cv_prog_cc_g = yes; then
        CFLAGS="-g"
      fi
    else
      if test "$GCC" = "yes"; then
        CFLAGS="-O2"
      else
        CFLAGS=""
      fi
    fi

    if test "$GCC" = "yes"; then
     CFLAGS="$CFLAGS -Wall"

     if test "$ac_use_strict_options" = "yes"; then
	CFLAGS="$CFLAGS -W -ansi -pedantic"     
     fi
    fi

  fi

  case "$host" in 
  *-*-sysv4.2uw*) CFLAGS="$CFLAGS -D_UNIXWARE";;
  esac

  if test -z "$LDFLAGS" && test "$ac_use_debug_code" = "no" && test "$GCC" = "yes"; then
     LDFLAGS="-s"
  fi


dnl this is AC_PROG_CPP. I had to include it here, since autoconf checks
dnl dependecies between AC_PROG_CPP and AC_PROG_CC (or is it automake?)

  AC_MSG_CHECKING(how to run the C preprocessor)
  # On Suns, sometimes $CPP names a directory.
  if test -n "$CPP" && test -d "$CPP"; then
    CPP=
  fi
  if test -z "$CPP"; then
  AC_CACHE_VAL(ac_cv_prog_CPP,
  [  # This must be in double quotes, not single quotes, because CPP may get
    # substituted into the Makefile and "${CC-cc}" will confuse make.
    CPP="${CC-cc} -E"
    # On the NeXT, cc -E runs the code through the compiler's parser,
    # not just through cpp.
    dnl Use a header file that comes with gcc, so configuring glibc    
    dnl with a fresh cross-compiler works.
    AC_TRY_CPP([#include <assert.h>
    Syntax Error], ,
    CPP="${CC-cc} -E -traditional-cpp"
    AC_TRY_CPP([#include <assert.h>
    Syntax Error], , CPP=/lib/cpp))
    ac_cv_prog_CPP="$CPP"])dnl
    CPP="$ac_cv_prog_CPP"
  else
    ac_cv_prog_CPP="$CPP"
  fi
  AC_MSG_RESULT($CPP)
  AC_SUBST(CPP)dnl


  AC_MSG_CHECKING(for a C++-Compiler)
  dnl if there is one, print out. if not, don't matter
  AC_MSG_RESULT($CXX) 
 
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, g++, g++) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, CC, CC) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, xlC, xlC) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, DCC, DCC) fi
  test -z "$CXX" && AC_MSG_ERROR([no acceptable C++-compiler found in \$PATH])

  AC_PROG_CXX_WORKS
  AC_PROG_CXX_GNU

  if test $ac_cv_prog_gxx = yes; then
    GXX=yes
  else
    AC_MSG_CHECKING(whether we are using SPARC CC)
    GXX=
    cat > conftest.C << EOF
#ifdef __SUNPRO_CC
   yes;
#endif
EOF

    ac_try="$CXX -E conftest.C"
    if { (eval echo configure:__online__: \"$ac_try\") 1>&5; (eval $ac_try) 2>&5; } | egrep yes >/dev/null 2>&1; then
      ac_cv_prog_CC=yes
    else
      ac_cv_prog_CC=no
    fi
    AC_MSG_RESULT($ac_cv_prog_CC)
    if test "$ac_cv_prog_CC" = "yes"; then
      AC_MSG_ERROR([Sparc CC doesn't work on KDE sources at least til version
4.2. This compiler has several problems accepting legal C++ code 
including the builtin C++ type bool. Since KDE is a freeware project,
we decided, that we don't want to support that broken compilers. 

If you really want to see support for Sparc CC within KDE, make reasonable
patches and join the KDE project. More information about KDE can be found
on www.kde.org])
    fi
  fi

  if test -z "$CXXFLAGS"; then 
    if test "$ac_use_debug_code" = "yes"; then
      AC_PROG_CXX_G
      if test $ac_cv_prog_cxx_g = yes; then
        CXXFLAGS="-g"
      fi
      if test "$ac_cv_prog_CC" = "yes"; then
        CXXFLAGS="$CXXFLAGS -pto"
      fi
    else
      if test "$GXX" = "yes"; then
         CXXFLAGS="-O2"
      else
         if test "$ac_cv_prog_CC" = "yes"; then
            CXXFLAGS="-pto -O2"
         else
            CXXFLAGS=""
         fi
      fi
    fi

    if test "$GXX" = "yes"; then
       CXXFLAGS="$CXXFLAGS -Wall"
 
       if test "$ac_use_strict_options" = "yes"; then
	CXXFLAGS="$CXXFLAGS -W -ansi -Wtraditional  -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Woverloaded-virtual -Wbad-function-cast  -Wsynth"
       fi

       if test "$kde_very_strict" = "yes"; then
         CXXFLAGS="$CXXFLAGS -Wold-style-cast -Wshadow -Wredundant-decls -Wconversion"
       fi
    fi
  fi  

    case "$host" in
      *-*-sysv4.2uw*) CXXFLAGS="$CXXFLAGS -D_UNIXWARE";;
    esac    
  
    AC_PROVIDE(AC_PROG_CXXCPP)

    AC_MSG_CHECKING(how to run the C++ preprocessor)
    if test -z "$CXXCPP"; then
      AC_CACHE_VAL(ac_cv_prog_CXXCPP,
      [
         AC_LANG_SAVE[]dnl
         AC_LANG_CPLUSPLUS[]dnl
         CXXCPP="${CXX-g++} -E"
         AC_TRY_CPP([#include <stdlib.h>], , CXXCPP=/lib/cpp)
         ac_cv_prog_CXXCPP="$CXXCPP"
         AC_LANG_RESTORE[]dnl
     ])dnl
     CXXCPP="$ac_cv_prog_CXXCPP"
     fi
    AC_MSG_RESULT($CXXCPP)
    AC_SUBST(CXXCPP)dnl
    
])

dnl just a wrapper to clean up configure.in
AC_DEFUN(KDE_PROG_LIBTOOL,
[
AC_REQUIRE([AM_ENABLE_SHARED])
AC_REQUIRE([AM_ENABLE_STATIC])
dnl libtool is only for C, so I must force him
dnl to find the correct flags for C++
kde_save_cc=$CC
kde_save_cflags="$CFLAGS"
CC=$CXX
CFLAGS="$CXXFLAGS"
AM_SET_LIBTOOL_VARIABLE([--silent])
AM_PROG_LIBTOOL dnl for libraries
CC=$kde_save_cc
CFLAGS="$kde_save_cflags"
])

AC_DEFUN(KDE_DO_IT_ALL,
[
AC_CANONICAL_SYSTEM 
AC_ARG_PROGRAM 
AM_INIT_AUTOMAKE($1, $2)
AM_DISABLE_LIBRARIES
AC_PREFIX_DEFAULT(${KDEDIR:-/usr/local/kde})
AC_CHECK_COMPILERS
KDE_PROG_LIBTOOL
AM_KDE_WITH_NLS
AC_PATH_KDE
])

AC_DEFUN(AC_CHECK_RPATH,
[
AC_MSG_CHECKING(for rpath)
AC_ARG_ENABLE(rpath,
      [  --disable-rpath         do not use the rpath feature of ld],
      USE_RPATH=$enableval, USE_RPATH=yes)

if test -z "$KDE_RPATH" && test "$USE_RPATH" = "yes"; then

  KDE_RPATH="-rpath \$(kde_libraries)"

  if test -n "$qt_libraries"; then
    KDE_RPATH="$KDE_RPATH -rpath \$(qt_libraries)"
  fi
  dnl $x_libraries is set to /usr/lib in case
  if test -n "$X_LDFLAGS"; then 
    KDE_RPATH="$KDE_RPATH -rpath \$(x_libraries)"
  fi
  if test -n "$KDE_EXTRA_RPATH"; then
    KDE_RPATH="$KDE_RPATH \$(KDE_EXTRA_RPATH)"
  fi
fi 
AC_SUBST(KDE_EXTRA_RPATH)
AC_SUBST(KDE_RPATH)
AC_MSG_RESULT($USE_RPATH)
])

dnl Check for the type of the third argument of getsockname
AC_DEFUN(AC_CHECK_KSIZE_T,
[AC_MSG_CHECKING(for the third argument of getsockname)  
AC_LANG_CPLUSPLUS
AC_CACHE_VAL(ac_cv_ksize_t,
[AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>
],[
socklen_t a=0; 
getsockname(0,(struct sockaddr*)0, &a);
],
ac_cv_ksize_t=socklen_t,
ac_cv_ksize_t=)
if test -z "$ac_cv_ksize_t"; then
ac_safe_cxxflags="$CXXFLAGS"
if test "$GCC" = "yes"; then
  CXXFLAGS="-Werror $CXXFLAGS"
fi
AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>
],[
int a=0; 
getsockname(0,(struct sockaddr*)0, &a);
],
ac_cv_ksize_t=int,
ac_cv_ksize_t=size_t)
CXXFLAGS="$ac_safe_cxxflags"
fi
])

if test -z "$ac_cv_ksize_t"; then
  ac_cv_ksize_t=int
fi

AC_MSG_RESULT($ac_cv_ksize_t)
AC_DEFINE_UNQUOTED(ksize_t, $ac_cv_ksize_t)

])

dnl This is a merge of some macros out of the gettext aclocal.m4
dnl since we don't need anything, I took the things we need
dnl the copyright for them is:
dnl >
dnl Copyright (C) 1994, 1995, 1996, 1997, 1998 Free Software Foundation, Inc.
dnl This Makefile.in is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY, to the extent permitted by law; without
dnl even the implied warranty of MERCHANTABILITY or FITNESS FOR A
dnl PARTICULAR PURPOSE.
dnl >
dnl for this file it is relicensed under LGPL

AC_DEFUN(AM_KDE_WITH_NLS,
  [AC_MSG_CHECKING([whether NLS is requested])
    AC_LANG_CPLUSPLUS
    dnl Default is enabled NLS
    AC_ARG_ENABLE(nls,
      [  --disable-nls           do not use Native Language Support],
      USE_NLS=$enableval, USE_NLS=yes)
    AC_MSG_RESULT($USE_NLS)
    AC_SUBST(USE_NLS)

    dnl If we use NLS figure out what method
    if test "$USE_NLS" = "yes"; then
      AC_DEFINE(ENABLE_NLS)

      AM_PATH_PROG_WITH_TEST_KDE(MSGFMT, msgfmt, 
         [test -n "`$ac_dir/$ac_word --version 2>&1 | grep 'GNU gettext'`"], msgfmt)
      AC_PATH_PROG(GMSGFMT, gmsgfmt, $MSGFMT)

      if test -z "`$GMSGFMT --version 2>&1 | grep 'GNU gettext'`"; then
        AC_MSG_RESULT([found msgfmt program is not GNU msgfmt; ignore it])
        GMSGFMT=":"
      fi
      MSGFMT=$GMSGFMT
      AC_SUBST(GMSGFMT)
      AC_SUBST(MSGFMT)

      AM_PATH_PROG_WITH_TEST_KDE(XGETTEXT, xgettext,
	[test -z "`$ac_dir/$ac_word -h 2>&1 | grep '(HELP)'`"], :)

      dnl Test whether we really found GNU xgettext.
      if test "$XGETTEXT" != ":"; then
	dnl If it is no GNU xgettext we define it as : so that the
	dnl Makefiles still can work.
	if $XGETTEXT --omit-header /dev/null 2> /dev/null; then
	  : ;
	else
	  AC_MSG_RESULT(
	    [found xgettext programs is not GNU xgettext; ignore it])
	  XGETTEXT=":"
	fi
      fi
     AC_SUBST(XGETTEXT)
    fi

  ])

# Search path for a program which passes the given test.
# Ulrich Drepper <drepper@cygnus.com>, 1996.

# serial 1
# Stephan Kulow: I appended a _KDE against name conflicts

dnl AM_PATH_PROG_WITH_TEST_KDE(VARIABLE, PROG-TO-CHECK-FOR,
dnl   TEST-PERFORMED-ON-FOUND_PROGRAM [, VALUE-IF-NOT-FOUND [, PATH]])
AC_DEFUN(AM_PATH_PROG_WITH_TEST_KDE,
[# Extract the first word of "$2", so it can be a program name with args.
set dummy $2; ac_word=[$]2
AC_MSG_CHECKING([for $ac_word])
AC_CACHE_VAL(ac_cv_path_$1,
[case "[$]$1" in
  /*)
  ac_cv_path_$1="[$]$1" # Let the user override the test with a path.
  ;;
  *)
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in ifelse([$5], , $PATH, [$5]); do
    test -z "$ac_dir" && ac_dir=.
    if test -f $ac_dir/$ac_word; then
      if [$3]; then
	ac_cv_path_$1="$ac_dir/$ac_word"
	break
      fi
    fi
  done
  IFS="$ac_save_ifs"
dnl If no 4th arg is given, leave the cache variable unset,
dnl so AC_PATH_PROGS will keep looking.
ifelse([$4], , , [  test -z "[$]ac_cv_path_$1" && ac_cv_path_$1="$4"
])dnl
  ;;
esac])dnl
$1="$ac_cv_path_$1"
if test -n "[$]$1"; then
  AC_MSG_RESULT([$]$1)
else
  AC_MSG_RESULT(no)
fi
AC_SUBST($1)dnl
])


# Check whether LC_MESSAGES is available in <locale.h>.
# Ulrich Drepper <drepper@cygnus.com>, 1995.
 
# serial 1
 
AC_DEFUN(AM_LC_MESSAGES,
  [if test $ac_cv_header_locale_h = yes; then
    AC_CACHE_CHECK([for LC_MESSAGES], am_cv_val_LC_MESSAGES,
      [AC_TRY_LINK([#include <locale.h>], [return LC_MESSAGES],
       am_cv_val_LC_MESSAGES=yes, am_cv_val_LC_MESSAGES=no)])
    if test $am_cv_val_LC_MESSAGES = yes; then
      AC_DEFINE(HAVE_LC_MESSAGES)
    fi
  fi])
 
dnl From Jim Meyering.
dnl FIXME: migrate into libit.

AC_DEFUN(AM_FUNC_OBSTACK,
[AC_CACHE_CHECK([for obstacks], am_cv_func_obstack,
 [AC_TRY_LINK([#include "obstack.h"],
	      [struct obstack *mem;obstack_free(mem,(char *) 0)],
	      am_cv_func_obstack=yes,
	      am_cv_func_obstack=no)])
 if test $am_cv_func_obstack = yes; then
   AC_DEFINE(HAVE_OBSTACK)
 else
   LIBOBJS="$LIBOBJS obstack.o"
 fi
])

dnl From Jim Meyering.  Use this if you use the GNU error.[ch].
dnl FIXME: Migrate into libit

AC_DEFUN(AM_FUNC_ERROR_AT_LINE,
[AC_CACHE_CHECK([for error_at_line], am_cv_lib_error_at_line,
 [AC_TRY_LINK([],[error_at_line(0, 0, "", 0, "");],
              am_cv_lib_error_at_line=yes,
	      am_cv_lib_error_at_line=no)])
 if test $am_cv_lib_error_at_line = no; then
   LIBOBJS="$LIBOBJS error.o"
 fi
 AC_SUBST(LIBOBJS)dnl
])

# Macro to add for using GNU gettext.
# Ulrich Drepper <drepper@cygnus.com>, 1995.

# serial 1
# Stephan Kulow: I put a KDE in it to avoid name conflicts

AC_DEFUN(AM_KDE_GNU_GETTEXT,
  [AC_REQUIRE([AC_PROG_MAKE_SET])dnl
   AC_REQUIRE([AC_PROG_RANLIB])dnl
   AC_REQUIRE([AC_HEADER_STDC])dnl
   AC_REQUIRE([AC_C_INLINE])dnl
   AC_REQUIRE([AC_TYPE_OFF_T])dnl
   AC_REQUIRE([AC_TYPE_SIZE_T])dnl
   AC_REQUIRE([AC_FUNC_ALLOCA])dnl
   AC_REQUIRE([AC_FUNC_MMAP])dnl
   AC_REQUIRE([AM_KDE_WITH_NLS])dnl
   AC_CHECK_HEADERS([argz.h limits.h locale.h nl_types.h malloc.h string.h \
unistd.h values.h alloca.h])
   AC_CHECK_FUNCS([getcwd munmap putenv setenv setlocale strchr strcasecmp \
__argz_count __argz_stringify __argz_next stpcpy])

   AM_LC_MESSAGES

   if test "x$CATOBJEXT" != "x"; then
     if test "x$ALL_LINGUAS" = "x"; then
       LINGUAS=
     else
       AC_MSG_CHECKING(for catalogs to be installed)
       NEW_LINGUAS=
       for lang in ${LINGUAS=$ALL_LINGUAS}; do
         case "$ALL_LINGUAS" in
          *$lang*) NEW_LINGUAS="$NEW_LINGUAS $lang" ;;
         esac
       done
       LINGUAS=$NEW_LINGUAS
       AC_MSG_RESULT($LINGUAS)
     fi

     dnl Construct list of names of catalog files to be constructed.
     if test -n "$LINGUAS"; then
       for lang in $LINGUAS; do CATALOGS="$CATALOGS $lang$CATOBJEXT"; done
     fi
   fi

  ])

AC_DEFUN(AC_HAVE_XPM,
 [AC_REQUIRE_CPP()dnl
  AC_REQUIRE([KDE_CHECK_EXTRA_LIBS])

 test -z "$XPM_LDFLAGS" && XPM_LDFLAGS=
 test -z "$XPM_INCLUDE" && XPM_INCLUDE=

 AC_ARG_WITH(xpm, [  --without-xpm           disable color pixmap XPM tests],
	xpm_test=$withval, xpm_test="yes")
 if test "x$xpm_test" = xno; then
   ac_cv_have_xpm=no
 else
   AC_MSG_CHECKING(for XPM)
   AC_CACHE_VAL(ac_cv_have_xpm,
   [
    AC_LANG_C
    ac_save_ldflags="$LDFLAGS"
    ac_save_cflags="$CFLAGS"
    LDFLAGS="$LDFLAGS $XPM_LDFLAGS $all_libraries -lXpm -lX11 -lXext $LIBSOCKET"
    CFLAGS="$CFLAGS $X_INCLUDES"
    test ! -z "$XPM_INCLUDE" && CFLAGS="-I$XPM_INCLUDE $CFLAGS"
    AC_TRY_LINK([#include <X11/xpm.h>],[],
	ac_cv_have_xpm="yes",ac_cv_have_xpm="no")
    LDFLAGS="$ac_save_ldflags"
    CFLAGS="$ac_save_cflags"
   ])dnl
 
  if test "$ac_cv_have_xpm" = no; then
    AC_MSG_RESULT(no)
    XPM_LDFLAGS=""
    XPMINC=""
    $2
  else
    AC_DEFINE(HAVE_XPM)
    if test "$XPM_LDFLAGS" = ""; then
       XPMLIB='-lXpm $(LIB_X11)'
    else
       XPMLIB="-L$XPM_LDFLAGS -lXpm "'$(LIB_X11)'
    fi
    if test "$XPM_INCLUDE" = ""; then
       XPMINC=""
    else
       XPMINC="-I$XPM_INCLUDE"
    fi
    AC_MSG_RESULT(yes)
    $1
  fi
 fi
 AC_SUBST(XPMINC)
 AC_SUBST(XPMLIB)
]) 

AC_DEFUN(AC_HAVE_GL,
 [AC_REQUIRE_CPP()dnl
  AC_REQUIRE([KDE_CHECK_EXTRA_LIBS])

 test -z "$GL_LDFLAGS" && GL_LDFLAGS=
 test -z "$GL_INCLUDE" && GL_INCLUDE=

 AC_ARG_WITH(gl, [  --without-gl            disable 3D GL modes],
	gl_test=$withval, gl_test="yes")
 if test "x$gl_test" = xno; then
   ac_cv_have_gl=no
 else
   AC_MSG_CHECKING(for GL)
   AC_CACHE_VAL(ac_cv_have_gl,
   [
    AC_LANG_C
    ac_save_ldflags="$LDFLAGS"
    ac_save_cflags="$CFLAGS"
    LDFLAGS="$LDFLAGS $GL_LDFLAGS $all_libraries -lMesaGL -lMesaGLU -lX11 -lXext -lm $LIBSOCKET"
    CFLAGS="$CFLAGS $X_INCLUDES"
    test ! -z "$GL_INCLUDE" && CFLAGS="-I$GL_INCLUDE $CFLAGS"
    AC_TRY_LINK([],[],
	ac_cv_have_gl="yes",ac_cv_have_gl="no")
    LDFLAGS="$ac_save_ldflags"
    CFLAGS="$ac_save_cflags"
   ])dnl
 
  if test "$ac_cv_have_gl" = no; then
    AC_MSG_RESULT(no)
    GL_LDFLAGS=""
    GLINC=""
    $2
  else
    AC_DEFINE(HAVE_GL)
    if test "$GL_LDFLAGS" = ""; then
       GLLIB='-lMesaGL -lMesaGLU $(LIB_X11)'
    else
       GLLIB="$GL_LDFLAGS -lMesaGL -lMesaGLU "'$(LIB_X11)'
    fi
    if test "$GL_INCLUDE" = ""; then
       GLINC=""
    else
       GLINC="-I$GL_INCLUDE"
    fi
    AC_MSG_RESULT(yes)
    $1
  fi
 fi
 AC_SUBST(GLINC)
 AC_SUBST(GLLIB)
]) 

 dnl PAM pam
 
 dnl Should test for PAM (Pluggable Authentication Modules)
 AC_DEFUN(AC_PATH_PAM_DIRECT,
 [
 test -z "$pam_direct_test_library" && pam_direct_test_library=pam
 test -z "$pam_direct_test_include" && pam_direct_test_include=security/pam_appl.h
 
   for ac_dir in               \
                               \
     /usr/local/include        \
     /usr/include              \
     /usr/unsupported/include  \
     /opt/include              \
     /usr/pam/include          \
     /usr/local/pam/include    \
     /usr/lib/pam/include      \
 			      \
     $extra_include            \
     ; \
   do
     if test -r "$ac_dir/$pam_direct_test_include"; then
       no_pam= ac_pam_includes=$ac_dir
       break
     fi
   done
 
 # First see if replacing the include by lib works.
 for ac_dir in `echo "$ac_pam_includes" | sed s/include/lib/` \
                           \
     /lib                  \
     /usr/lib              \
     /usr/local/lib        \
     /usr/unsupported/lib  \
     /lib/security         \
     /usr/security/lib     \
     $extra_lib            \
     ; \
 do
   for ac_extension in a so sl; do
     if test -r $ac_dir/lib${pam_direct_test_library}.$ac_extension; then
       no_pam= ac_pam_libraries=$ac_dir
       break 2
     fi
   done
 done
])

AC_DEFUN(AC_PATH_PAM,
 [
  AC_REQUIRE([KDE_CHECK_LIBDL])
  AC_REQUIRE_CPP()dnl

  AC_CHECK_LIB(pam_misc, main, [PAM_MISC_LIB="-lpam_misc"], [], [-lpam $LIBDL])

 AC_MSG_CHECKING(for PAM)
 AC_ARG_WITH(pam, 
[  --with-pam[=ARG]        enable support for PAM: ARG=[yes|no|service name]],
  [
    if test "x$withval" = "xyes"; then
      no_pam=
      default_pam=yes
    elif test "x$withval" = "xno"; then
      no_pam=yes
    else
      no_pam=
      pam_service="$withval"
        if test -z "$pam_service"; then
        default_pam=yes
        else
        default_pam=
        fi 
      fi
  ], no_pam=yes
 )

 if test ! "$no_pam" = yes; then

 AC_CACHE_VAL(ac_cv_path_pam,
 [
 ac_pam_includes=NONE
 ac_pam_libraries=NONE
 if test -z "$pam_libraries"; then
   pam_libraries=NONE
 fi
 if test -z "$pam_includes"; then
   pam_includes=NONE
 fi

 AC_PATH_PAM_DIRECT
 
 test "x$pam_includes" = xNONE && pam_includes=$ac_pam_includes
 test "x$pam_libraries" = xNONE && pam_libraries=$ac_pam_libraries
 
 if test ! "x$pam_includes" = xNONE && test ! "x$pam_libraries" = xNONE; then
   ac_pam_libs="-lpam $PAM_MISC_LIB $LIBDL"
   ac_cv_path_pam="no_pam= ac_pam_includes=$ac_pam_includes ac_pam_libraries=$ac_pam_libraries ac_pam_libs=\"$ac_pam_libs\""
 else
   ac_cv_path_pam="no_pam=yes"
 fi
 ])

 eval "$ac_cv_path_pam"
 
 fi

 if test "$no_pam" = yes; then
   AC_MSG_RESULT(no)
 else
   AC_DEFINE(HAVE_PAM)
   PAMLIBS="$ac_pam_libs"
   test "x$pam_includes" = xNONE && pam_includes=$ac_pam_includes
   test "x$pam_libraries" = xNONE && pam_libraries=$ac_pam_libraries
   AC_MSG_RESULT([libraries $pam_libraries, headers $pam_includes])
 if test "$default_pam" = yes; then
   AC_MSG_RESULT(["default pam service name will be used"])
 else
   AC_DEFINE_UNQUOTED(KDE_PAM_SERVICE,"$pam_service")
   AC_MSG_RESULT(["pam service name will be: " $pam_service])
 fi
dnl test whether struct pam_message is const (Linux) or not (Sun)
   pam_appl_h="$ac_pam_includes/security/pam_appl.h"
   AC_MSG_CHECKING(for const pam_message)
   AC_EGREP_HEADER([struct pam_message],
      $pam_appl_h,
      [ AC_EGREP_HEADER([const struct pam_message],
                        $pam_appl_h,
                        [AC_MSG_RESULT(["const: Linux-type PAM"]) ],
                        [AC_MSG_RESULT(["nonconst: Sun-type PAM"])
                        AC_DEFINE(PAM_MESSAGE_NONCONST)] 
                        )],
       [AC_MSG_RESULT(["not found - assume const, Linux-type PAM"])]
       )
 fi
 
 if test "x$pam_libraries" != x && test "x$pam_libraries" != xNONE ; then
     PAMLIBPATHS="-L$pam_libraries"
 fi
 if test "x$pam_includes" != x && test "x$pam_includes" != xNONE ; then
     PAMINC="-I$pam_includes"
 fi
 
 AC_SUBST(PAMINC)
 AC_SUBST(PAMLIBS)
 AC_SUBST(PAMLIBPATHS)

]) 

AC_DEFUN(KDE_CHECK_LIBDL,
[
AC_CHECK_LIB(dl, dlopen, [
LIBDL="-ldl"
ac_cv_have_dlfcn=yes
])

AC_CHECK_LIB(dld, shl_unload, [
LIBDL="-ldld"
ac_cv_have_shload=yes
])

AC_SUBST(LIBDL)
])

AC_DEFUN(KDE_CHECK_DLOPEN,
[
KDE_CHECK_LIBDL
AC_CHECK_HEADERS(dlfcn.h dl.h)
if test "$ac_cv_header_dlfcn_h" = "no"; then
  ac_cv_have_dlfcn=no
fi

if test "$ac_cv_header_dl_h" = "no"; then
  ac_cv_have_shload=no
fi

enable_dlopen=no
AC_ARG_ENABLE(dlopen,
[  --disable-dlopen        link staticly [default=no]] ,
[if test "$enableval" = yes; then
  enable_dlopen=yes
fi],
enable_dlopen=yes)

# override the user's opinion, if we know it better ;)
if test "$ac_cv_have_dlfcn" = "no" && test "$ac_cv_have_shload" = "no"; then
  enable_dlopen=no
fi

if test "$ac_cv_have_dlfcn" = "yes"; then
  AC_DEFINE_UNQUOTED(HAVE_DLFCN)
fi

if test "$ac_cv_have_shload" = "yes"; then
  AC_DEFINE_UNQUOTED(HAVE_SHLOAD)
fi

if test "$enable_dlopen" = no ; then
  test -n "$1" && eval $1
else
  test -n "$2" && eval $2
fi

])

AC_DEFUN(KDE_CHECK_DYNAMIC_LOADING,
[
KDE_CHECK_DLOPEN(libtool_enable_shared=no, libtool_enable_static=no)
KDE_PROG_LIBTOOL
AC_MSG_CHECKING([dynamic loading])
eval "`egrep '^build_libtool_libs=' libtool`"
if test "$build_libtool_libs" = "yes" && test "$enable_dlopen" = "yes"; then
  dynamic_loading=yes
  AC_DEFINE_UNQUOTED(HAVE_DYNAMIC_LOADING)
else
  dynamic_loading=no
fi
AC_MSG_RESULT($dynamic_loading)
if test "$dynamic_loading" = "yes"; then
  $1
else
  $2
fi
])

AC_DEFUN(KDE_ADD_INCLUDES,
[
if test -z "$1"; then 
  test_include="Pix.h"
else
  test_include="$1"
fi

AC_MSG_CHECKING([for libg++ ($test_include)])

AC_CACHE_VAL(kde_cv_libgpp_includes,
[
kde_cv_libgpp_includes=no

   for ac_dir in               \
                               \
     /usr/include/g++          \
     /usr/include              \
     /usr/unsupported/include  \
     /opt/include              \
     $extra_include            \
     ; \
   do
     if test -r "$ac_dir/$test_include"; then
       kde_cv_libgpp_includes=$ac_dir
       break
     fi
   done
])

AC_MSG_RESULT($kde_cv_libgpp_includes)
if test "$kde_cv_libgpp_includes" != "no"; then
  all_includes="-I$kde_cv_libgpp_includes $all_includes"
fi
])
])


AC_DEFUN(KDE_CHECK_MICO,
[
AC_REQUIRE([KDE_CHECK_LIBDL])
AC_REQUIRE([KDE_MISC_TESTS])
AC_MSG_CHECKING(for MICO)
AC_ARG_WITH(micodir,
  [  --with-micodir=micodir  where mico is installed ],
  kde_micodir=$withval,
  kde_micodir=/usr/local
)
AC_MSG_RESULT($kde_micodir)
if test ! -r  $kde_micodir/include/CORBA.h; then
  AC_MSG_ERROR([No CORBA.h found, specify another micodir])
fi

MICO_INCLUDES=-I$kde_micodir/include
AC_SUBST(MICO_INCLUDES)
MICO_LDFLAGS=-L$kde_micodir/lib
AC_SUBST(MICO_LDFLAGS)

AC_MSG_CHECKING([for MICO version])
AC_CACHE_VAL(kde_cv_mico_version,
[
AC_LANG_C
cat >conftest.$ac_ext <<EOF
#include <stdio.h>
#include <mico/version.h>
int main() { 
    
   printf("MICO_VERSION=%s\n",MICO_VERSION); 
   return (0); 
}
EOF
ac_compile='${CC-gcc} $CFLAGS $MICO_INCLUDES conftest.$ac_ext -o conftest'
if AC_TRY_EVAL(ac_compile); then
  if eval `./conftest 2>&5`; then
    kde_cv_mico_version=$MICO_VERSION
  else
    AC_MSG_ERROR([your system is not able to execute a small application to
    find MICO version! Check $kde_micodir/include/mico/version.h])
  fi 
else
  AC_MSG_ERROR([your system is not able to compile a small application to
  find MICO version! Check $kde_micodir/include/mico/version.h])
fi
])

dnl installed MICO version
mico_v_maj=`echo $kde_cv_mico_version | sed -e 's/^\(.*\)\..*\..*$/\1/'`
mico_v_mid=`echo $kde_cv_mico_version | sed -e 's/^.*\.\(.*\)\..*$/\1/'`
mico_v_min=`echo $kde_cv_mico_version | sed -e 's/^.*\..*\.\(.*\)$/\1/'`

dnl required MICO version
req_v_maj=`echo $1 | sed -e 's/^\(.*\)\..*\..*$/\1/'`
req_v_mid=`echo $1 | sed -e 's/^.*\.\(.*\)\..*$/\1/'`
req_v_min=`echo $1 | sed -e 's/^.*\..*\.\(.*\)$/\1/'` 

if test "$mico_v_maj" -lt "$req_v_maj" || \
   ( test "$mico_v_maj" -eq "$req_v_maj" && \
        test "$mico_v_mid" -lt "$req_v_mid" ) || \
   ( test "$mico_v_mid" -eq "$req_v_mid" && \
        test "$mico_v_min" -lt "$req_v_min" )

then
  AC_MSG_ERROR([found MICO version $kde_cv_mico_version but version $1 \
at least is required. You should upgrade MICO.])
else
  AC_MSG_RESULT([$kde_cv_mico_version (minimum version $1, ok)])
fi

LIBMICO="-lmico$kde_cv_mico_version $LIBCRYPT $LIBDL"
AC_SUBST(LIBMICO)
IDL=$kde_micodir/bin/idl
AC_SUBST(IDL)
])


AC_DEFUN(KDE_CHECK_MINI_STL,
[
AC_REQUIRE([KDE_CHECK_MICO])

AC_MSG_CHECKING(if we use mico's mini-STL)
AC_CACHE_VAL(kde_cv_have_mini_stl,
[
AC_LANG_CPLUSPLUS
kde_save_cxxflags="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS $MICO_INCLUDES"
AC_TRY_COMPILE(
[
#include <mico/config.h>
],
[
#ifdef HAVE_MINI_STL
#error "nothing"
#endif
],
kde_cv_have_mini_stl=no,
kde_cv_have_mini_stl=yes)
CXXFLAGS="$kde_save_cxxflags"
])


AC_MSG_RESULT($kde_cv_have_mini_stl)
if test "$kde_cv_have_mini_stl" = "yes"; then
  AC_DEFINE_UNQUOTED(HAVE_MINI_STL)
fi
])

])


AC_DEFUN(KDE_CHECK_LIBPTHREAD,
[
AC_CHECK_LIB(pthread, pthread_create, [LIBPTHREAD="-lpthread"], LIBPTHREAD= )
AC_SUBST(LIBPTHREAD)
])

AC_DEFUN(KDE_TRY_LINK_PYTHON,
[
AC_CACHE_VAL(kde_cv_try_link_python_$1,
[
kde_save_cxxflags="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS $PYTHONINC"
kde_save_libs="$LIBS"
LIBS="$LIBS $LIBPYTHON $2 $LIBDL $LIBSOCKET"
kde_save_ldflags="$LDFLAGS"
LDFLAGS="$LDFLAGS $PYTHONLIB"

AC_TRY_LINK(
[
#include <Python.h>
],[
	PySys_SetArgv(1, 0);
],
	[kde_cv_try_link_python_$1=yes],
	[kde_cv_try_link_python_$1=no]
)
CXXFLAGS="$kde_save_cxxflags"
LIBS="$kde_save_libs"
LDFLAGS="$kde_save_ldflags"
])

if test "$kde_cv_try_link_python_$1" = "yes"; then
  $3
else
  $4
fi

])

AC_DEFUN(KDE_CHECK_PYTHON,
[
AC_REQUIRE([KDE_CHECK_LIBDL])
AC_REQUIRE([KDE_CHECK_LIBPTHREAD])
if test -z "$1"; then 
  version="1.5"
else
  version="$1"
fi

AC_MSG_CHECKING([for Python$version])

AC_ARG_WITH(pythondir, 
[  --with-pythondir=pythondir   use python installed in pythondir ],
[
  ac_python_dir=$withval
], ac_python_dir=/usr/local
)

python_incdirs="$ac_python_dir/include/python$version /usr/include/python$version /usr/local/include/python$version /usr/local/include"
AC_FIND_FILE(Python.h, $python_incdirs, python_incdir)
if test ! -r $python_incdir/Python.h; then
  AC_MSG_ERROR(Python.h not found.)
fi

PYTHONINC=-I$python_incdir

python_libdirs="$ac_python_dir/lib/python$version/config /usr/lib/python$version/config /usr/local/python$version/config /usr/lib"
AC_FIND_FILE(libpython$version.a, $python_libdirs, python_libdir)
if test ! -r $python_libdir/libpython$version.a; then
  AC_MSG_ERROR(libpython$version.a not found.)
fi

PYTHONLIB=-L$python_libdir
LIBPYTHON=-lpython$version

AC_MSG_RESULT(header $python_incdir library $python_libdir)

dnl Note: this test is very weak
AC_MSG_CHECKING(if an Python application links)
KDE_TRY_LINK_PYTHON(normal, "", 
[AC_MSG_RESULT(yes)
 LIBPYTHON="$LIBPYTHON $LIBDL $LIBSOCKET"
],
 [
    AC_MSG_RESULT(no)
    AC_MSG_CHECKING(if Python depends on -lpthread)
    KDE_TRY_LINK_PYTHON(pthread, "$LIBPTHREAD",
    [  
       AC_MSG_RESULT(yes)
       LIBPYTHON="$LIBPYTHON $LIBPTHREAD $LIBDL $LIBSOCKET"
    ],
    [
       AC_MSG_RESULT(no)
       AC_MSG_CHECKING(if Python depeds on -ltcl)
       KDE_TRY_LINK_PYTHON(tcl, "-ltcl",
       [
	  AC_MSG_RESULT(yes)
	  LIBPYTHON="$LIBPYTHON -ltcl $LIBDL $LIBSOCKET"
       ],
       [
	  AC_MSG_RESULT(no)
	AC_MSG_WARN([it seems, Python depends on another library. 
    Pleae use \"make LIBPTYHON='-lpython$version -lotherlib'\" to fix this
    and contact the authors to let them know about this problem])
	])
    ])
 ]) 

AC_SUBST(PYTHONINC)
AC_SUBST(PYTHONLIB)
AC_SUBST(LIBPYTHON)

])


AC_DEFUN(KDE_CHECK_STL_SGI,
[
    AC_MSG_CHECKING([if STL implementation is SGI like])
    AC_CACHE_VAL(kde_cv_stl_type_sgi,
    [
      AC_TRY_COMPILE([
#include <string>
],[
  string astring="Hallo Welt.";
  astring.erase(0, 6); // now astring is "Welt"
  return 0;
], kde_cv_stl_type_sgi=yes,
   kde_cv_stl_type_sgi=no)
])

   AC_MSG_RESULT($kde_cv_stl_type_sgi)

   if test "$kde_cv_stl_type_sgi" = "yes"; then
	AC_DEFINE_UNQUOTED(HAVE_SGI_STL) 
   fi
])

AC_DEFUN(KDE_CHECK_STL_HP,
[
    AC_MSG_CHECKING([if STL implementation is HP like])
    AC_CACHE_VAL(kde_cv_stl_type_hp,
    [
      AC_TRY_COMPILE([
#include <string>
],[
  string astring="Hello World";
  astring.remove(0, 6); // now astring is "World"
  return 0;
], kde_cv_stl_type_hp=yes,
   kde_cv_stl_type_hp=no)
])
   AC_MSG_RESULT($kde_cv_stl_type_hp)

   if test "$kde_cv_stl_type_hp" = "yes"; then
	AC_DEFINE_UNQUOTED(HAVE_HP_STL) 
   fi
])

AC_DEFUN(KDE_CHECK_STL,
[
    KDE_CHECK_STL_SGI
    
    if test "$kde_cv_stl_type_sgi" = "no"; then
       KDE_CHECK_STL_HP

       if test "$kde_cv_stl_type_hp" = "no"; then
         AC_MSG_ERROR("no known STL type found")
       fi
    fi

])

AC_DEFUN(AC_FIND_QIMGIO,
   [AC_REQUIRE([AC_FIND_JPEG])
AC_REQUIRE([KDE_CHECK_EXTRA_LIBS])
AC_MSG_CHECKING([for qimgio])
AC_CACHE_VAL(ac_cv_lib_qimgio,
[
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
ac_save_LIBS="$LIBS"
LIBS="$all_libraries -lqimgio -lpng -lz $LIBJPEG $LIBQT"
AC_TRY_LINK(dnl
[
void qInitImageIO ();
],
            [qInitImageIO();],
            eval "ac_cv_lib_qimgio=yes",
            eval "ac_cv_lib_qimgio=no")
LIBS="$ac_save_LIBS"
AC_LANG_RESTORE
])dnl
if eval "test \"`echo $ac_cv_lib_qimgio`\" = yes"; then
  LIBQIMGIO="-lqimgio -lpng -lz $LIBJPEG"
  AC_MSG_RESULT(yes)
  AC_DEFINE_UNQUOTED(HAVE_QIMGIO)
  AC_SUBST(LIBQIMGIO)
else
  AC_MSG_RESULT(not found)
fi
])

AC_DEFUN(KDE_CHECK_ANSI,
[
AC_MSG_CHECKING([for strdup])

    AC_CACHE_VAL(kde_cv_has_strdup,
    [
AC_LANG_CPLUSPLUS
save_CXXFLAGS="$CXXFLAGS"
if test "$GCC" = "yes"; then
  CXXFLAGS="$CXXFLAGS -pedantic-errors"
fi

AC_TRY_COMPILE([
#include <string.h>
],[
  char buffer[] = "Hallo";
  strdup(buffer)
], kde_cv_has_strdup=yes,
   kde_cv_has_strdup=no)
CXXFLAGS="$save_CXXFLAGS"
])
AC_MSG_RESULT($kde_cv_has_strdup)

if test "$kde_cv_has_strdup" = "yes"; then
  AC_DEFINE_UNQUOTED(HAVE_STRDUP)
fi

])

AC_DEFUN(KDE_CHECK_INSURE,
[
  AC_ARG_ENABLE(insure, [  --enable-insure             use insure++ for debugging [default=no]],
  [
  if test $enableval = "no"; dnl
	then ac_use_insure="no"
	else ac_use_insure="yes"
   fi
  ], [ac_use_insure="no"])

  AC_MSG_CHECKING(if we will use Insure++ to debug)
  AC_MSG_RESULT($ac_use_insure)
  if test "$ac_use_insure" = "yes"; dnl
       then CC="insure"; CXX="insure"; dnl CFLAGS="$CLAGS -fno-rtti -fno-exceptions "????
   fi
])          

AC_DEFUN(AM_DISABLE_LIBRARIES,
[
    AC_PROVIDE([AM_ENABLE_STATIC])
    AC_PROVIDE([AM_ENABLE_SHARED])
    enable_static=no
    enable_shared=no
])


AC_DEFUN(AC_CHECK_UTMP_FILE,
[
    AC_MSG_CHECKING([for utmp file])
 
    AC_CACHE_VAL(kde_cv_utmp_file,
    [
    kde_cv_utmp_file=no
 
    for ac_file in    \
                      \
	/var/run/utmp \
	/var/adm/utmp \
	/etc/utmp     \
     ; \
    do
     if test -r "$ac_file"; then
       kde_cv_utmp_file=$ac_file
       break
     fi
    done
    ])
 
    AC_MSG_RESULT($kde_cv_utmp_file)
    if test "$kde_cv_utmp_file" != "no"; then
	AC_DEFINE_UNQUOTED(UTMP, "$kde_cv_utmp_file")
    fi
])


AC_DEFUN(KDE_CREATE_SUBDIRSLIST,
[

DO_NOT_COMPILE="$DO_NOT_COMPILE CVS debian bsd-port admin"

if test ! -s $srcdir/inst-apps && test -s $srcdir/subdirs; then
 cp $srcdir/subdirs $srcdir/inst-apps
fi

if test ! -s $srcdir/inst-apps; then
  TOPSUBDIRS=""
  files=`cd $srcdir && ls -1`
  dirs=`for i in $files; do if test -d $i; then echo $i; fi; done`
  for i in $dirs; do 
    echo $i >> $srcdir/subdirs
  done
  cp $srcdir/subdirs $srcdir/inst-apps
fi    

if test -s $srcdir/inst-apps; then
  ac_topsubdirs="`cat $srcdir/inst-apps`"
fi  

for i in $ac_topsubdirs; do
  AC_MSG_CHECKING([if $i should be compiled])
  if test -d $srcdir/$i; then
    install_it="yes"
    for j in $DO_NOT_COMPILE; do 
      if test $i = $j; then
        install_it="no"
      fi
    done
  else
    install_it="no"
  fi
  AC_MSG_RESULT($install_it)
  if test $install_it = "yes"; then 
    TOPSUBDIRS="$TOPSUBDIRS $i"
  fi
done

AC_SUBST(TOPSUBDIRS)
])

AC_DEFUN(KDE_CHECK_NAMESPACES,
[
AC_MSG_CHECKING(whether C++ compiler supports namespaces)
AC_LANG_CPLUSPLUS
AC_TRY_COMPILE([
],
[
namespace Foo {
  extern int i;
  namespace Bar {
    extern int i;
  }
}

int Foo::i = 0;
int Foo::Bar::i = 1;
],[
  AC_MSG_RESULT(yes)
  AC_DEFINE(HAVE_NAMESPACES)
], [
AC_MSG_RESULT(no)
])
])

AC_DEFUN(KDE_CHECK_NEWLIBS,
[
AC_MSG_CHECKING([for new KDE libraries to be present])
AC_CACHE_VAL(kde_cv_newlibs,
[
AC_LANG_CPLUSPLUS
cat > conftest.$ac_ext <<EOF
#include <stdio.h>
#include "confdefs.h"
#include <k2url.h>

int main() {
    K2URL::List l;
    return 0;
}
EOF

ac_compile='${CXX-g++} -c $CXXFLAGS $all_includes $CPPFLAGS conftest.$ac_ext'
if AC_TRY_EVAL(ac_compile); then
  kde_cv_newlibs=yes
else
  kde_cv_newlibs=no
fi

rm -rf conftest.*

])

if test "$kde_cv_newlibs" = "yes"; then
    AC_MSG_RESULT(yes)
else
  AC_MSG_ERROR([we can't find k2url.h. It may be that you have to
compile kdelibs with --enable-new-stuff!])
fi

LIB_KDEUTIL='-lkdeutil'
AC_SUBST(LIB_KDEUTIL)

LIB_KIO='-lkio $(LIB_KDEUI) $(LIB_KDEUTIL)'
AC_SUBST(LIB_KIO)
])

dnl ------------------------------------------------------------------------
dnl Check for S_ISSOCK macro. Doesn't exist on Unix SCO. faure@kde.org
dnl ------------------------------------------------------------------------
dnl
AC_DEFUN(AC_CHECK_S_ISSOCK,
[
AC_MSG_CHECKING(for S_ISSOCK)
AC_CACHE_VAL(ac_cv_have_s_issock,
[
AC_LANG_SAVE
AC_LANG_C
AC_TRY_LINK(
[
#include <sys/stat.h>
],
[
struct stat buff;
int b = S_ISSOCK( buff.st_mode );
],
ac_cv_have_s_issock=yes,
ac_cv_have_s_issock=no)
AC_LANG_RESTORE
])
AC_MSG_RESULT($ac_cv_have_s_issock)
if test "$ac_cv_have_s_issock" = "yes"; then
  AC_DEFINE_UNQUOTED(HAVE_S_ISSOCK)
fi
])

dnl ------------------------------------------------------------------------
dnl Check for MAXPATHLEN macro, defines KDEMAXPATHLEN. faure@kde.org
dnl ------------------------------------------------------------------------
dnl
AC_DEFUN(AC_CHECK_KDEMAXPATHLEN,
[
AC_MSG_CHECKING(for MAXPATHLEN)
AC_CACHE_VAL(ac_cv_maxpathlen,
[
AC_LANG_C
cat > conftest.$ac_ext <<EOF
#include <stdio.h>
#include <sys/param.h>
#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

KDE_HELLO MAXPATHLEN

EOF

ac_try="$ac_cpp conftest.$ac_ext 2>/dev/null | grep '^KDE_HELLO' >conftest.out"

if AC_TRY_EVAL(ac_try) && test -s conftest.out; then 
    ac_cv_maxpathlen=`sed 's#KDE_HELLO ##' conftest.out`
else
    ac_cv_maxpathlen=1024
fi

rm conftest.*

])
AC_MSG_RESULT($ac_cv_maxpathlen)
AC_DEFINE_UNQUOTED(KDEMAXPATHLEN,$ac_cv_maxpathlen)
])

dnl this is for kdm:

AC_DEFUN(AC_CHECK_KDM,
[
AC_CHECK_FUNCS(getsecretkey)
dnl checks for X server

AC_PATH_PROG(X_SERVER, X)
if test ! -z "$X_SERVER"; then
X_SERVER=`echo $X_SERVER | sed -e 's+/X$++'`
AC_DEFINE_UNQUOTED(XBINDIR,$X_SERVER)
XBINDIR=$X_SERVER
AC_SUBST(XBINDIR)
fi

dnl This one tries to find XDMDIR for config files
AC_ARG_WITH(xdmdir,
	[  --with-xdmdir	          If the xdm config dir can't be found automaticly],
	[ ac_xdmdir=$withval],
	[ ac_xdmdir="no"])

AC_MSG_CHECKING([for xdm configuration dir])
if test "$ac_xdmdir" = "no"; then
    rm -fr conftestdir
    if mkdir conftestdir; then
	cd conftestdir
    cat > Imakefile <<'EOF'
acfindxdm:
	@echo 'ac_xdmdir="$(XDMDIR)";'
EOF
	if (xmkmf) > /dev/null 2> /dev/null && test -f Makefile; then
	    eval `${MAKE-make} acfindxdm 2>/dev/null 2>/dev/null | grep -v make`
	fi
	cd ..
	rm -fr conftestdir
	dnl Check if Imake was right
	if test -f $ac_xdmdir/xdm-config; then
	    AC_MSG_RESULT($ac_xdmdir)
	else
	    dnl Here we must do something else
	    dnl Maybe look for xdm-config in standard places, and
	    dnl if that fails use a fresh copy in $KDEDIR/config/kdm/
	    AC_FIND_FILE(xdm-config,/etc/X11/xdm /var/X11/xdm /usr/openwin/xdm /usr/X11R6/lib/X11/xdm,ac_xdmdir)
	    if test -f $ac_xdmdir/xdm-config; then
                AC_MSG_RESULT($ac_xdmdir)
            else                                 
		if test "${prefix}" = NONE; then
			ac_xdmdir=$ac_default_prefix/config/kdm
		else
			ac_xdmdir=$prefix/config/kdm
		fi
		AC_MSG_RESULT([xdm config dir not found, installing defaults in $ac_xdmdir])
		xdmconfigsubdir=xdmconfig
		AC_SUBST(xdmconfigsubdir)
	    fi
	fi
    fi
else
    if test -f $ac_xdmdir/xdm-config; then
	AC_MSG_RESULT($ac_xdmdir)
    else

	AC_MSG_RESULT([xdm config dir not found, installing defaults in $ac_xdmdir])
	xdmconfigsubdir=xdmconfig
	AC_SUBST(xdmconfigsubdir)
    fi
fi
AC_DEFINE_UNQUOTED(XDMDIR,"$ac_xdmdir")
AC_SUBST(ac_xdmdir)

AC_PATH_PAM
if test "x$no_pam" = "xyes"; then 
	pam_support="no"
else
	pam_support="yes"
        shadow_support="no" # if pam is installed, use it. We can't savely 
	                    # test, if it works *sigh*
fi

AC_ARG_WITH(shadow,
	[  --with-shadow		  If you want shadow password support ],
	[ if test "$withval" = "yes"; then
             shadow_support="yes"
          else
             shadow_support="no"
          fi
	  if test "$pam_support" = "yes" && test "$shadow_support=yes"; then
		AC_MSG_WARN("You can not define both pam AND shadow")
	  fi
	],
	[ if test -z "$shadow_support"; then shadow_support="no"; fi ] )

if test "$pam_support" = "yes"; then
  AC_CHECK_LIB(pam, main, [PASSWDLIB="-lpam -ldl"
  AC_DEFINE_UNQUOTED(HAVE_PAM_LIB)],
  [],-ldl)
  AC_CHECK_LIB(pam_misc, main, PASSWDLIB="-lpam_misc $PASSWDLIB"
			       AC_DEFINE_UNQUOTED(HAVE_PAM_MISC))
fi

if test -z "$PASSWDLIB" && test "$shadow_support" = "yes"; then
  AC_CHECK_LIB(shadow, main,
    [ PASSWDLIB="-lshadow"
      AC_DEFINE_UNQUOTED(HAVE_SHADOW_LIB)
    ])
fi
AC_SUBST(PASSWDLIB)
AC_REQUIRE([KDE_MISC_TESTS])
AC_CHECK_LIB(util, main, [LIBUTIL="-lutil"]) dnl for FreeBSD
AC_SUBST(LIBUTIL)
AC_CHECK_LIB(s, main, [LIB_LIBS="-ls"]) dnl for AIX
AC_SUBST(LIB_LIBS)
AC_CHECK_LIB(Xdmcp, main, [LIBXDMCP="-lXdmcp"], , $X_LDFLAGS -lX11 $LIBSOCKET) dnl for Unixware
AC_SUBST(LIBXDMCP)

if test -n "$LIBXDMCP"; then
  ac_cpp_safe=$ac_cpp
  ac_cpp='$CXXCPP $CPPFLAGS $X_INCLUDES'
  AC_CHECK_HEADERS(X11/Xdmcp.h)
  ac_cpp=$ac_cpp_safe
fi

])


# serial 29 AM_PROG_LIBTOOL
AC_DEFUN(AM_PROG_LIBTOOL,
[AC_REQUIRE([AM_ENABLE_SHARED])dnl
AC_REQUIRE([AM_ENABLE_STATIC])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
AC_REQUIRE([AC_PROG_RANLIB])dnl
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AM_PROG_LD])dnl
AC_REQUIRE([AM_PROG_NM])dnl
AC_REQUIRE([AM_SYS_NM_PARSE])dnl
AC_REQUIRE([AC_PROG_LN_S])dnl
AC_REQUIRE([AM_SET_LIBTOOL_VARIABLE])dnl
dnl

# Check for any special flags to pass to ltconfig.
libtool_flags=
test "$enable_shared" = no && libtool_flags="$libtool_flags --disable-shared"
test "$enable_static" = no && libtool_flags="$libtool_flags --disable-static"
test "$silent" = yes && libtool_flags="$libtool_flags --silent"
test "$ac_cv_prog_gcc" = yes && libtool_flags="$libtool_flags --with-gcc"
test "$ac_cv_prog_gnu_ld" = yes && libtool_flags="$libtool_flags --with-gnu-ld"

# Some flags need to be propagated to the compiler or linker for good
# libtool support.
case "$host" in
*-*-irix6*)
  # Find out which ABI we are using.
  echo '[#]line __oline__ "configure"' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case "`/usr/bin/file conftest.o`" in
    *32-bit*)
      LD="${LD-ld} -32"
      ;;
    *N32*)
      LD="${LD-ld} -n32"
      ;;
    *64-bit*)
      LD="${LD-ld} -64"
      ;;
    esac
  fi
  rm -rf conftest*
  ;;

*-*-sco3.2v5*)
  # On SCO OpenServer 5, we need -belf to get full-featured binaries.
  SAVE_CFLAGS="$CFLAGS"
  CFLAGS="$CFLAGS -belf"
  AC_CACHE_CHECK([whether the C compiler needs -belf], lt_cv_cc_needs_belf,
    [AC_TRY_LINK([],[],[lt_cv_cc_needs_belf=yes],[lt_cv_cc_needs_belf=no])])
  if test x"$lt_cv_cc_needs_belf" != x"yes"; then
    # this is probably gcc 2.8.0, egcs 1.0 or newer; no need for -belf
    CFLAGS="$SAVE_CFLAGS"
  fi
  ;;

*-*-cygwin32*)
  AM_SYS_LIBTOOL_CYGWIN32
  ;;

esac

# enable the --disable-libtool-lock switch

AC_ARG_ENABLE(libtool-lock,
[  --disable-libtool-lock  force libtool not to do file locking],
need_locks=$enableval,
need_locks=yes)

if test x"$need_locks" = xno; then
  libtool_flags="$libtool_flags --disable-lock"
fi


# Actually configure libtool.  ac_aux_dir is where install-sh is found.
CC="$CC" CFLAGS="$CFLAGS" CPPFLAGS="$CPPFLAGS" \
LD="$LD" NM="$NM" RANLIB="$RANLIB" LN_S="$LN_S" \
DLLTOOL="$DLLTOOL" AS="$AS" \
${CONFIG_SHELL-/bin/sh} $ac_aux_dir/ltconfig --no-reexec \
$libtool_flags --no-verify $ac_aux_dir/ltmain.sh $host \
|| AC_MSG_ERROR([libtool configure failed])

# Redirect the config.log output again, so that the ltconfig log is not
# clobbered by the next message.
exec 5>>./config.log
])

# AM_ENABLE_SHARED - implement the --enable-shared flag
# Usage: AM_ENABLE_SHARED[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN(AM_ENABLE_SHARED,
[define([AM_ENABLE_SHARED_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(shared,
changequote(<<, >>)dnl
<<  --enable-shared[=PKGS]  build shared libraries [default=>>AM_ENABLE_SHARED_DEFAULT],
changequote([, ])dnl
[p=${PACKAGE-default}
case "$enableval" in
yes) enable_shared=yes ;;
no) enable_shared=no ;;
*)
  enable_shared=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_shared=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_shared=AM_ENABLE_SHARED_DEFAULT)dnl
])

# AM_DISABLE_SHARED - set the default shared flag to --disable-shared
AC_DEFUN(AM_DISABLE_SHARED,
[AM_ENABLE_SHARED(no)])

# AM_DISABLE_STATIC - set the default static flag to --disable-static
AC_DEFUN(AM_DISABLE_STATIC,
[AM_ENABLE_STATIC(no)])

# AM_ENABLE_STATIC - implement the --enable-static flag
# Usage: AM_ENABLE_STATIC[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN(AM_ENABLE_STATIC,
[define([AM_ENABLE_STATIC_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(static,
changequote(<<, >>)dnl
<<  --enable-static[=PKGS]  build static libraries [default=>>AM_ENABLE_STATIC_DEFAULT],
changequote([, ])dnl
[p=${PACKAGE-default}
case "$enableval" in
yes) enable_static=yes ;;
no) enable_static=no ;;
*)
  enable_static=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_static=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_static=AM_ENABLE_STATIC_DEFAULT)dnl
])


# AM_PROG_LD - find the path to the GNU or non-GNU linker
AC_DEFUN(AM_PROG_LD,
[AC_ARG_WITH(gnu-ld,
[  --with-gnu-ld           assume the C compiler uses GNU ld [default=no]],
test "$withval" = no || with_gnu_ld=yes, with_gnu_ld=no)
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
ac_prog=ld
if test "$ac_cv_prog_gcc" = yes; then
  # Check if gcc -print-prog-name=ld gives a path.
  AC_MSG_CHECKING([for ld used by GCC])
  ac_prog=`($CC -print-prog-name=ld) 2>&5`
  case "$ac_prog" in
    # Accept absolute paths.
changequote(,)dnl
    /* | [A-Za-z]:/*)
      # Canonicalize the path of ld
      re_direlt='/[^/][^/]*/\.\./'
      sub_uncdrive='s%^\([A-Za-z]\):/%//\1/%'
changequote([,])dnl
      while echo $ac_prog | grep "$re_direlt" > /dev/null 2>&1; do
        ac_prog=`echo $ac_prog| sed "s%$re_direlt%/%"`
      done
      case "$host_os" in
      cygwin*)
        # Convert to a UNC path for cygwin
        test -z "$LD" && LD=`echo X$ac_prog | $Xsed -e "$sub_uncdrive"`
	;;
      *)
        test -z "$LD" && LD="$ac_prog"
	;;
      esac
      ;;
    ##
    ## FIXME:  The code fails later on if we try to use an $LD with
    ##         '\\' path separators.
    ##
changequote(,)dnl
    [A-Za-z]:[\\]*)
      # Canonicalize the path of ld
      re_direlt='\\[^\\][^\\]*\\\.\.\(\\\)'
      sub_uncdrive='s%^\([A-Za-z]\):\\%//\1/%'
changequote([,])dnl
      sub_uncdir='s%\\%/%g'
      while echo $ac_prog | grep "$re_direlt" > /dev/null 2>&1; do
        ac_prog=`echo $ac_prog| sed "s%$re_direlt%\1%"`
      done
      case "$host_os" in
      cygwin*)
        # Convert to a UNC path for cygwin
        test -z "$LD" && LD=`echo X$ac_prog | sed -e 's%^X%%' -e "$sub_uncdrive" -e "$sub_uncdir"`
	;;
      *)
        test -z "$LD" && LD="$ac_prog"
	;;
      esac
      ;;
  "")
    # If it fails, then pretend we aren't using GCC.
    ac_prog=ld
    ;;
  *)
    # If it is relative, then search for the first ld in PATH.
    with_gnu_ld=unknown
    ;;
  esac
elif test "$with_gnu_ld" = yes; then
  AC_MSG_CHECKING([for GNU ld])
else
  AC_MSG_CHECKING([for non-GNU ld])
fi
AC_CACHE_VAL(ac_cv_path_LD,
[if test -z "$LD"; then
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in $PATH; do
    test -z "$ac_dir" && ac_dir=.
    if test -f "$ac_dir/$ac_prog"; then
      ac_cv_path_LD="$ac_dir/$ac_prog"
      # Check to see if the program is GNU ld.  I'd rather use --version,
      # but apparently some GNU ld's only accept -v.
      # Break only if it was the GNU/non-GNU ld that we prefer.
      if "$ac_cv_path_LD" -v 2>&1 < /dev/null | egrep '(GNU|with BFD)' > /dev/null; then
	test "$with_gnu_ld" != no && break
      else
        test "$with_gnu_ld" != yes && break
      fi
    fi
  done
  IFS="$ac_save_ifs"
else
  ac_cv_path_LD="$LD" # Let the user override the test with a path.
fi])
LD="$ac_cv_path_LD"
if test -n "$LD"; then
  AC_MSG_RESULT($LD)
else
  AC_MSG_RESULT(no)
fi
test -z "$LD" && AC_MSG_ERROR([no acceptable ld found in \$PATH])
AC_SUBST(LD)
AM_PROG_LD_GNU
])

AC_DEFUN(AM_PROG_LD_GNU,
[AC_CACHE_CHECK([if the linker ($LD) is GNU ld], ac_cv_prog_gnu_ld,
[# I'd rather use --version here, but apparently some GNU ld's only accept -v.
if $LD -v 2>&1 </dev/null | egrep '(GNU|with BFD)' 1>&5; then
  ac_cv_prog_gnu_ld=yes
else
  ac_cv_prog_gnu_ld=no
fi])
])

# AM_PROG_NM - find the path to a BSD-compatible name lister
AC_DEFUN(AM_PROG_NM,
[AC_MSG_CHECKING([for BSD-compatible nm])
AC_CACHE_VAL(ac_cv_path_NM,
[if test -n "$NM"; then
  # Let the user override the test.
  ac_cv_path_NM="$NM"
else
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in /usr/ucb /usr/ccs/bin $PATH /bin; do
    test -z "$ac_dir" && ac_dir=.
    if test -f $ac_dir/nm; then
      # Check to see if the nm accepts a BSD-compat flag.
      # Adding the `sed 1q' prevents false positives on HP-UX, which says:
      #   nm: unknown option "B" ignored
      if ($ac_dir/nm -B /dev/null 2>&1 | sed '1q'; exit 0) | egrep /dev/null >/dev/null; then
        ac_cv_path_NM="$ac_dir/nm -B"
      elif ($ac_dir/nm -p /dev/null 2>&1 | sed '1q'; exit 0) | egrep /dev/null >/dev/null; then
        ac_cv_path_NM="$ac_dir/nm -p"
      else
        ac_cv_path_NM="$ac_dir/nm"
      fi
      break
    fi
  done
  IFS="$ac_save_ifs"
  test -z "$ac_cv_path_NM" && ac_cv_path_NM=nm
fi])
NM="$ac_cv_path_NM"
AC_MSG_RESULT([$NM])
AC_SUBST(NM)
])

# AM_SYS_NM_PARSE - Check for command ro grab the raw symbol name followed
# by C symbol name from nm.
AC_DEFUN(AM_SYS_NM_PARSE,
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AM_PROG_NM])dnl
# Check for command to grab the raw symbol name followed by C symbol from nm.
AC_MSG_CHECKING([command to parse $NM output])
AC_CACHE_VAL(ac_cv_sys_global_symbol_pipe,
[# These are sane defaults that work on at least a few old systems.
# {They come from Ultrix.  What could be older than Ultrix?!! ;)}

changequote(,)dnl
# Character class describing NM global symbol codes.
ac_symcode='[BCDEGRSTU]'

# Regexp to match symbols that can be accessed directly from C.
ac_sympat='\([_A-Za-z][_A-Za-z0-9]*\)'

# Transform the above into a raw symbol and a C symbol.
ac_symxfrm='\1 \1'

# Define system-specific variables.
case "$host_os" in
aix*)
  ac_symcode='[BCDTU]'
  ;;
sunos* | cygwin32* | mingw32*)
  ac_sympat='_\([_A-Za-z][_A-Za-z0-9]*\)'
  ac_symxfrm='_\1 \1'
  ;;
irix*)
  # Cannot use undefined symbols on IRIX because inlined functions mess us up.
  ac_symcode='[BCDEGRST]'
  ;;
solaris*)
  ac_symcode='[BDTU]'
  ;;
esac

# If we're using GNU nm, then use its standard symbol codes.
if $NM -V 2>&1 | egrep '(GNU|with BFD)' > /dev/null; then
  ac_symcode='[ABCDGISTUW]'
fi

case "$host_os" in
cygwin32* | mingw32*)
  # We do not want undefined symbols on cygwin32.  The user must
  # arrange to define them via -l arguments.
  ac_symcode='[ABCDGISTW]'
  ;;
esac
changequote([,])dnl

# Write the raw and C identifiers.
ac_cv_sys_global_symbol_pipe="sed -n -e 's/^.* $ac_symcode $ac_sympat$/$ac_symxfrm/p'"

# Check to see that the pipe works correctly.
ac_pipe_works=no
cat > conftest.$ac_ext <<EOF
#ifdef __cplusplus
extern "C" {
#endif
char nm_test_var;
void nm_test_func(){}
#ifdef __cplusplus
}
#endif
int main(){nm_test_var='a';nm_test_func;return 0;}
EOF
if AC_TRY_EVAL(ac_compile); then
  # Now try to grab the symbols.
  ac_nlist=conftest.nm
  if AC_TRY_EVAL(NM conftest.$ac_objext \| $ac_cv_sys_global_symbol_pipe \> $ac_nlist) && test -s "$ac_nlist"; then

    # Try sorting and uniquifying the output.
    if sort "$ac_nlist" | uniq > "$ac_nlist"T; then
      mv -f "$ac_nlist"T "$ac_nlist"
      ac_wcout=`wc "$ac_nlist" 2>/dev/null`
changequote(,)dnl
      ac_count=`echo "X$ac_wcout" | sed -e 's,^X,,' -e 's/^[ 	]*\([0-9][0-9]*\).*$/\1/'`
changequote([,])dnl
      (test "$ac_count" -ge 0) 2>/dev/null || ac_count=-1
    else
      rm -f "$ac_nlist"T
      ac_count=-1
    fi

    # Make sure that we snagged all the symbols we need.
    if egrep ' nm_test_var$' "$ac_nlist" >/dev/null; then
      if egrep ' nm_test_func$' "$ac_nlist" >/dev/null; then
	cat <<EOF > conftest.c
#ifdef __cplusplus
extern "C" {
#endif

EOF
        # Now generate the symbol file.
        sed 's/^.* \(.*\)$/extern char \1;/' < "$ac_nlist" >> conftest.c

	cat <<EOF >> conftest.c
#if defined (__STDC__) && __STDC__
# define __ptr_t void *
#else
# define __ptr_t char *
#endif

/* The number of symbols in dld_preloaded_symbols, -1 if unsorted. */
int dld_preloaded_symbol_count = $ac_count;

/* The mapping between symbol names and symbols. */
struct {
  char *name;
  __ptr_t address;
}
changequote(,)dnl
dld_preloaded_symbols[] =
changequote([,])dnl
{
EOF
        sed 's/^\(.*\) \(.*\)$/  {"\1", (__ptr_t) \&\2},/' < "$ac_nlist" >> conftest.c
        cat <<\EOF >> conftest.c
  {0, (__ptr_t) 0}
};

#ifdef __cplusplus
}
#endif
EOF
        # Now try linking the two files.
        mv conftest.$ac_objext conftestm.$ac_objext
	ac_save_LIBS="$LIBS"
	ac_save_CFLAGS="$CFLAGS"
        LIBS="conftestm.$ac_objext"
	CFLAGS="$CFLAGS$no_builtin_flag"
        if AC_TRY_EVAL(ac_link) && test -s conftest; then
          ac_pipe_works=yes
        else
          echo "configure: failed program was:" >&AC_FD_CC
          cat conftest.c >&AC_FD_CC
        fi
        LIBS="$ac_save_LIBS"
	CFLAGS="$ac_save_CFLAGS"
      else
        echo "cannot find nm_test_func in $ac_nlist" >&AC_FD_CC
      fi
    else
      echo "cannot find nm_test_var in $ac_nlist" >&AC_FD_CC
    fi
  else
    echo "cannot run $ac_cv_sys_global_symbol_pipe" >&AC_FD_CC
  fi
else
  echo "$progname: failed program was:" >&AC_FD_CC
  cat conftest.c >&AC_FD_CC
fi
rm -rf conftest*

# Do not use the global_symbol_pipe unless it works.
test "$ac_pipe_works" = yes || ac_cv_sys_global_symbol_pipe=
])

ac_result=yes
if test -z "$ac_cv_sys_global_symbol_pipe"; then
   ac_result=no
fi
AC_MSG_RESULT($ac_result)
])

# AM_SYS_LIBTOOL_CYGWIN32 - find tools needed on cygwin32
AC_DEFUN(AM_SYS_LIBTOOL_CYGWIN32,
[AC_CHECK_TOOL(DLLTOOL, dlltool, false)
AC_CHECK_TOOL(AS, as, false)
])

AC_DEFUN(AM_SET_LIBTOOL_VARIABLE,
[# Always use our own libtool.
LIBTOOL='$(SHELL) $(top_builddir)/libtool $1'
AC_SUBST(LIBTOOL)dnl
])

# AM_SYS_SYMBOL_UNDERSCORE - does the compiler prefix global symbols
#                            with an underscore?
AC_DEFUN(AM_SYS_SYMBOL_UNDERSCORE,
[AC_REQUIRE([AM_PROG_NM])dnl
AC_REQUIRE([AM_SYS_NM_PARSE])dnl
AC_MSG_CHECKING([for _ prefix in compiled symbols])
AC_CACHE_VAL(ac_cv_sys_symbol_underscore,
[ac_cv_sys_symbol_underscore=no
cat > conftest.$ac_ext <<EOF
void nm_test_func(){}
int main(){nm_test_func;return 0;}
EOF
if AC_TRY_EVAL(ac_compile); then
  # Now try to grab the symbols.
  ac_nlist=conftest.nm
  if AC_TRY_EVAL(NM conftest.$ac_objext \| $ac_cv_sys_global_symbol_pipe \> $ac_nlist) && test -s "$ac_nlist"; then
    # See whether the symbols have a leading underscore.
    if egrep '^_nm_test_func' "$ac_nlist" >/dev/null; then
      ac_cv_sys_symbol_underscore=yes
    else
      if egrep '^nm_test_func ' "$ac_nlist" >/dev/null; then
        :
      else
        echo "configure: cannot find nm_test_func in $ac_nlist" >&AC_FD_CC
      fi
    fi
  else
    echo "configure: cannot run $ac_cv_sys_global_symbol_pipe" >&AC_FD_CC
  fi
else
  echo "configure: failed program was:" >&AC_FD_CC
  cat conftest.c >&AC_FD_CC
fi
rm -rf conftest*
])
AC_MSG_RESULT($ac_cv_sys_symbol_underscore)
if test x$ac_cv_sys_symbol_underscore = xyes; then
  AC_DEFINE(WITH_SYMBOL_UNDERSCORE,1,
  [define if compiled symbols have a leading underscore])
fi
])

# Do all the work for Automake.  This macro actually does too much --
# some checks are only needed if your package does certain things.
# But this isn't really a big deal.

# serial 1

dnl Usage:
dnl AM_INIT_AUTOMAKE(package,version, [no-define])

AC_DEFUN(AM_INIT_AUTOMAKE,
[AC_REQUIRE([AC_PROG_INSTALL])
PACKAGE=[$1]
AC_SUBST(PACKAGE)
VERSION=[$2]
AC_SUBST(VERSION)
dnl test to see if srcdir already configured
if test "`cd $srcdir && pwd`" != "`pwd`" && test -f $srcdir/config.status; then
  AC_MSG_ERROR([source directory already configured; run "make distclean" there first])
fi
ifelse([$3],,
AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version number of package]))
AC_REQUIRE([AM_SANITY_CHECK])
AC_REQUIRE([AC_ARG_PROGRAM])
dnl FIXME This is truly gross.
missing_dir=`cd $ac_aux_dir && pwd`
AM_MISSING_PROG(ACLOCAL, aclocal, $missing_dir)
AM_MISSING_PROG(AUTOCONF, autoconf, $missing_dir)
AM_MISSING_PROG(AUTOMAKE, automake, $missing_dir)
AM_MISSING_PROG(AUTOHEADER, autoheader, $missing_dir)
AM_MISSING_PROG(MAKEINFO, makeinfo, $missing_dir)
AC_REQUIRE([AC_PROG_MAKE_SET])])

#
# Check to make sure that the build environment is sane.
#

AC_DEFUN(AM_SANITY_CHECK,
[AC_MSG_CHECKING([whether build environment is sane])
# Just in case
sleep 1
echo timestamp > conftestfile
# Do `set' in a subshell so we don't clobber the current shell's
# arguments.  Must try -L first in case configure is actually a
# symlink; some systems play weird games with the mod time of symlinks
# (eg FreeBSD returns the mod time of the symlink's containing
# directory).
if (
   set X `ls -Lt $srcdir/configure conftestfile 2> /dev/null`
   if test "[$]*" = "X"; then
      # -L didn't work.
      set X `ls -t $srcdir/configure conftestfile`
   fi
   if test "[$]*" != "X $srcdir/configure conftestfile" \
      && test "[$]*" != "X conftestfile $srcdir/configure"; then

      # If neither matched, then we have a broken ls.  This can happen
      # if, for instance, CONFIG_SHELL is bash and it inherits a
      # broken ls alias from the environment.  This has actually
      # happened.  Such a system could not be considered "sane".
      AC_MSG_ERROR([ls -t appears to fail.  Make sure there is not a broken
alias in your environment])
   fi

   test "[$]2" = conftestfile
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly created file is older than distributed files!
Check your system clock])
fi
rm -f conftest*
AC_MSG_RESULT(yes)])

dnl AM_MISSING_PROG(NAME, PROGRAM, DIRECTORY)
dnl The program must properly implement --version.
AC_DEFUN(AM_MISSING_PROG,
[AC_MSG_CHECKING(for working $2)
# Run test in a subshell; some versions of sh will print an error if
# an executable is not found, even if stderr is redirected.
# Redirect stdin to placate older versions of autoconf.  Sigh.
if ($2 --version) < /dev/null > /dev/null 2>&1; then
   $1=$2
   AC_MSG_RESULT(found)
else
   $1="$3/missing $2"
   AC_MSG_RESULT(missing)
fi
AC_SUBST($1)])

# Like AC_CONFIG_HEADER, but automatically create stamp file.

AC_DEFUN(AM_CONFIG_HEADER,
[AC_PREREQ([2.12])
AC_CONFIG_HEADER([$1])
dnl When config.status generates a header, we must update the stamp-h file.
dnl This file resides in the same directory as the config header
dnl that is generated.  We must strip everything past the first ":",
dnl and everything past the last "/".
AC_OUTPUT_COMMANDS(changequote(<<,>>)dnl
ifelse(patsubst(<<$1>>, <<[^ ]>>, <<>>), <<>>,
<<test -z "<<$>>CONFIG_HEADERS" || echo timestamp > patsubst(<<$1>>, <<^\([^:]*/\)?.*>>, <<\1>>)stamp-h<<>>dnl>>,
<<am_indx=1
for am_file in <<$1>>; do
  case " <<$>>CONFIG_HEADERS " in
  *" <<$>>am_file "*<<)>>
    echo timestamp > `echo <<$>>am_file | sed -e 's%:.*%%' -e 's%[^/]*$%%'`stamp-h$am_indx
    ;;
  esac
  am_indx=`expr "<<$>>am_indx" + 1`
done<<>>dnl>>)
changequote([,]))])

