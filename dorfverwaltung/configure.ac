dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(dorfverwaltung, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC






AM_PROG_LIBTOOL






PKG_CHECK_MODULES(LiteSql, litesql sqlite3)
PKG_CHECK_MODULES(UnitTest, cppunit)
AC_OUTPUT([
Makefile
src-test/Makefile
src/Makefile

])
