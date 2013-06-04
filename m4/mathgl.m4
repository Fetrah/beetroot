# mathgl.m4: Locate MathGL headers and libraries for autoconf-based projects.
# author: James Robinson <james.robinson@cern.ch>
# date:   May 2013

AC_DEFUN([AC_CHECK_MATHGL],[
  AC_MSG_RESULT([checking for MathGL])

  # Provide ability to set MathGL location
  mathglpath=""
  AC_ARG_WITH(mathgl, AC_HELP_STRING(--with-mathgl, prefix for MathGL installation),
              [mathglpath=${with_mathgl}],
              [mathglpath=${prefix}])

  # Add user path to search path for libraries and headers
  AS_IF([test "x${mathglpath}" != "x${prefix}"], [
    LDFLAGS="${LDFLAGS} -L${mathglpath}/lib"
    AC_SUBST(LDFLAGS)
    CPPFLAGS="$CPPFLAGS -I${mathglpath}/include"
    AC_SUBST(CPPFLAGS)
  ])

  # Check for MathGL library
  AC_CHECK_LIB(mgl, main, [], AC_MSG_ERROR([MathGL library could not be located. Try using --with-mathgl to specify its location]))

  # Check for MathGL headers
  AC_CHECK_HEADERS([mgl2/mgl.h], [], AC_MSG_ERROR([MathGL headers could not be located. Try using --with-mathgl to specify their location]))
])