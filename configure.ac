#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Perlude
AC_PREREQ([2.63])
AC_INIT([YiCppLib::BayesGenotype], [1.0.0], [atrusqiao@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Fixing file creation time
find ${srcdir} -name aclocal.m4 -exec touch {} \;
find ${srcdir} -name \*.in -exec touch {} \;
find ${srcdir} -name configure -exec touch {} \;



# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
#AM_PROG_AR
LT_PREREQ([2.2])
LT_INIT([disable-shared])
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AC_CHECK_PROG([dot], [dot], [yes], [no])
AM_CONDITIONAL([FOUND_DOT], [test "x$dot" = xyes])
AM_COND_IF([FOUND_DOT],,[AC_MSG_WARN([Graphviz dot utility not found. Document compiling disabled])])

AC_CONFIG_SRCDIR([src/Genotyper.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for libraries.

## START: CHECKING FOR GSL ##
AC_ARG_WITH([gsl],
			[AS_HELP_STRING([--with-gsl=DIR], 
							[specify the path to search for gnu scientific library])],
							[gsl_path=${withval}])

if test "x${gsl_path}" != x; then
	if test -e ${gsl_path}/lib; then LDFLAGS+=" -L${gsl_path}/lib"; fi
	if test -e ${gsl_path}/lib64; then LDFLAGS+=" -L${gsl_path}/lib64"; fi
	if test -e ${gsl_path}/include; then CPPFLAGS+=" -I${gsl_path}/include"; fi
fi

echo "checking for gsl in ${gsl_path}"

have_gsl=no

AC_SEARCH_LIBS([gsl_cdf_binomial_Q], [gsl], [have_gsl=yes], [have_gsl=no], [-lgsl -lgslcblas -lm])

if test "x${have_gsl}" = xyes; then
	AC_CHECK_HEADERS([gsl/gsl_cdf.h], [], [have_gsl=no])
fi

if test "x${have_gsl}" = xno; then
	AC_MSG_ERROR([Unable to locate gsl])
fi
## END: CHECKINF FOR GSL ##

## START: CHECKING FOR GMOCK ##
AC_ARG_WITH([gmock],
			[AS_HELP_STRING([--with-gmock=DIR],
							[specify the path to search for gmock])],
							[gmock_path=${withval}])
if test "x${gmock_path}" != x; then
	if test -e ${gmock_path}/lib; then LDFLAGS+=" -L${gmock_path}/lib"; fi
	if test -e ${gmock_path}/include; then CPPFLAGS+=" -isystem ${gmock_path}/include -I${gmock_path}"; fi
	if test -e ${gmock_path}/gtest/lib; then LDFLAGS+=" -L${gmock_path}/gtest/lib"; fi
	if test -e ${gmock_path}/gtest/include; then CPPFLAGS+=" -isystem ${gmock_path}/gtest/include -I${gmock_path}/gtest"; fi
fi
echo "checking for gmock in ${gmock_path}"

AC_CHECK_HEADERS([gmock/gmock.h], [have_gmock=yes], [have_gmock=no])
AC_CHECK_HEADERS([gtest/gtest.h], [have_gtest=yes], [have_gtest=no])

AM_CONDITIONAL([FOUND_GMOCK], [test "x${have_gmock}" == xyes])
AM_CONDITIONAL([FOUND_GTEST], [test "x${have_gtest}" == xyes])

AM_CONDITIONAL([CUSTOM_GMOCK_PATH], [test "x${gmock_path}" != x])
AM_COND_IF([FOUND_GMOCK], [AC_SUBST([GMOCK_DIR], [${gmock_path}])], [AC_MSG_WARN([Unable to locate gmock header, testing disabled])])
AM_COND_IF([FOUND_GTEST], [AC_SUBST([GTEST_DIR], [${gmock_path}/gtest])], [AC_MSG_WARN([Unable to locate gtest header, testing disabled])])
## END: CHECKINF FOR GMOCK ##


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
				 src/Makefile
				 doc/Makefile
				 test/Makefile])

AC_OUTPUT
