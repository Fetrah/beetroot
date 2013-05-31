#AC_SEARCH_ROOT(actionIfFound, actionIfNotFound)
AC_DEFUN([AC_SEARCH_ROOT], [

AC_ARG_VAR([ROOTSYS], [Path to Root installation.])

AC_ARG_WITH([root-config],
        [AS_HELP_STRING([--with-root-config], [give the path to the root-config script if not in a default search path or specified in $ROOTSYS])],
        [root_config_path=$withval],[])

AC_ARG_WITH([root],
        [AS_HELP_STRING([--with-root], [give the path to the root installation directory containing include and bin directories if not in a default search path or specified in $ROOTSYS])],
        [root_path=$withval],[])
        
ROOTSEARCHPATH=$PATH

if test -n "$ROOTSYS"; then
  AC_MSG_NOTICE([ROOTSYS environment variable set: adding $ROOTSYS/bin to root-config search path])
  ROOTSEARCHPATH=$ROOTSYS/bin:$ROOTSEARCHPATH
fi

if test x$root_path != xyes && test x$root_path != xno ; then
  AC_MSG_NOTICE([Adding $root_path to root installation search path])
  ROOTSEARCHPATH=$root_path/bin:$ROOTSEARCHPATH
fi

if test x$root_config_path != xyes && test x$root_config_path != xno ; then
  AC_MSG_NOTICE([Adding $root_config_path to root-config search path])
  ROOTSEARCHPATH=$root_config_path:$ROOTSEARCHPATH
fi

AC_MSG_NOTICE([root-config search path is $ROOTSEARCHPATH])

AC_PATH_PROG(ROOTCONFIG, [root-config], [no], [$ROOTSEARCHPATH])

AS_IF([test x$ROOTCONFIG != xno ],
[have_root_config=yes],[have_root_config=no])

if test x$have_root_config = xyes ; then
  ROOTBINDIR="`$ROOTCONFIG --bindir`"
  AC_PATH_PROG(ROOTCINT, [rootcint], [no], [$ROOTBINDIR])
  ROOTLIBDIR="`$ROOTCONFIG --libdir`"
  
  xmlparser=no
  
  for extn in so dylib la a dll ; do
    if test -f $ROOTLIBDIR/libXMLParser.$extn ; then
      xmlparser=-lXMLParser
    fi
  done
  
  if test x$ROOTCINT != xno && test x$xmlparser != xno ; then
    if test -n $shlibpath_var ; then
      ROOTCINT="$ROOTCINT"
    fi
    have_root=yes
  else
    have_root=no
  fi
  
else
  have_root=no
fi


AM_CONDITIONAL(ENABLE_ROOT, [test x$have_root != xno])

if test x$have_root != xno; then
  AC_MSG_NOTICE([Using root-config to get ROOT paths])
  ROOTCPPFLAGS="`$ROOTCONFIG --cflags`"
  ROOTLIBS="`$ROOTCONFIG --libs`  -lXMLParser"
  ROOTLDFLAGS="`$ROOTCONFIG --ldflags`"

  AC_SUBST([ROOTCPPFLAGS])
  AC_SUBST([ROOTLIBS])
  AC_SUBST([ROOTLDFLAGS])
  AC_SUBST([ROOTBINDIR])
  AC_SUBST([ROOTCINT])
  AC_MSG_NOTICE([ROOTCPPFLAGS=$ROOTCPPFLAGS])
  AC_MSG_NOTICE([ROOTLIBS=$ROOTLIBS])
  AC_MSG_NOTICE([ROOTLDFLAGS=$ROOTLDFLAGS])
  AC_MSG_NOTICE([ROOTBINDIR=$ROOTBINDIR])
  AC_MSG_NOTICE([ROOTCINT=$ROOTCINT])
  $1
else

  AC_MSG_NOTICE([Root is not found!])
  $2
fi

])
