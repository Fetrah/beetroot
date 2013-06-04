ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libbeetroot.la
libbeetroot_la_SOURCES = src/Axis.cxx src/DataPoint.cxx src/Figure.cxx src/FileHandler.cxx src/Histogram1D.cxx src/Named.cxx src/Plot.cxx src/ROOTFileHandler.cxx src/ROOTUtils.cxx src/UUIDWrapper.cxx
libbeetroot_la_CPPFLAGS = $(AM_CPPFLAGS) $(ROOTCPPFLAGS) $(BOOST_CPPFLAGS)
#libbeetroot_la_LDFLAGS = $(AM_LDFLAGS) $(ROOTLDFLAGS) -static -version-info 1:0:0
libbeetroot_la_LDFLAGS = $(AM_LDFLAGS) $(ROOTLDFLAGS) -version-info 1:0:0

include aminclude.am
EXTRA_DIST = $(DX_CONFIG) doc/html

library_includedir=$(includedir)/beetroot
library_include_HEADERS = beetroot/*.h
