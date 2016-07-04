dnl ----------------------------------------------------
dnl Package name, release number, description, and URL
dnl ----------------------------------------------------
AC_INIT([descendu], [0.0.0], [rhys.ulerich@gmail.com])
AC_REVISION([$Id$])
PACKAGE_DESCRIPTION="Draft of a lousy game inspired by Greed Corp"
AC_SUBST([PACKAGE_DESCRIPTION])
PACKAGE_URL="http://github.com/RhysU/descendu"
AC_SUBST([PACKAGE_URL])

dnl ------------------------------------------------
dnl Initialization macros
dnl ------------------------------------------------
AC_CONFIG_SRCDIR([descendu/hex.hpp])
AM_CONFIG_HEADER([descendu/config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE(1.11 no-define color-tests -Wall foreign subdir-objects)
AX_ADD_AM_CTAGSFLAGS

dnl -------------------------------
dnl Manipulate compilation settings
dnl -------------------------------
AX_CHECK_ENABLE_DEBUG([info])
AX_CXX_COMPILE_STDCXX_14([noext],[mandatory])
AX_CXXFLAGS_WARN_ALL

dnl ------------------------------------------------
dnl Generate Makefiles
dnl ------------------------------------------------
AC_CONFIG_FILES([
    Makefile
])

AC_OUTPUT()
