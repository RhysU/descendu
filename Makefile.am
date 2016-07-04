## Process this file with automake to produce Makefile.in
ACLOCAL_AMFLAGS = -I m4
bin_PROGRAMS    =
check_PROGRAMS  =
TESTS           =

TESTS          += test/d
check_PROGRAMS += test/d
test_d_SOURCES  = test/d.cpp

TESTS              += test/hello
check_PROGRAMS     += test/hello
test_hello_SOURCES  = test/hello.cpp

TESTS                += test/redblob
check_PROGRAMS       += test/redblob
test_redblob_SOURCES  = test/redblob.cpp

DISTCLEANFILES = aminclude.am

@INC_AMINCLUDE@
