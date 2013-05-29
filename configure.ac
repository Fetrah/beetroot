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

# Checks for boost
BOOST_REQUIRE
BOOST_FOREACH
BOOST_FORMAT

AC_SEARCH_ROOT([AC_MSG_NOTICE([Found Root])],[AC_MSG_ERROR([ROOT is required and is not found.  Please either set the path to Root using ROOTSYS or --with-root-config or --with-root])])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([mkdir])

AM_CXXFLAGS="$AM_CXXFLAGS -O2 -Wall -Wextra -Wabi -Weffc++ -Wno-reorder"
AM_CPPFLAGS="$AM_CPPFLAGS -O2 -Wall -Wextra -Wabi -Weffc++ -Wno-reorder -I\$(top_builddir)"
AC_SUBST(AM_CXXFLAGS)
AC_SUBST(AM_CPPFLAGS)

DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN(libbeetroot, doxygen.cfg, doc)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT