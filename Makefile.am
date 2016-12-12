## Process this file with automake to produce Makefile.in
AM_DEFAULT_SOURCE_EXT = .cpp
ACLOCAL_AMFLAGS = -I m4
bin_PROGRAMS    =
check_PROGRAMS  =

pkginclude_HEADERS  = descendu/d.hpp
pkginclude_HEADERS += descendu/hex.hpp

noinst_HEADERS  = test/catch.hpp
check_PROGRAMS += test/d
check_PROGRAMS += test/hex
check_PROGRAMS += test/redblob
TESTS = $(check_PROGRAMS)

DISTCLEANFILES = aminclude.am

@INC_AMINCLUDE@
