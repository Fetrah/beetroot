## configure.ac for libbeetroot
## James Robinson
## james.robinson@cern.ch

AC_PREREQ(2.59)
AC_INIT( [beetroot], [1.0.0], [james.robinson@cern.ch])

AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([beetroot/FileHandler.h])
AC_CONFIG_HEADERS([config/config.h])
AC_LANG(C++)

AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S

AC_SEARCH_ROOT([AC_MSG_NOTICE([Found Root])],[AC_MSG_ERROR([ROOT is required and is not found.  Please either set the path to Root using ROOTSYS or --with-root-config or --with-root])])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([mkdir])

AM_CXXFLAGS="$AM_CXXFLAGS -Wall -O2 "
AM_CPPFLAGS="$AM_CPPFLAGS -Wall -O2 -I\$(top_builddir)"
AC_SUBST(AM_CXXFLAGS)
AC_SUBST(AM_CPPFLAGS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT