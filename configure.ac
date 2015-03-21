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

if test "x${gsl_path}" != x -a -x "${gsl_path}/bin/gsl-config"; then
	GSL_LDADDS=`${gsl_path}/bin/gsl-config --libs` 
	GSL_CPPFLAGS=`${gsl_path}/bin/gsl-config --cflags`
else
	GSL_LDADDS=`gsl-config --libs` 
	GSL_CPPFLAGS=`gsl-config --cflags`
fi

echo "checking for gsl in ${gsl_path}"

LDADDS+=" ${GSL_LDADDS}"
CPPFLAGS+=" ${GSL_CPPFLAGS}"

have_gsl=yes
AC_SEARCH_LIBS([gsl_ran_multinomial_pdf], [gsl], [], [have_gsl=no], [${GSL_LDADDS}])
AC_SEARCH_LIBS([gsl_multiset_calloc],     [gsl], [], [have_gsl=no], [${GSL_LDADDS}])
AC_SEARCH_LIBS([gsl_multiset_next],       [gsl], [], [have_gsl=no], [${GSL_LDADDS}])
AC_SEARCH_LIBS([gsl_multiset_free],       [gsl], [], [have_gsl=no], [${GSL_LDADDS}])

if test "x${have_gsl}" = xyes; then
	AC_CHECK_HEADERS([gsl/gsl_multiset.h], [], [have_gsl=no])
	AC_CHECK_HEADERS([gsl/gsl_randist.h], [], [have_gsl=no])
fi

AM_CONDITIONAL([FOUND_GSL], [test "x${have_gsl}" == xyes])
AM_CONDITIONAL([CUSTOM_GSL_PATH], [test "x${gsl_path}" != x])
AM_COND_IF([FOUND_GSL], [AC_SUBST([GSL_DIR], [${gsl_path}])], [AC_MSG_ERROR([Unable to locate usable gsl library. If you have a custom built version, supply the path with --with-gsl=<path>])])
AC_SUBST([GSL_LDADDS], [${GSL_LDADDS}])
AC_SUBST([GSL_CPPFLAGS], [${GSL_CPPFLAGS}])
## END: CHECKINF FOR GSL ##

## START: CHECKING FOR GMOCK ##
AC_ARG_WITH([gmock],
			[AS_HELP_STRING([--with-gmock=DIR],
							[specify the path to search for gmock])],
							[gmock_path=${withval}])
if test "x${gmock_path}" != x -a -x "${gmock_path}/scripts/gmock-config"; then
	GMOCK_CONFIG="${gmock_path}/scripts/gmock-config"
else
	GMOCK_CONFIG="gmock-config"
fi

GMOCK_CPPFLAGS=`${GMOCK_CONFIG} --cppflags`
GMOCK_CXXFLAGS=`${GMOCK_CONFIG} --cxxflags`
GMOCK_LDFLAGS=`${GMOCK_CONFIG} --ldflags`
GMOCK_LDADDS=`${GMOCK_CONFIG} --libs`
CPPFLAGS+=" ${GMOCK_CPPFLAGS}"
CXXFLAGS+=" ${GMOCK_CXXFLAGS}"

echo "checking for gmock in ${gmock_path}"

AC_CHECK_HEADERS([gmock/gmock.h], [have_gmock=yes], [have_gmock=no])
AC_CHECK_HEADERS([gtest/gtest.h], [have_gtest=yes], [have_gtest=no])

AM_CONDITIONAL([FOUND_GMOCK], [test "x${have_gmock}" == xyes])
AM_CONDITIONAL([FOUND_GTEST], [test "x${have_gtest}" == xyes])

AM_CONDITIONAL([CUSTOM_GMOCK_PATH], [test "x${gmock_path}" != x])
AM_COND_IF([FOUND_GMOCK], [AC_SUBST([GMOCK_DIR], [${gmock_path}])], [AC_MSG_WARN([Unable to locate gmock header, testing disabled])])
AM_COND_IF([FOUND_GTEST], [AC_SUBST([GTEST_DIR], [${gmock_path}/gtest])], [AC_MSG_WARN([Unable to locate gtest header, testing disabled])])
AC_SUBST([GMOCK_CPPFLAGS], [${GMOCK_CPPFLAGS}])
AC_SUBST([GMOCK_CXXFLAGS], [${GMOCK_CXXFLAGS}])
AC_SUBST([GMOCK_LDFLAGS], [${GMOCK_LDFLAGS}])
AC_SUBST([GMOCK_LDADDS], [${GMOCK_LDADDS}])
## END: CHECKINF FOR GMOCK ##


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
				 src/Makefile
				 doc/Makefile
				 test/Makefile])

AC_OUTPUT
