## Process this file with automake to produce Makefile.in
AM_DEFAULT_SOURCE_EXT = .cpp
ACLOCAL_AMFLAGS = -I m4
bin_PROGRAMS    =
check_PROGRAMS  =

pkginclude_HEADERS  = descendu/consumable.hpp
pkginclude_HEADERS += descendu/d.hpp
pkginclude_HEADERS += descendu/hex.hpp
pkginclude_HEADERS += descendu/map.hpp
pkginclude_HEADERS += descendu/optional.hpp
pkginclude_HEADERS += descendu/player.hpp
pkginclude_HEADERS += descendu/resource.hpp
pkginclude_HEADERS += descendu/tile.hpp
pkginclude_HEADERS += descendu/world.hpp

noinst_HEADERS  = test/catch.hpp
check_PROGRAMS += test/consumable
check_PROGRAMS += test/d
check_PROGRAMS += test/hex
check_PROGRAMS += test/map
check_PROGRAMS += test/player
check_PROGRAMS += test/redblob
check_PROGRAMS += test/resource
check_PROGRAMS += test/test_optional
check_PROGRAMS += test/test_type_traits
check_PROGRAMS += test/tile
check_PROGRAMS += test/world
TESTS = $(check_PROGRAMS)

DISTCLEANFILES = aminclude.am

@INC_AMINCLUDE@
